#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COSTANTI

#define FINAL_TIME 0.2		//Tempo finale 
#define GAMMA 1.4           	//Indice Adiabatico
#define alpha 1.0		//Servono per calcolo di elemento
#define beta 2.0		//di viscosita' aggiunto a mano
#define EPSILON 0.01		//Costante per evitare problemi numerici
#define K 0.1			//Costante per il calcolo del passo temporale 
#define M 0.000125          	//Massa 


// STRUTTURE

struct nlist{
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

#ifndef _NR_UTILS_H_
#define _NR_UTILS_H_

typedef struct Particle{
    int i;
    double h;
    double x;
    double v;
    double rho;
    double P;
    double u;
    double ax;
    double au;
    int neigh_num;
    int neighbors[120];
};

static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

static double dsqrarg;
#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg)

static double dmaxarg1,dmaxarg2;
#define DMAX(a,b) (dmaxarg1=(a),dmaxarg2=(b),(dmaxarg1) > (dmaxarg2) ?\
        (dmaxarg1) : (dmaxarg2))

static double dminarg1,dminarg2;
#define DMIN(a,b) (dminarg1=(a),dminarg2=(b),(dminarg1) < (dminarg2) ?\
        (dminarg1) : (dminarg2))

static float maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
        (maxarg1) : (maxarg2))

static float minarg1,minarg2;
#define FMIN(a,b) (minarg1=(a),minarg2=(b),(minarg1) < (minarg2) ?\
        (minarg1) : (minarg2))

static long lmaxarg1,lmaxarg2;
#define LMAX(a,b) (lmaxarg1=(a),lmaxarg2=(b),(lmaxarg1) > (lmaxarg2) ?\
        (lmaxarg1) : (lmaxarg2))

static long lminarg1,lminarg2;
#define LMIN(a,b) (lminarg1=(a),lminarg2=(b),(lminarg1) < (lminarg2) ?\
        (lminarg1) : (lminarg2))

static int imaxarg1,imaxarg2;
#define IMAX(a,b) (imaxarg1=(a),imaxarg2=(b),(imaxarg1) > (imaxarg2) ?\
        (imaxarg1) : (imaxarg2))

static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\
        (iminarg1) : (iminarg2))

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

#if defined(__STDC__) || defined(ANSI) || defined(NRANSI) /* ANSI */

//FUNZIONI RICERCA VICINI 
int cmp_part(const void *a, const void *b) ;
double quicksearch(struct Particle *p, int N, double L_domain) ;


// FUNZIONI FISICHE/CALCOLO
double distance(struct Particle a, struct Particle b, double L_domain);
double kernel(double r, double h);
double kern_der(double r, double h);
void ComputeXLR8(struct Particle *p, int N, double L_domain);
void ComputeDensPress(struct Particle *p, int N, double L_domain);
double ComputeViscosity(struct Particle a, struct Particle b, double L_domain);
double ComputeTimeStep(struct Particle *p, int N, double h);
void KDK(struct Particle *p, int n, double dt, double h, double L_domain);

// FUNZIONI INPUT/OUTPUT

void snap_time(struct Particle *p, int n, int step);
void snap_last(struct Particle *p, int n);
void set_IC(struct Particle *p, int n_lz, int n_rz, double L_domain);

// FUNZIONI CREAZIONE/LIBERAZIONE MEMORIA

void nrerror(char error_text[]);
float *vector(long nl, long nh);
int *ivector(long nl, long nh);
unsigned char *cvector(long nl, long nh);
unsigned long *lvector(long nl, long nh);
double *dvector(long nl, long nh);
float **matrix(long nrl, long nrh, long ncl, long nch);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
int **imatrix(long nrl, long nrh, long ncl, long nch);
float ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_pvector(struct Particle *p, long nl, long nh);
void free_vector(float *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
void free_cvector(unsigned char *v, long nl, long nh);
void free_lvector(unsigned long *v, long nl, long nh);
void free_dvector(double *v, long nl, long nh);
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch, long ndl, long ndh);

#else /* ANSI */
/* traditional - K&R */
int cmp_part();
double quicksearch();
double distance();
double kernel();
double kern_der();
void ComputeXLR8();
void ComputeDensPress();
double ComputeViscosity();
double ComputeTimeStep();
void KDK();
void snap_time();
void snap_last();
void set_IC();
int get_units();
void nrerror();
float *vector();
int *ivector();
unsigned char *cvector();
unsigned long *lvector();
double *dvector();
float **matrix();
double **dmatrix();
int **imatrix();
float **submatrix();
float **convert_matrix();
float ***f3tensor();
void dealloL();
void free_pvector();
void free_Livector();
void free_vector();
void free_ivector();
void free_cvector();
void free_lvector();
void free_dvector();
void free_matrix();
void free_submatrix();
void free_convert_matrix();
void free_dmatrix();
void free_imatrix();
void free_f3tensor();

#endif /* ANSI */

#endif /* _NR_UTILS_H_ */
