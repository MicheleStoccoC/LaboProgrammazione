#include "nrutil.h"

    /* COSTANTI */
#define PI 3.14159
#define E 2.71828
    /* COST ASTROFISICHE */
#define C 0.02
#define RHO 10.0
#define TG 1.5
/* Variabili globali per odeint */
extern int kmax, kount ;
extern float *xp, **yp, dxsav ;


    /* FUNZIONI */
double rholin(){
    return C*RHO/TG ;
}

double rhopar(double t, double R){
    return (C*R/TG)*t ;
}

double exact(double t, double R){
    return 0.5*(C*R/TG)*t*t ;
}

void derivata(float t, float y[], float dydt[]){
#ifdef RHO_CONST
    double R=RHO ;
#else
    double R=RHO-y[1] ;
#endif

    if(t>=2*TG){
        dydt[1]=0. ;
    }else{
        dydt[1]=rhopar(t,R) ;
    }

}


    /* MAIN */
int main(){
    float *ystart=vector(1,1) ;
    float ti, tf ;
    float eps=1.e-4 ;       
    float hi=0.1 ;
    float hmin=0. ;
    int nok, nbad ;

    ti=0. ;
    tf=3.5 ;

    kmax=200 ;
    xp=vector(1,kmax) ;
    yp=matrix(1,1,1,kmax) ;

    ystart[1]=0.0 ;
    odeint(ystart,1,ti,tf,eps,hi,hmin,&nok,&nbad,derivata,rkqs) ;

    FILE *f=fopen("rho_adaptive.txt","w") ;
    if (f==NULL){
        printf("apertura file fallita!") ;
        return 1 ;
    }
    for(int i=1; i<=kount; i++){
        fprintf(f, "%f\t%f\t%f\t%f\n", xp[i], RHO, yp[1][i], exact(xp[i], RHO)) ;
    }

    free_vector(ystart,1,1) ;
    free_vector(xp,1,kmax) ;
    free_matrix(yp,1,1,1,kmax) ;

    return 0 ;
}
