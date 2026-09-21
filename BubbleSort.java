public class BubbleSort {

    public static void bubbleSort(int[] a) {
        int s = a.length;
        for (int j = 0; j < s; j++) {
            boolean isSwapped = false;
            for (int i = 0; i < s - j - 1; i++) {
                if (a[i] > a[i + 1]) {
                  a[i] = a[i] + a[i + 1];     
                  a[i + 1] = a[i] - a[i + 1]; 
                  a[i] = a[i] - a[i + 1];
                  isSwapped = true;
                }
            }
            if (isSwapped == false) {
                break;
            }
        }
    }

    public static void main(String[] args) {
        int[] a = {15, 16, 11, 13, 14};
        System.out.println("Antes de ordenar los elementos del array son: ");
       for (int i = 0; i< a.length; i++) {
            System.out.printf("%d ", a[i]);
        }

        bubbleSort(a);
        
        System.out.println("\nDespués de ordenar los elementos del array son: ");
        for (int j = 0; j < a.length; j++) {
            System.out.printf("%d ", a[j]);
        }
    }
}