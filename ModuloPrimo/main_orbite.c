#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include "stdarg.h"

    /* COSTANTI MATEMATICHE */
#define PI 3.14159
#define E 2.71828
    /* COSTANTI ASTROFISICHE */
char *end ;
#define GNEWT strtod("6.67e-11", &end)
#define MSUN strtod("2.0e33", &end)
#define VTER 100.0
#define UA strtod("1.5e8", &end)

    /* STRUTTURE */
struct pianeta{
    double R ;
    double posX ;
    double posY ;
    double v ;
    double vX ;
    double vY ;
    double a ;
    double aX ;
    double aY ;
} ;

    /* FUNZIONI */
struct pianeta assegnazione(int n) {
    struct pianeta temp ;
    printf("Immettere l'ascissa del pianeta %d rispetto al Sole, in unita' astronomiche: \n", n) ;
    scanf("%lf", &temp.posX) ;
    printf("Immettere l'ordinata del pianeta %d rispetto al Sole, in unita' astronomiche: \n", n) ;
    scanf("%lf", &temp.posY) ;
    printf("Immettere il modulo della velocita' tangenziale del pianeta %d, in unita' terrestri: \n", n) ;
    scanf("%lf", &temp.v) ;
    temp.R=sqrt(temp.posX*temp.posX + temp.posY*temp.posY) ;
    temp.a=(GNEWT*MSUN)/(temp.R*UA*temp.R*UA) ;
    return temp ;
}

struct pianeta components(struct pianeta P){
    double theta=atan(P.posY/P.posX) ;
    P.vX=P.v*cos(theta) ;
    P.vY=P.v*sin(theta) ;
    P.aX=P.a*cos(theta) ;
    P.aY=P.a*sin(theta) ;
    return P ;
}

struct pianeta printPlanet(struct pianeta P){
    printf("Distanza, velocita' e accelerazione con rispettive componenti: \n") ;
    printf("%lf: (%lf ; %lf) \n%lf: (%lf ; %lf) \n%lf: (%lf ;%lf) \n", P.R, P.posX, P.posY, P.v, P.vX, P.vY, P.a, P.aX, P.aY) ;
    return ;
}

    /* MAIN */
int main(){
    int N=1 ;
    double G=GNEWT*MSUN/(UA*UA*UA) ;
    printf("Quanti pianeti vuoi modellare? \n") ;
    scanf("%d", &N) ;
    printf("G in unita' di UA e M_sun: %lf \n", G) ;

    /*
    struct pianeta *lista_pianeti ; // Puntatore a un array di strutture
    lista_pianeti = (struct pianeta *)malloc(N*sizeof(struct pianeta)) ; // Allocazione di memoria per l'array di strutture
    // Controllo del successo di allocazione 
    if (lista_pianeti == NULL) {
        printf("Errore nell'allocazione di memoria.\n") ;
        return 1 ;
    }
    // Inizializzazione strutture
    for (int i=0; i<N; i++) {
        lista_pianeti[i] = assegnazione(i+1) ;
    }
    // Dovrei scriverle da qualche parte
    // Deallocazione
    free(lista_pianeti) ;
    */
    
    struct pianeta Terra=assegnazione(N) ;
    Terra=components(Terra) ;
    printPlanet(Terra) ;

    return 0;
}
