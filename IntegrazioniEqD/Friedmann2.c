#include "nrutil.h"

    /* COSTANTI */
#define PI 3.14159
#define E 2.71828
    /* COST ASTROFISICHE */
#define GNEWT 6.67e-11
#define U_SPACE 3.086e19     // km (1Mpc)
#define LIGHT 2.99792e5     // km/s

/* Variabili globali per odeint */
extern int kmax, kount ;
extern float *xp, **yp, dxsav ;
/* Variabili globali del codice */
float H0, O_m, w_EoS, O_DE, O_k ;

    /* FUNZIONI */
// Quelle di integrazione sono incluse dai file esterni attraverso il Makefile

void derivata(float t, float y[], float dydt[]){
    float a=y[1] ;
    // per calcolare da/dt prendiamo l aseconda eq di friedmann e ne facciamo la radice
    float K=O_k ;
    float M=O_m/a ;
    float DE=O_DE*pow(a,(-1-3*w_EoS)) ;
    float Ez=sqrt(M+K+DE) ;
    float h0=H0/U_SPACE ;

    dydt[1]=h0*Ez ;

}

    /* MAIN */
int main(int argc, char *argv[]){

    if(argc<4){
        printf("ERRORE: Utilizzo errato, argc troppo pochi \n") ;
        printf("\t Utilizzo corretto: <eseguibile> <H0> <Omega Matter> <omega EoS> <Omega DE>") ;
        exit(-1) ;
    }

    clock_t Tstart, Tend ;

    H0=atof(argv[1]) ;          // km/s/Mpc
    float h0=h0=H0/U_SPACE ;    // 1/s
    O_m=atof(argv[2]) ;
    w_EoS=atof(argv[3]) ;
    O_DE=atof(argv[4]) ;
    O_k=1.-O_m-O_DE ;

    float *a, *dadt ;
    a=vector(1,1) ;
    dadt=vector(1,1) ;
    
    float zi, zf, ai, af, ti, tf ;
    zi=100. ;
    zf=0. ;
    ai=1./(1.+zi) ;
    af=1. ;
    ti=0. ;
    tf=1./h0 ;

    a[1]=ai ;

    // Parametri per odeint
    float eps=1.0e-4 ; 
    float h1=tf/10000. ; 
    float hmin=0. ;   
    int nok, nbad ;

    // Variabili globali in odeint.c
    kmax=1000 ;                     // Numero max di punti salvati
    dxsav=tf/200. ;   // Intervallo per il  salvataggio
    xp=vector(1,kmax) ;
    yp=matrix(1,1,1,kmax) ;

    printf("\t Inizio integrazione della cosmologia: H0=%.1f O_m=%.2f O_DE=%.2f O_k=%.2f w_EoS=%.1f\n", H0, O_m, O_DE, O_k, w_EoS) ;

    /* Adaptive TimeStep */
    float h=h1 ;
    float *yscal ; 
    yscal=vector(1,1) ;
    FILE *f1=fopen("Fried_adaptive.txt", "w") ;
    if (f1==NULL){
        printf("apertura file fallita!") ;
        return 1 ;
    }
    float t=ti ;
    float hdid, hnext ;

    Tstart=clock() ;
    odeint(a,1,ti,tf,eps,h1,hmin,&nok,&nbad,derivata,rkqs) ;
    Tend=clock() ;
	double Ttot=((double)(Tend-Tstart))/CLOCKS_PER_SEC ;
    printf("Tempo impiegato ad integrare il sistema con adaptive: %lf sec \n", Ttot) ;

    for(int i=1; i<=kount; i++){
        fprintf(f1, "%e\t%f\n", xp[i]/3.154e16, yp[1][i]) ;    // Tempo in Gyr
    }
    fclose(f1) ;
    /* END */

    /* Midpoint Integration */
    a[1]=ai ;
    t=ti ;
    h=h1*10. ;

    FILE *f2=fopen("Fried_midpoint.txt", "w") ;

    float *yout=vector(1,1) ;
    Tstart=clock() ;
    while(a[1]<af){
        derivata(t,a,dadt) ;
        midpointfunc(a,dadt,1,t,h,yout,derivata) ;

        t += h;
        a[1]=yout[1] ;
        
        fprintf(f2, "%e\t%f\n", t/3.154e16, a[1]) ;
    }
    Tend=clock() ;
	Ttot=((double)(Tend-Tstart))/CLOCKS_PER_SEC ;

    fclose(f2) ;
    free_vector(yout,1,1) ;

    printf("Tempo impiegato ad integrare il sistema con midpoint: %lf sec \n", Ttot) ;
    /* END */

    free_vector(a,1,1) ;
    free_vector(dadt,1,1) ;
    free_vector(yscal,1,1) ;
    free_vector(xp,1,kmax) ;
    free_matrix(yp,1,1,1,kmax) ;

    printf("\a");
    fflush(stdout);

    return 0 ;

}
