#include "header.h"

    /* FUNZIONI */
    
double find_data(FILE *fd, const char *label) {
    char linea[100] ;   // Caratteri massimi della riga impostati a 100
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

struct pianeta assegnazione(int n, double G, double M, FILE *fd){
    struct pianeta temp ;
    char Dist[15] ;
#ifndef TRAPPIST
    sprintf(Dist, "Sole_%d", n) ;
#else
    sprintf(Dist, "Trap_%d", n) ;
#endif
    temp.posX=find_data(fd,Dist) ;
    temp.posY=0 ;
    temp.R=sqrt(temp.posX*temp.posX + temp.posY*temp.posY) ;
    temp.v=sqrt(GNEWT*M/(temp.posX*UA)) ;
    temp.v=temp.v*YEAR/UA ;
    temp.a=G/(temp.R*temp.R) ;
    temp.time=0 ;
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

struct pianeta transcribe(struct pianeta *P, FILE *f1){
    double temp[7]={P->time, P->posX, P->posY, P->vX, P->vY, P->aX, P->aY} ;
    fwrite(temp, sizeof(double), 7, f1) ;
    return *P ;
}

void Eulero(struct pianeta *P, double dt, int n, FILE *f1){
    P->time=dt*n ;
    P->posX+=P->vX*dt ;
    P->posY+=P->vY*dt ;
    P->R=sqrt(P->posY*P->posY+P->posX*P->posX) ;
    P->aX=-P->a*(P->posX/P->R) ;
    P->aY=-P->a*(P->posY/P->R) ;
    P->a=sqrt(P->aY*P->aY+P->aX*P->aX) ;
    P->vX+=P->aX*dt ;
    P->vY+=P->aY*dt ;
    transcribe(P,f1) ;
}

