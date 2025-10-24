#include <stdio.h>
#include <math.h>

/*VOID SCANF*/
void inputcoeff(double *p,double *q,double *r){
    scanf("%lf %lf %lf", p, q, r);
}


int main() {
    double a, b, c, X[2];
    double delta;
    //double *A=&a, *B=&b, *C=&c ;      cosi' alloco piu' memoria.

    printf("Inserire i parametri a, b, c: ");
    inputcoeff(&a,&b,&c);

    delta = b*b - 4*a*c;

    if (delta < 0) {
        printf("L'equazione non ha soluzioni reali.\n");
    } else {
        X[0] = (-b + sqrt(delta)) / (2*a);
        X[1] = (-b - sqrt(delta)) / (2*a);
        printf("Le radici sono: %lf e %lf\n", X[0], X[1]);
    }

    return 0;
}
