    /* INCLUDE GUARD */
#ifndef HEADER_H
#define HEADER_H

     // LIBRERIE UTILI
#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"string.h"
#include"stdarg.h"

    /* COSTANTI MATEMATICHE */
#define PI 3.1415926535
#define E 2.71828
    /* COSTANTI ASTROFISICHE */
extern const double GNEWT ;
extern const double MSUN ;
extern const double UA ;
extern const double YEAR ;
extern const double VTER ;

    /* STRUTTURE */
struct pianeta{
    double time ;
    double R ;
    double posX ;
    double posY ;
    double v ;
    double vX ;
    double vY ;
    double a ;
    double aX ;
    double aY ;
} ;


    /* FUNZIONI */
double find_data(FILE *fd, const char *label) ;

struct pianeta assegnazione(int n, double G, double M, FILE *fd) ;

struct pianeta components(struct pianeta P) ;

struct pianeta printPlanet(struct pianeta P) ;

struct pianeta transcribe(struct pianeta *P, FILE *f1) ;

void Eulero(struct pianeta *P, double dt, int n, FILE *f1) ;


#endif 