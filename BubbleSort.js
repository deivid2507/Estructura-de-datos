function bubbleSort(a) {
    let s = a.length;
    for (let j = 0; j < s; j++) {
        let isSwapped = false;
        for (let i = 0; i < s - j - 1; i++) {
            if (a[i] > a[i + 1]) {
                [a[i], a[i + 1]] = [a[i + 1], a[i]];
                isSwapped = true;
            }
        }
        if (isSwapped === false) {
            break;
        }
    }
}

function main() {
    let a = [15, 16, 11, 13, 14];

    console.log("Antes de ordenar los elementos del array son:");
    console.log(a.join(" "));

    bubbleSort(a);

    console.log("\nDespués de ordenar los elementos del array son:");
    console.log(a.join(" "));
}

main();