#include "nrutil.h"

/* Costanti del codice */
#define NGRID 100       // Punti griglia
#define K 0.01          // cm^2/s
#define LDOMAIN 1.0     // Dominio dell'integrazione

/* Variabili globali per odeint */
extern int kount ;
extern float *xp, **yp ;

        /* FUNZIONI */
/* Derivata con griglia */
void derivataG(float t, float u[], float dudt[]){
    float dx=LDOMAIN/NGRID ;
    float A=K/(dx*dx) ;

    /* soluzione da file */
    for(int i=2; i<(NGRID); i++){
        dudt[i]=A*(u[i+1]-2*u[i]+u[i-1]) ;
    }
    /* CC Muro senza flusso */
    dudt[1]=A*(u[2]-u[1]) ;
    dudt[NGRID]=A*(u[NGRID-1]-u[NGRID]) ;

}


        /* MAIN */
int main(){

    int step ;
    float *u=vector(1,NGRID) ;

    float ti=0. ;
    float tf=5. ;
    float dt_snap=0.5 ;     // Ogni quanto si salva una "foto"
    float eps=1.e-5 ;
    float h1=0.0001 ;
    float hmin=0. ;
    int nok, nbad ;

    xp=NULL ; 
    yp=NULL ;

    /* Condizioni Iniziali */
    for(int i=1; i<(NGRID+1); i++){
        u[i]=0. ;
    }
    for(int i=45; i<56; i++){
        u[i]=1. ;
    }

    FILE *f1=fopen("InkDiff.txt", "w") ;
    if (f1==NULL){
        printf("apertura file fallita!") ;
        return 1 ;
    }

    float t=0. ;
    
    for(int i=1; i<(NGRID+1); i++){
        fprintf(f1, "%f\t%f\t%f\n", t, (i-0.5)*(LDOMAIN/NGRID), u[i]) ;
    }

    while(t<tf){
        float t_next=t+dt_snap ;
        
        odeint(u,NGRID,t,t_next,eps,h1,hmin,&nok,&nbad,derivataG,rkqs) ;
        
        t=t_next ;

        /* Salvataggio snapshot attuale */
        for(int i=1; i<(NGRID+1); i++){
            fprintf(f1, "%f\t%f\t%f\n", t, (i-0.5)*(LDOMAIN/NGRID), u[i]) ;
        }
    }

    fclose(f1) ;
    free_vector(u,1,NGRID) ;

    return 0;
}
