using System;
class HelloWorld {
    static void BubbleSort(int[] a) {
    int s = a.Length;
    for (int j=0; j < s; j++){
        bool isSwapped = false;
        for (int i=0; i < s-j-1; i++){
            if (a[i] > a[i + 1]){
               (a[i], a[i + 1]) = (a[i + 1], a[i]);
                isSwapped = true;
            }
        }
        if (isSwapped == true){
            break;
        }
    }
  }
  static void Main(string[] args) {
    int[] a = { 15, 16, 11, 13, 14 };
    
    Console.WriteLine("Antes de ordenar los elementos del array :");
    for (int i=0; i < a.Length; i++){
        Console.Write(a[i] + " ");
    }
    
    BubbleSort(a);
    
    Console.WriteLine("\nLos elementos del array son: ");
    for (int i=0; i < a.Length; i++){
        Console.Write(a[i] + " ");
    }
  }
}