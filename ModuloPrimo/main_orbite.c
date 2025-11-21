#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"stdarg.h"

    /* COSTANTI MATEMATICHE */
#define PI 3.1415926535
#define E 2.71828
    /* COSTANTI ASTROFISICHE */
char *end ;
#define GNEWT strtod("6.67e-11", &end) // Nm^2/kg^2
#define MSUN strtod("2.0e30", &end) // kg
#define UA strtod("1.5e11", &end) // m
#define VTER sqrt(GNEWT*MSUN/UA) // m/s
#define DAY 86400.0 // s
#define G GNEWT*MSUN*(DAY*DAY)/(UA*UA*UA)

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
double find_data(FILE *fd, const char *label) {
    char linea[100] ;   //Caratteri massimi della riga impostati a 100
    double val=-1.0 ;   // Valore di default in caso di errore

    fseek(fd, 0, SEEK_SET) ;  // Riavvolge il puntatore all'inizio del file per garantire una ricerca completa
    // Scansiona il file riga per riga
    while (fgets(linea, 100, fd) != NULL) {
        // Ignora le righe di commento e le righe vuote
        if (linea[0]=='#' || linea[0]=='\n' || linea[0]=='\r') {
            continue ;
        }
        // Controlla se la riga inizia con l'etichetta cercata
        if (strncmp(linea, label, strlen(label))==0) {
            //Estrai il valore numerico
            if (sscanf(linea, "%*s %lf", &val) == 1) {
                break ;
            }
        }
    }
    return val;
}

struct pianeta assegnazione(int n, FILE *fd) {
    struct pianeta temp ;
    char Asci[15] ;
    char Ordi[15] ;
    char Vel[15] ;
    sprintf(Asci, "Ascissa_%d", n) ;
    sprintf(Ordi, "Ordinata_%d", n) ;
    sprintf(Vel, "Velocita_%d", n) ;
    temp.posX=find_data(fd,Asci) ;
    temp.posY=find_data(fd,Ordi) ;
    temp.v=find_data(fd,Vel) ;
    temp.R=sqrt(temp.posX*temp.posX + temp.posY*temp.posY) ;
    temp.v=temp.v*VTER*DAY/UA ;
    temp.a=G/(temp.R*temp.R) ;
    return temp ;
}

struct pianeta components(struct pianeta P){
    P.vX=P.v*(P.posY/P.R) ; // sin()
    P.vY=P.v*(P.posX/P.R) ; // cos()
    P.aX=-P.a*(P.posX/P.R) ;
    P.aY=-P.a*(P.posY/P.R) ;
    return P ;
}

struct pianeta printPlanet(struct pianeta P){
    printf("Distanza, velocita' e accelerazione con rispettive componenti: \n") ;
    printf("%lf:\t(%lf ; %lf) (%lf ; %lf) (%lf ;%lf) \n", cos(atan(P.posY/P.posX)), P.posX, P.posY, P.vX, P.vY, P.aX, P.aY) ;
    return P;
}

struct pianeta transcribe(struct pianeta P, FILE *f1){
    fprintf(f1, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", P.posX*UA, P.posY*UA,P.R*UA, P.vX*(UA/DAY), P.vY*(UA/DAY), P.aX*(UA/(DAY*DAY)), P.aY*(UA/(DAY*DAY))) ;
    return P ;
}

void Eulero(struct pianeta *P, double dt, FILE *f1){
    P->posX+=P->vX*dt ;
    P->posY+=P->vY*dt ;
    //P->R=sqrt(P->posY*P->posY+P->posX*P->posX) ;
    P->vX+=P->aX*dt ;
    P->vY+=P->aY*dt ;
    P->aX=-P->a*(P->posX/P->R) ;
    P->aY=-P->a*(P->posY/P->R) ;
    //P->a=sqrt(P->aY*P->aY+P->aX*P->aX) ;
    transcribe(*P, f1) ;
}


        /* MAIN */
int main(){
    int N=1 ;
    printf("Quanti pianeti vuoi modellare? \n") ;
    scanf("%d", &N) ;

    struct pianeta *lista_pianeti ; // Puntatore a un array di strutture
    lista_pianeti = (struct pianeta *)malloc(N*sizeof(struct pianeta)) ; // Allocazione di memoria per l'array di strutture
    // Controllo del successo di allocazione 
    if (lista_pianeti == NULL) {
        printf("Errore nell'allocazione di memoria.\n") ;
        return 1 ;
    }
    // TUTTOOOO!!!
    char nome1[100] ;
    for (int i=0; i<N; i++) {
        FILE *fd = fopen("data.txt","r") ;
        lista_pianeti[i] = assegnazione(i+1,fd) ;
        fclose(fd) ;
        lista_pianeti[i]=components(lista_pianeti[i]) ;
        sprintf(nome1, "Pianeta_%d.txt", i+1) ;
        FILE *f1 = fopen(nome1, "w") ;
        if (!f1) {
        perror("Errore apertura file") ;
        return 1 ;
        }
        for(int j=0; j<3400; j++){
        Eulero(&lista_pianeti[i],0.2,f1) ;
        }
        fclose(f1) ;
    }
    // Deallocazione
    free(lista_pianeti) ;

    return 0;
}


