#include "header.h"

char *end ; 

        /* MAIN */
int main(int argc, char *argv[]){
    double M_star=strtod(argv[1], &end) ;
    int N=atoi(argv[2]) ;
    double dt=strtod(argv[3], &end) ;
    double G=GNEWT*M_star*(YEAR*YEAR)/(UA*UA*UA) ;
    double T ;
    int steps ;

    struct pianeta *lista_pianeti ; // Puntatore a un array di strutture
    lista_pianeti = (struct pianeta *)malloc(N*sizeof(struct pianeta)) ; // Allocazione di memoria per l'array di strutture
    // Controllo del successo di allocazione 
    if (lista_pianeti == NULL) {
        printf("Errore nell'allocazione di memoria.\n") ;
        return 1 ;
    }
    // TUTTOOOO!!!
    char nome1[100] ;
    FILE *fd ;
    fd = fopen("DATA.txt","r") ;
    
    char farD[15] ;
    double farV ;
#ifndef TRAPPIST
    sprintf(farD, "Sole_%d", N) ;
#else
    sprintf(farD, "Trap_%d", N) ;
#endif
    double D=find_data(fd,farD) ;
    printf("%lf\n",D) ;
    farV= sqrt(GNEWT*M_star/(D*UA)) ;
    printf("%lf\n",farV) ;
    T=((2*PI*D*UA)/farV)/YEAR ;
    printf("%lf\n",T) ;
    steps=T/dt ;
    printf("%d\n",steps) ;
    for (int i=0; i<N; i++){
        lista_pianeti[i] = assegnazione(i+1,G,M_star,fd) ;
        lista_pianeti[i]=components(lista_pianeti[i]) ;
        sprintf(nome1, "Pianeta_%d.bin", i+1) ;
        FILE *f1 = fopen(nome1, "wb") ;
        if (!f1) {
        perror("Errore apertura file") ;
        return 1 ;
        }
        for(int j=0; j<steps; j++){
        Eulero(&lista_pianeti[i],dt,j,f1) ;
        }
        fclose(f1) ;
    }
    fclose(fd) ;
    // Deallocazione
    free(lista_pianeti) ;

    return 0 ;
}
