#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

const int tam = 8;
const int MAX_MOV = 200;

// struct para almacenar cada movimiento del historial
struct Jugada {
	char jugador;
	int fo, co;
	int fd, cd;
	bool captura;
};

Jugada historial[MAX_MOV];
int total_mov = 0;

void limpiar_hist() {
	total_mov = 0;
}

// Guarda los movimentos en un historial
void registrar(char jug, int fo, int co, int fd, int cd) {
	if (total_mov < MAX_MOV) {
		historial[total_mov].jugador = jug;
		historial[total_mov].fo = fo + 1;
		historial[total_mov].co = co + 1;
		historial[total_mov].fd = fd + 1;
		historial[total_mov].cd = cd + 1;
		historial[total_mov].captura = (abs(fd - fo) == 2);
		total_mov++;
	}
}

// Identifica a las fichas coronadas
bool es_reina(char f) {
	return (f == 'X' || f == 'O');
}

// Identifica a las fichas enemigas
bool es_enemiga(char f, char jug) {
	if (jug == 'x' && (f == 'o' || f == 'O')) return true;
	if (jug == 'o' && (f == 'x' || f == 'X')) return true;
	return false;
}

// Identifica las fichas del jugador en turno
bool es_propia(char f, char jug) {
	if (jug == 'x' && (f == 'x' || f == 'X')) return true;
	if (jug == 'o' && (f == 'o' || f == 'O')) return true;
	return false;
}

// Valida que la fila y columna se encuentren en el rango de 0 a 7
bool dentro(int f, int c) {
	return (f >= 0 && f < tam && c >= 0 && c < tam);
}

// Coloca las fichas en el tablero
void init_tab(char t[tam][tam]) {
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			t[i][j] = ' ';
			if ((i + j) % 2 != 0) {
				if (i < 3) t[i][j] = 'x';
				if (i > 4) t[i][j] = 'o';
			}
		}
	}
}

// Funcion para mostrar el tablero
void ver_tab(char t[tam][tam]) {
	cout << "   1  2  3  4  5  6  7  8\n";
	for (int i = 0; i < tam; i++) {
		cout << (i + 1) << " ";
		for (int j = 0; j < tam; j++) {
			if ((i + j) % 2 != 0) {
				cout << "\033[40m " << t[i][j] << " \033[0m"; // Casilla oscura
			} else {
				cout << "\033[47m " << t[i][j] << " \033[0m"; // Casilla clara
			}
		}
		cout << "\n";
	}
}

// Valida que el tipo de dato ingresado sea validon y que las filas y columnas de destino se encuentren en el rango correcto
void pedir_pos(int &f, int &c) {
	f = 0;
	c = 0;
	while (f < 1 || f > 8 || c < 1 || c > 8) {
		cout << "Columna (1-8): ";
		cin >> c;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Entrada invalida. Por favor ingresa solo numeros.\n";
			f = 0;
			c = 0;
		} else {
			cout << "Fila (1-8): ";
			cin >> f;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Entrada invalida. Por favor ingresa solo numeros.\n";
				f = 0;
				c = 0;
			} else if (f < 1 || f > 8 || c < 1 || c > 8) {
				cout << "Posicion fuera de rango (1-8). Intenta de nuevo.\n";
			}
		}
	}
}

// Verifica que la casilla seleccionada contenga una ficha del jugador actual
bool ficha_valida(char t[tam][tam], int f, int c, char jug) {
	if (es_propia(t[f][c], jug)) return true;
	cout << "Ahi no hay una ficha tuya. Intenta de nuevo.\n";
	return false;
}

// Valida si la direccion del movimiento en vertical es permitida para la ficha
bool avance_ok(char jug, int df, bool reina) {
	if (reina) return true;
	if (jug == 'x' && df > 0) return true;
	if (jug == 'o' && df < 0) return true;
	return false;
}

// Valida si la ficha dada tiene al menos un movimiento de captura posible
bool puede_comer(char t[tam][tam], int fo, int co, char jug) {
	int d[2] = {-1, 1};
	bool reina = es_reina(t[fo][co]);

	for (int a = 0; a < 2; a++) {
		for (int b = 0; b < 2; b++) {
			int fm = fo + d[a];
			int cm = co + d[b];
			int fd = fo + 2 * d[a];
			int cd = co + 2 * d[b];

			if (dentro(fd, cd) && t[fd][cd] == ' ') {
				if (es_enemiga(t[fm][cm], jug) && avance_ok(jug, d[a], reina)) {
					return true;
				}
			}
		}
	}
	return false;
}

