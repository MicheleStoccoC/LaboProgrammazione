#include "header.h"

    /* STRUTTURE */
typedef struct {
    double t;
    double x;
    double y;
    double vx;
    double vy;
    double ax;
    double ay;
}transfer ;

    /* MAIN */
int main(int argc, char *argv[]){
    int N=atoi(argv[1]) ;
    int J=atoi(argv[2]) ;
    long sizeT=sizeof(transfer) ;
    long jump=sizeT*J ; //Ogni J+1 time-steps viene trascritto il file
    char nome1[100] ;
    char nome2[100] ;
    for(int i=1; i<N+1; i++){
        sprintf(nome1, "Pianeta_%d.bin", i) ;
        sprintf(nome2, "Pianeta_%d.txt", i) ;
        FILE *f1 = fopen(nome1, "rb") ;
        FILE *f2 = fopen(nome2, "w") ;
        if (!f1 || !f2) {
        perror("Errore apertura file") ;
        return 1 ;
        }
        transfer T ;
        while (fread(&T, sizeT, 1, f1) == 1) {
        fprintf(f2, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", T.t, T.x*UA, T.y*UA, T.vx*(UA/YEAR), T.vy*(UA/YEAR), T.ax*(UA/(YEAR*YEAR)), T.ay*(UA/(YEAR*YEAR))) ;
        fseek(f1, jump, SEEK_CUR) ;
    }

    fclose(f1) ;
    fclose(f2) ;
    }

    return 0;
}