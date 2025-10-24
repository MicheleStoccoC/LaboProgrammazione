#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
#define E 2.71828

        /* PUNTO */
struct point {
    double x;
    double y;
};

        /* PUNTO CASUALE */
struct point genera_punto(double r) {
    struct point temp;
    double theta = ((double) rand() / RAND_MAX)*2.0*PI;
    temp.x = r*cos(theta);
    temp.y = r*sin(theta);
    return temp;
}

        /* MAIN */
int main(int argc, char *argv[]) {
    if (argc != 5){
        printf("Numero di argomenti sbagliato, ne servono 5: file, N, M, r1, r2. \n");
        return 1;
    }
    if(atoi(argv[1])>=1e5 || atoi(argv[2])>=1e5){
        printf("Numero massimo di punti generabili ecceduto: max=99'999. \n");
        return 1;
    }
    if(atof(argv[3])>=1e2 || atof(argv[4])>=1e2){
        printf("Raggio massimo ecceduto: max=99.99999. \n");
        return 1;
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    double r1 = atof(argv[3]);
    double r2 = atof(argv[4]);

    srand(time(NULL));

    char nome1[100], nome2[100];
    sprintf(nome1, "sfera%05d_%08.5f.txt", N, r1);
    sprintf(nome2, "sfera%05d_%08.5f.txt", M, r2);

    FILE *f1 = fopen(nome1, "w");
    FILE *f2 = fopen(nome2, "w");

    if (!f1 || !f2) {
        perror("Errore apertura file");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        struct point p = genera_punto(r1);
        fprintf(f1, "%lf %lf\n", p.x, p.y);
    }

    for (int i = 0; i < M; i++) {
        struct point p = genera_punto(r2);
        fprintf(f2, "%lf %lf\n", p.x, p.y);
    }

    fclose(f1);
    fclose(f2);

    printf("File generati:\n  %s\n  %s\n", nome1, nome2);
    return 0;
}