    /* INCLUDE GUARD */
#ifndef HEADER_H
#define HEADER_H

     // LIBRERIE UTILI
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"stdarg.h"
#include"fftw3.h"

    /* COSTANTI MATEMATICHE */
#define PI 3.1415926535
#define E 2.71828
    /* COSTANTI COSMOLOGICHE */
    /* PARAMETRI */
extern const double UnitVel ; 
extern const double UnitMass ;
extern const double UnitLength ;
extern const int N_pt ;             // number of mass points
extern const int N_grid ;           // FFT grid
extern const double BoxL ;          // Length of the box (in kpc)
extern const double A_deltaPar ;    // Maximum density contrast
extern const double G ;

    /* STRUTTURE */

    /* FUNZIONI */
double contrastD(double x) ;
double Kernel(double x) ;
double density(double m, double x[], double J, double dx) ;
void InitialConditions(double x[], double v[], FILE *f1) ;

void ComputePotential(double *Density, double *Pot, fftw_complex *kDensity, fftw_complex *kPot, fftw_plan fft_real_fwd, fftw_plan fft_real_bck) ;
void ComputeMeshForce(double *Pot, double MF[], double dx) ;
void ComputePartForce(double MF[], double PF[], double x[], double dx) ;

double MaxA(double Arr[], int N) ;

#endif