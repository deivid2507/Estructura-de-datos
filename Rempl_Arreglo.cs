using System;
class Remplazar {
  static void Main() {
    const int filas = 3;
    const int columnas = 4;
   
   int?[,] matriz = new int? [filas, columnas]{
            { 1, 0, null, null},
            { 4, null, 6, 8},
            { null, 10, 11, null}
   };
   Console.WriteLine("Matriz con espacios nulos");
   for (int i= 0; i < filas; i++){
       for (int j=0; j < columnas; j++){
           if (matriz[i,j].HasValue){
               Console.Write(matriz[i,j].Value + " ");
           }
           else{
               Console.Write("- ");
           }
       }
            Console.WriteLine();
   } 
    for ( int i=0; i < filas; i++){
        for ( int j=0; j < columnas; j++){
            if (!matriz[i,j].HasValue){
                for( int k= i +1; k < filas; k++){
                    if (matriz[k,j].HasValue){
                        matriz[i,j]= matriz[k,j];
                        matriz[k,j]= null;
                        break;
                    }
                }
            }
        }
    }
     Console.WriteLine();
     Console.WriteLine();
     
       Console.WriteLine("Matriz Recorrida");
       for (int i= 0; i < filas; i++){
        for (int j=0; j < columnas; j++){
           if (matriz[i,j].HasValue){
               Console.Write(matriz[i,j].Value + " ");
           }
           else{
               Console.Write("- ");
           }
       }
       Console.WriteLine();
     }

  }
}