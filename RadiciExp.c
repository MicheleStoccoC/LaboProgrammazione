#include "stdio.h"
#include "math.h"

#define PI 3.14159
#define E 2.71828
#define EPS 1e-6

double L, M, N ;

//      LINEE DI TEST
#ifdef TEST
/*F*/
double F(double x){
    x=L*x*x+M*x+N ;
    return x ;
}
/*F'*/
double f(double x){
    x=2*L*x + M ;
    return x ;
}
//      FINE DI TEST
#else
/*FUNZIONE PRINCIPALE*/
double F(double x){
    x=pow(x,x)-(1/pow(E,x))-1 ;
    return x ;
}
/*DERIVATA PRIMA*/
double f(double x){
    x=pow(x,x)*(1+log(x))+1/pow(E,x) ;
    return x ;
}
#endif

/*ALGORITMI RADICI*/
double Bisez(double a, double b){
   double c, f_c ;
   c = (a+b)/2 ;
   f_c = F(c) ;
   while(fabs(b-a)>EPS){
        if(fabs(f_c)<=EPS){
        return c;
    }
    else{
        if(f_c>0){
            b=c ;
            return Bisez(a,b);
        }else{
            a=c ;
            return Bisez(a,b);
            }
        }
   }
   return 0;
}

double Newt(double O, double a, double b){
    double r=O-(F(O))/(f(O)) ;
    while(fabs(r-O)>EPS*fabs(r)){
        if(r<a || r>b){
            printf("Errore: uscita dall'intervallo di ricerca") ;
            break ;
        }
        O=r ;
        r=O-(F(O))/(f(O)) ;
    }
    return r;
}

        /* MAIN */
int main(){
    #ifdef TEST
    printf("Inserire parametri a, b e c della parabola: ") ;
    scanf("%lf %lf %lf", &L, &M, &N) ;
    #else
    L=0; 
    M=0; 
    N=0;
    #endif

    double m, n, Xo;
    double R=0. ;
    do{
        printf("Inserire gli estremi dell'intervallo tali per cui f_m<0 & f_M>0: ") ;
        scanf("%lf %lf", &m, &n) ;
    }while(F(m)>0 || F(n)<0) ;
    R = Bisez(m,n) ;
    printf("Radice con bisezione: %lf \n", R) ;

    R=0 ;

    do{
        printf("Inserire X0 nell'intervallo sopra definito: ") ;
        scanf("%lf", &Xo) ;
    }while(Xo<fmin(m,n) || Xo>fmax(m,n)) ;
    R = Newt(Xo, m, n);
    printf("Radice con Newton: %lf \n", R) ;

}