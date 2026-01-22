#include "nrutil.h"

    /* COSTANTI */
#define PI 3.14159
#define E 2.71828
    /* COST ASTROFISICHE */
#define C 0.02
#define RHO 10.0
#define TG 1.5


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

double midpoint(double h, double k1, double k2, double t, double y, FILE *f2){
#ifdef RHO_CONST
    double R=RHO ;
#else
    double R=RHO-y ;
#endif
    if(t>=2*TG){
        return 0 ;
    }else{
        k1=rhopar(t, R) ;
        k2=rhopar(t+0.5*h, R) ;
        y=y+h*k2 ;
        fprintf(f2, "%g %g %g %g\n", t+h, R, y, y-exact(t+h, R)) ;
        t=t+h ;
        return midpoint(h, k1, k2, t, y, f2) ;
    }
}


    /* MAIN */
int main(){
    int N ;
    double h ;
    printf("Inserire numero di timesteps: ") ;
    scanf("%d", &N) ;

    h=2*TG/N ;

    FILE *f2 = fopen("rho_midpoint.txt","w") ;
    if (f2 == NULL){
        printf("apertura file fallita!") ;
        return 1 ;
    }

    double k1=0, k2=0, y=0 ;
    double t=0 ;
    fprintf(f2, "%lf\t%lf\t%lf\t%lf\n", t, RHO, y, exact(t, RHO)) ;
    midpoint(h,k1,k2,t,y,f2) ;

    fclose(f2) ;

    return 0 ;
}
