filas=3
columnas=4

matriz=[
    [1, 0, None, None],
    [4, None, 6, 8],
    [None, 10, 11, None]
]
    
print ("Matriz con espacios nulos")
for i in range (filas):
    for j in range (columnas):
        if matriz[i][j] is not None :
            print( str(matriz[i][j]) + " ", end="")
        else:
            print ("- " ,end ="")
    print()
    
for i in range(filas):
    for j in range(columnas):
        if (matriz[i][j] is None):
            for k in range (i + 1,filas):
                matriz[i][j] = matriz[k][j]
                matriz[k][j] = None
                break
print()
print()

print("Matriz Recorrida")
for i in range (filas):
    for j in range (columnas):
        if matriz is not None:
            print(str (matriz[i][j]) +  " ", end="")
        else:
            print ("- " ,end="")
    print()