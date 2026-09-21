#include <iostream>
using namespace std;

void bubbleSort(int a[], int s){
    for (int j; j < s; j++){
        bool isSwapped = false;
        for (int i=0; i < s-j-1; i++){
            if (a[i] > a[i+1]){
                swap (a[i], a[i+1]);
                isSwapped = true;
            }
        }
        if (isSwapped == true){
            break;
        }
    }
}

int main()
{
    int a[] = {12, 16, 11, 13, 14};
    int s = sizeof(a) / sizeof(a[0]);
    
    cout << "Antes de ordenar los elementos del array son" << endl;
    for (int j=0; j < s; j++){
        cout << a[j] << " ";
    }
    
    bubbleSort (a, s);
    
    cout << "\nDespues de ordenar los elemntos del array son: " << endl;
    for (int j=0; j < s; j++){
        cout << a[j] << " ";
    }
    return 0;
}