function main (){
    const filas = 3;
    const columnas = 4;
    let matriz = [
        [1, 0, null, null],
        [4, null, 6, 8],
        [null, 10, 11, null]
    ]; 
    
    console.log("Matriz con espacios nulos");
    for (let i = 0; i < filas; i++){
        let filaTexto="";
        for (let j = 0; j < columnas; j++){
            if (matriz[i][j] !== null){
                filaTexto+= matriz[i][j] + " ";
            } else{
                filaTexto += "- ";
            }
        }
        console.log(filaTexto);
    }
    
    for (let i =0;i < filas; i++){
        for(let j = 0; j < columnas; j++){
            if (matriz[i][j] === null){
                for (let k= i+1; k < filas; k++){
                    matriz[i][j] = matriz[k][j];
                    matriz[k][j] = null;
                    break;
                }
            }
        }
    }
    let filaTexto="";
    console.log(filaTexto);
    console.log(filaTexto);
    
    console.log ("Matriz Recorrida");
    for (let i=0; i < filas; i++){
         let filaTexto="";
        for (let j=0; j < columnas; j++){
            if (matriz[i][j] !== null){
                filaTexto+= matriz[i][j] + " ";
            } else{
                filaTexto += "- ";
            }
        }
        console.log(filaTexto);
    }
    }

main();