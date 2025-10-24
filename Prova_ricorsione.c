#include <stdio.h>
#include <math.h>

// Funzione ricorsiva
long long fattoriale(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * fattoriale(n - 1);
    }
}

int main() {
    int num;
    printf("Inserisci un numero intero non negativo: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Errore: il fattoriale non e' definito per numeri negativi.\n");
        return 1;
    } else {
        printf("Il fattoriale di %d e' %lli \n", num, fattoriale(num));
    }

    return 0;
}