#include <iostream>
#include <optional>

using namespace std;

int main() {
    const int filas = 3;
    const int columnas = 4;
    int vacio = 0; 

    optional <int> matriz [filas][columnas] = 
    {
        {1, 0, nullopt, nullopt},
        {4, nullopt, 6, 8},
        {nullopt, 10, 11, nullopt}
    };
    cout << "Matriz con espacios nulos" << endl;
    for (int i=0; i< filas; i++){
       for (int j=0; j < columnas; j++){
       if (matriz[i][j].has_value()) {
                cout << matriz[i][j].value() << " ";
            } else {
                cout << "- "; 
                 vacio++;
            }
        
        }
        cout << "\n";
    }
 
     for (int i=0; i< filas; i++){
       for (int j=0; j < columnas; j++){
        if (!matriz[i][j].has_value()) {
                   for (int k= i+1; k< filas; k++){
                        matriz[i][j]= matriz[k][j];
                        matriz[k][j]= nullopt;
                        break;
                   }
            
            }
       
    }
}
     cout << "\n";
     cout << "\n";
    cout << "Matriz Recorrida" << endl;
    for (int i=0; i< filas; i++){
       for (int j=0; j < columnas; j++){
            if (matriz[i][j].has_value()) {
                cout << matriz[i][j].value() << " ";
            } else {
                cout << "- "; 
                 vacio++;
            }
        
        }
        cout << "\n";
    }
    return 0;
}