// Valida que hayan capturas disponibles
bool hay_captura(char t[tam][tam], char jug) {
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (es_propia(t[i][j], jug) && puede_comer(t, i, j, jug)) {
				return true;
			}
		}
	}
	return false;
}

// Muestra los movimientos posibles en base a la ficha origen
void ver_opciones(char t[tam][tam], int fo, int co, char jug) {
	int d[2] = {-1, 1};
	bool reina = es_reina(t[fo][co]);
	int opciones = 0;

	cout << "\n--- Opciones disponibles para la ficha (" << (co + 1) << ", " << (fo + 1) << ") ---\n";

	for (int a = 0; a < 2; a++) {
		for (int b = 0; b < 2; b++) {
			for (int p = 1; p <= 2; p++) {
				int fd = fo + d[a] * p;
				int cd = co + d[b] * p;
				if (dentro(fd, cd) && t[fd][cd] == ' ' && avance_ok(jug, d[a], reina)) {
					bool valido = true;
					if (p == 2) {
						valido = es_enemiga(t[fo + d[a]][co + d[b]], jug);
					}
					if (valido) {
						opciones++;
						cout << " -> Columna " << (cd + 1) << ", Fila " << (fd + 1);
						if (p == 2) cout << " (CAPTURA)";
						cout << "\n";
					}
				}
			}
		}
	}

	if (opciones == 0) {
		cout << " -> No hay movimientos posibles para esta ficha.\n";
	}
	cout << "--------------------------------------------------\n";
}

// Valida que el Movimiento a la casilla destino sea valido
bool mov_valido(char t[tam][tam], int fo, int co, int fd, int cd, char jug) {
	if (t[fd][cd] != ' ') {
		cout << "La casilla destino no esta vacia.\n";
		return false;
	}

	int dif_f = fd - fo;
	int dif_c = abs(cd - co);
	bool reina = es_reina(t[fo][co]);

	if (dif_c != 1 && dif_c != 2) {
		cout << "Movimiento invalido. Debe ser de 1 o 2 casillas en diagonal.\n";
		return false;
	}

	if (abs(dif_f) != dif_c) {
		cout << "El movimiento debe ser diagonal.\n";
		return false;
	}

	// Regla de captura obligatoria
	if (hay_captura(t, jug) && dif_c != 2) {
		cout << "Regla del juego: Es obligatorio capturar si tienes una oportunidad.\n";
		return false;
	}

	// Fichas normales solo van hacia adelante
	if (!reina) {
		if (jug == 'x' && dif_f < 0) {
			cout << "Las fichas 'x' solo pueden avanzar hacia abajo.\n";
			return false;
		}
		if (jug == 'o' && dif_f > 0) {
			cout << "Las fichas 'o' solo pueden avanzar hacia arriba.\n";
			return false;
		}
	}

	// Si es captura, verifica la ficha intermedia
	if (dif_c == 2) {
		int fm = (fo + fd) / 2;
		int cm = (co + cd) / 2;

		if (!es_enemiga(t[fm][cm], jug)) {
			cout << "No hay una ficha enemiga en medio para capturar.\n";
			return false;
		}
	}

	return true;
}

// Aplica el movimiento en el tablero
void mover(char t[tam][tam], int fo, int co, int fd, int cd) {
	if (abs(fd - fo) == 2) {
		int fm = (fo + fd) / 2;
		int cm = (co + cd) / 2;
		t[fm][cm] = ' ';
	}

	t[fd][cd] = t[fo][co];
	t[fo][co] = ' ';
}

// Corona a la ficha si cruza todo el tablero
void coronar(char t[tam][tam], int fd, int cd) {
	if (t[fd][cd] == 'x' && fd == 7) t[fd][cd] = 'X';
	if (t[fd][cd] == 'o' && fd == 0) t[fd][cd] = 'O';
}

// Cuenta cuantas fichas le quedan a cada jugador
void contar(char t[tam][tam], int &fichas_x, int &fichas_o) {
	fichas_x = 0;
	fichas_o = 0;

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (t[i][j] == 'x' || t[i][j] == 'X') fichas_x++;
			if (t[i][j] == 'o' || t[i][j] == 'O') fichas_o++;
		}
	}
}

