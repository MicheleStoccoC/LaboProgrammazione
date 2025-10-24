#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include "stdarg.h"

#define PI 3.14159
#define E 2.71828
#define EPS 1e-6


double (*function)(char *, ...) ;


        /*FUNZIONI*/
/*Quadra
double quad(double x, char *P, char *Q, char *R){
    x=atof(P)*x*x+atof(Q)*x+atof(R) ; // -1 2 1 ; m=3 n=1.5 ; R=2.414 c/a
    return x ;
}
*/
/*Quadra Variabile*/
double quad(char *fmt, ...) {
    va_list args ;
    va_start(args, fmt) ;

    double x=va_arg(args, double) ;
    char *P=va_arg(args, char *) ;
    char *Q=va_arg(args, char *) ;
    char *R=va_arg(args, char *) ;

    va_end(args) ;

    return atof(P)*x*x+atof(Q)*x+atof(R) ;
}

/*Cubica
double cube(double x, char *P, char *Q, char *R){
    x=x*x*x+x+1 ; // 0 0 0 ; m=-1 n=-0.1 ; R=-0.682 c/a
    return x ;
}
*/
double cube(char *fmt, ...) {
    va_list args ;
    va_start(args, fmt) ;

    double x=va_arg(args, double) ;
    va_end(args) ;

    return x*x*x+x+1 ;
}

/*Trascendendte I
double trascI(double x, char *P, char *Q, char *R){
    x=3*x-pow(E,x) ; // 0 0 0 ; m=2 n=1.2 ; R=1.512 c/a
    return x ;
}
*/
double trascI(char *fmt, ...) {
    va_list args ;
    va_start(args, fmt) ;

    double x=va_arg(args, double) ;
    va_end(args) ;

    return 3*x-pow(E, x) ;
}

/*Trascendente II
double trascII(double x, char *P, char *Q, char *R){
    x=pow(x,x)-(1/pow(E,x))-1 ; // 0 0 0 ; m=1 n=1.5 ; R=1.231 c/a
    return x ;
}
*/
double trascII(char *fmt, ...) {
    va_list args ;
    va_start(args, fmt) ;

    double x=va_arg(args, double) ;
    va_end(args) ;

    return pow(x, x)-(1/pow(E, x))-1 ;
}


        /*BISEZIONE*/
double Bisez(char *fmt, ...) {
    va_list args ;
    va_start(args, fmt) ;

    double a=va_arg(args, double) ;
    double b=va_arg(args, double) ;
    char *P=va_arg(args, char *) ;
    char *Q=va_arg(args, char *) ;
    char *R=va_arg(args, char *) ;

    va_end(args) ;

    double c, f_c ;
    c=(a+b)/2.0 ;
    f_c=function("%lf%s%s%s",c,P,Q,R) ;

    while (fabs(b-a)>EPS){
        if (fabs(f_c)<=EPS){
            return c ;
        }else{
            if(f_c>0){
                b=c ;
                return Bisez("%lf%lf%s%s%s",a,b,P,Q,R) ;
            }else{
                a=c ;
                return Bisez("%lf%lf%s%s%s",a,b,P,Q,R) ;
            }
            //Opzione non ricorsiva
            /*
            c=(a+b)/2.0 ;
            f_c=function("%lf%s%s%s",c,P,Q,R) ;
            */
        }
    }

    return c ;
}
/*double Bisez(double a, double b, char *P, char *Q, char *R){
   double c, f_c ;
   c = (a+b)/2 ;
   f_c = function("%lf%s%s%s",c, P, Q, R) ;
   while(fabs(b-a)>EPS){
        if(fabs(f_c)<=EPS){
        return c ;
    }
    else{
        if(f_c>0){
            b=c ;
            return Bisez(a,b,P,Q,R);
        }else{
            a=c ;
            return Bisez(a,b,P,Q,R);
            }
        }
   }
   return 0 ;
}*/



        /*MAIN*/
int main(int argc, char *argv[]){
    printf("Sono stati inseriti: %d argomenti\n", argc) ;
    
    // Scelta della funzione in base all'argomento
    if (strcmp(argv[1], "quad") == 0) {
        function = quad ;
        printf("E' stata selezionata la funzione: %s \n", argv[1]) ;
    } else if (strcmp(argv[1], "cube") == 0) {
        function = cube;
        printf("E' stata selezionata la funzione: %s \n", argv[1]) ;
    } else if (strcmp(argv[1], "trascI") == 0) {
        function = trascI;
        printf("E' stata selezionata la funzione: %s \n", argv[1]) ;
    }else if (strcmp(argv[1], "trascII") == 0) {
        function = trascII;
        printf("E' stata selezionata la funzione: %s \n", argv[1]) ;
    } else {
        printf("Funzione '%s' non riconosciuta.\n", argv[1]);
        printf("Avete a disposizione: 'quad','cube','trascI' e 'trascII'. \n");
        return 1;
    }

    char *p=argv[2], *q=argv[3], *r=argv[4] ;

    double m, n , R=0;
    do{
        printf("Inserire gli estremi dell'intervallo tali per cui f_m<0 & f_M>0: ") ;
        scanf("%lf %lf", &m, &n) ;
    }while(function("%lf%s%s%s",m,p,q,r)>0 || function("%lf%s%s%s",n,p,q,r)<0) ;
    R = Bisez("%lf%lf%s%s%s",m,n,p,q,r) ;
    printf("Radice con bisezione: %lf \n", R) ;

}
