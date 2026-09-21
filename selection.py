def selection(a):

    for i in range(len(a)):
        small = i
        for j in range(i+1, len(a)):
            if a[small] > a[j]:
                small = j
        a[i], a[small] = a[small], a[i]
def printArr(a):
    for i in range(len(a)):
        print (a[i], end = " ")
a = [65, 26, 13, 23, 12]
print("Arreglo antes de ser ordenado: ")
printArr(a)
selection(a)
print("\nArreglo despues de ser ordenado")
selection(a)
printArr(a)