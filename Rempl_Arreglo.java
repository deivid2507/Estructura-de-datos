public class Main
{
	public static void main(String[] args) {
	    final int filas = 3;
	    final int columnas = 4;
		
		Integer[][] matriz = new Integer[][]{
		    { 1, 0, null, null},
            { 4, null, 6, 8},
            { null, 10, 11, null}
		};
		System.out.println("Matriz con espacios nulos");
		for (int i = 0; i < filas; i++){
		    for (int j=0; j < columnas; j++){
		        if (matriz[i][j] != null){
		            System.out.print(matriz[i][j] + " ");
		        }else{
		            System.out.print("- ");
		        }
		        
		    }
		    System.out.println();
		}
		
		for (int i = 0; i < filas; i++){
		    for (int j=0; j < columnas; j++){
		        if (matriz[i][j] == null){
		            for(int k= i +1; k < filas; k++){
		                matriz[i][j]= matriz[k][j];
		                matriz[k][j]= null;
		                break;
		            }
		        }
		    }
		}
		
		System.out.println();
		System.out.println();
		
		System.out.println("Matriz recorrida");
		for (int i = 0; i < filas; i++){
		    for (int j=0; j < columnas; j++){
		        if (matriz[i][j] != null){
		            System.out.print(matriz[i][j] + " ");
		        }else{
		            System.out.print("- ");
		        }
		        
		    }
		    System.out.println();
		}

	}
}
