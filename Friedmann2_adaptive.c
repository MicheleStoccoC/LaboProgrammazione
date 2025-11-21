#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <nrutil.h>
#include <nr.h>

    /* COSTANTI */
#define PI 3.14159
#define E 2.71828
    /* COST ASTROFISICHE */
char *end ;
#define GNEWT strtod("6.67e-11", &end)
#define LIGHT strtod("2.99792e5", &end) // km/s
#define H0 70.0 // km/s/Mpc
#define OM_M 0.3
#define OM_R 0.0
#define OM_L 0.7
/* Dopo questi verranno inseriti da riga di comando ma ora sono piu' utili cosi' */

    /* FUNZIONI */
void odeint(double ystart[], int nvar, double x1, double x2, double eps, double h1, double hmin, 
    int *nok, int *nbad, void (*derivs)(double, double[], double[]), 
    void (*rkqs)(double [], double [], int, double *, double, double, double [], 
    double *, double *, void (*)(double, double [], double []))) ;

void derivs(double t, double y[], double dadt[]) {
    double a = y[1] ;
    double v = y[2] ;

    dadt[1] = v;

    dadt[2] = -0.5 * H0 * H0 * (OM_M / (a*a) + 2.0 * OM_R / (a*a*a) - 2.0 * OM_L * a) ;
}


    /* MAIN */
int main(){}