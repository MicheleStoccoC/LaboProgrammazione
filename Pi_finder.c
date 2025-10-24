#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

            /* Pi finder con numeri casuali */
/* Quadrato di lato 2 centrato in O=(0;0) */

int main() {
    int N, i, count = 0;
    double x, y, pi;

    printf("Inserisci il numero di punti da generare: ");
    scanf("%d", &N);

    /* Per inizializzare il generatore */
    srand(time(NULL));

    for (i = 0; i < N; i++) {
        x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        if (x*x + y*y <= 1.0) {
            count++;
        }
    }

    pi = 4.0 * (double)count / (double)N;
    printf("Valore approssimato del Pi greco: %lf \n", pi);

    return 0;
}

/* Prove con diversi N
1e1  : 3.2
1e2 : 3.24
1e3 : 3.224
1e4 : 3.1336
1e5 : 3.1471
1e6 : 3.1406
1e7 : 3.1404
1e8 : 3.141479
1e9 : 3.141493
*/