// Escribe los datos de la partida finalizada en "partida_finalizada.txt"
void guardar(char t[tam][tam], char ganador, int fichas_x, int fichas_o) {
	ofstream archivo("partida_finalizada.txt");

	if (!archivo.is_open()) {
		cout << "\n[X] Error al intentar crear/abrir el archivo para guardar.\n";
		return;
	}

	archivo << "========================================\n";
	archivo << "       REGISTRO DE PARTIDA FINALIZADA   \n";
	archivo << "========================================\n\n";
	archivo << "Ganador: Jugador '" << ganador << "'\n";
	archivo << "Fichas restantes 'x': " << fichas_x << "\n";
	archivo << "Fichas restantes 'o': " << fichas_o << "\n\n";

	archivo << "----------------------------------------\n";
	archivo << "       HISTORIAL DE MOVIMIENTOS         \n";
	archivo << "----------------------------------------\n";

	if (total_mov == 0) {
		archivo << "(No se registraron movimientos)\n";
	} else {
		for (int i = 0; i < total_mov; i++) {
			archivo << "Jugada " << (i + 1) << " | Jugador '" << historial[i].jugador << "': "
			        << "De Col " << historial[i].co << ", Fila " << historial[i].fo
			        << " -> A Col " << historial[i].cd << ", Fila " << historial[i].fd;

			if (historial[i].captura) archivo << " [CAPTURA]";
			archivo << "\n";
		}
	}

	archivo << "\n----------------------------------------\n";
	archivo << "       ESTADO FINAL DEL TABLERO         \n";
	archivo << "----------------------------------------\n\n";

	archivo << "   1 2 3 4 5 6 7 8\n";
	for (int i = 0; i < tam; i++) {
		archivo << (i + 1) << " |";
		for (int j = 0; j < tam; j++) {
			if (t[i][j] == ' ') archivo << " |";
			else archivo << t[i][j] << "|";
		}
		archivo << "\n";
	}

	archivo.close();
	cout << "\n[!] La partida se guardo exitosamente en 'partida_finalizada.txt'\n";
}

// Funcion principal del juego
int main() {
	char reintentar;

	// Controla reinicio de partidas
	do {
		char tab[tam][tam];
		init_tab(tab); // Llama a init_tab
		limpiar_hist(); // Llama a limpiar_hist

		char jug = 'x';       // Inicia jugador x
		int fo, co, fd, cd;   // Coordenadas origen y destino

		// Bucle de turnos
		while (true) {
			system("cls"); //Limpia pantalla
			ver_tab(tab); // Llama a ver_tab

			// Revisa captura obligatoria
			bool obligatoria = hay_captura(tab, jug); // Llama a hay_captura
			if (obligatoria) {
				cout << "\nATENCION: tienes una captura obligatoria disponible\n";
			}

			// Bucle para seleccionar origen
			while (true) {
				cout << "\nTurno del Jugador '" << jug << "' - Selecciona la ficha a mover:\n";
				pedir_pos(fo, co); // Llama a pedir_pos

				// Resta el numero ingresado por el jugador en uno para que este dentro de los espacios de la matriz
				fo--;
				co--;

				// Valida ficha propia
				if (!ficha_valida(tab, fo, co, jug)) { // Llama a ficha_valida
					continue;
				}

				// Valida captura obligatoria
				if (obligatoria && !puede_comer(tab, fo, co, jug)) { // Llama a puede_comer
					cout << "Esta ficha no puede capturar - Elige una que si pueda\n";
					continue;
				}

				break;
			}

			// Selecciona destino y ejecuta movimiento
			ver_opciones(tab, fo, co, jug); // Llama a ver_opciones

			// Bucle para seleccionar destino
			do {
				cout << "Selecciona la casilla destino:\n";
				pedir_pos(fd, cd); // Llama a pedir_pos
				fd--;
				cd--;
			} while (!mov_valido(tab, fo, co, fd, cd, jug)); // Llama a mov_valido

			mover(tab, fo, co, fd, cd); // Llama a mover
			registrar(jug, fo, co, fd, cd); // Llama a registrar
			coronar(tab, fd, cd); // Llama a coronar

			int fichas_x, fichas_o;
			contar(tab, fichas_x, fichas_o); // Llama a contar

			// Verifica ganador
			if (fichas_x == 0 || fichas_o == 0) {
				system("cls"); // Borra la consola
				ver_tab(tab);  // Llama a ver_tab

				char ganador = 'x';
				if (fichas_x == 0) ganador = 'o';

				cout << "\nEl Jugador '" << ganador << "' ha ganado la partida\n";

				// Opcion de guardado
				char opcion;
				cout << "\nDeseas guardar el registro de la partida? (s/n): ";
				cin >> opcion;

				if (opcion == 's' || opcion == 'S') {
					guardar(tab, ganador, fichas_x, fichas_o); // Llama a guardar
				}

				break;
			}

			// Cambio de turno
			if (jug == 'x') jug = 'o';
			else jug = 'x';
		}

		cout << "\nDesean jugar otra partida? (s/n): ";
		cin >> reintentar;

	} while (reintentar == 's' || reintentar == 'S');

	return 0;
}