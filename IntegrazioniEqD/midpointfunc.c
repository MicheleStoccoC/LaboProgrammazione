#define NRANSI
#include "nrutil.h"


void midpointfunc(float y[], float dydx[], int n, float x, float h, float yout[], void (*derivata)(float, float [], float [])){
    int i ;
    float *ym, *dym ;
    ym=vector(1,n) ;
    dym=vector(1,n) ;

    for(i=1; i<=n; i++){
        ym[i]=y[i]+0.5*h*dydx[i] ;
    }

    (*derivata)(x+0.5*h,ym,dym) ;

    for(i=1; i<=n; i++){
        yout[i]=y[i]+h*dym[i] ;
    }

    free_vector(ym,1,n) ;
    free_vector(dym,1,n) ;
    
}
#undef NRANSI
/* (C) Copr. 1986-92 Numerical Recipes Software )!0,". */
