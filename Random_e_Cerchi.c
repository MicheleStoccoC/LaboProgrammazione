#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
#define E 2.71828

    /* STRUTTURE */
    struct point {
#ifndef THREE_DIM
    double R ;
    double phi ;
#else 
    double R ;
    double phi ;
    double theta ;
#endif
};

    /* FUNZIONI */
struct point genera_punto(double r, FILE *f1) {
#ifndef THREE_DIM
    struct point temp;
    temp.R= (double)rand()/RAND_MAX*r ;
    temp.phi=((double)rand()/RAND_MAX)*2.0*PI ;
    fprintf(f1, "%lf\t%lf\n", temp.R*cos(temp.phi), temp.R*sin(temp.phi)) ;
#else
    struct point temp;
    temp.R= (double)rand()/RAND_MAX*r ;
    temp.phi=((double)rand()/RAND_MAX)*2.0*PI ;
    temp.theta=acos((double)rand()/RAND_MAX*2.0-1.0) ;
    fprintf(f1, "%lf\t%lf\t%lf\n", temp.R*sin(temp.theta)*sin(temp.phi), temp.R*sin(temp.theta)*cos(temp.phi), temp.R*cos(temp.theta)) ;
#endif
    return temp ;
}

struct point genera_punto_unif(double r, FILE *f2) {
#ifndef THREE_DIM
    struct point temp;
    temp.R= sqrt((double)rand()/(RAND_MAX+1.0))*r ;
    temp.phi=2*PI*((double)rand()/(RAND_MAX+1.0)) ;
    fprintf(f2, "%lf\t%lf\n", temp.R*cos(temp.phi), temp.R*sin(temp.phi)) ;
#else
    struct point temp;
    temp.R= sqrt((double)rand()/(RAND_MAX+1.0))*r ;
    temp.phi=2*PI*((double)rand()/(RAND_MAX+1.0)) ;
    temp.theta=acos((double)rand()/(RAND_MAX+1.0)*2.0-1.0) ;
    fprintf(f2, "%lf\t%lf\t%lf\n", temp.R*sin(temp.theta)*sin(temp.phi), temp.R*sin(temp.theta)*cos(temp.phi), temp.R*cos(temp.theta)) ;
#endif
    return temp ;
}

void genera_sfera1(double r, int N, FILE *f1){
    for (int i = 0; i < N; i++) {
        struct point p = genera_punto(r, f1) ;
    }
}

void genera_sfera2(double r, int N, FILE *f2){
    for (int i = 0; i < N; i++) {
        struct point p = genera_punto_unif(r, f2) ;
    }
}

    /* MAIN */
int main(){
    int N ;
    double r1, r2 ;

    printf("Inserisci il numero di punti da generare (max 9999): ") ;
    scanf("%d", &N) ;
    printf("Inserisci il raggio della sfera 1 (max 999): ") ;
    scanf("%lf", &r1) ;
    printf("Inserisci il raggio della sfera 2 (max 999): ") ;
    scanf("%lf", &r2) ;

    srand(time(NULL)) ;

    char nome1[100], nome2[100];
#ifndef THREE_DIM
    sprintf(nome1, "2Dsphere_1_%04d_%04.1f.txt", N, r1) ;
    sprintf(nome2, "2Dsphere_2_%04d_%04.1f.txt", N, r2) ;
#else
    sprintf(nome1, "3Dsphere_1_%04d_%04.1f.txt", N, r1) ;
    sprintf(nome2, "3Dsphere_2_%04d_%04.1f.txt", N, r2) ;
#endif

    FILE *f1 = fopen(nome1, "w") ;
    FILE *f2 = fopen(nome2, "w") ;

    if (!f1 || !f2) {
        perror("Errore apertura file") ;
        return 1 ;
    }

    genera_sfera1(r1, N, f1) ;
    genera_sfera2(r2, N, f2) ;

    fclose(f1);
    fclose(f2);

    printf("File con coordinate cartesiane e distribuzione lineare:\n  %s\n", nome1) ;
    printf("File con coordinate cartesiane e distribuzione uniforme:\n  %s\n", nome2) ;
    return 0;
}