#include "header.h"

    /*  PARAMETRI COSMOLOGICI GLOBALI */

    /* PARAMETRI GLOBALI  */
const double UnitVel=2.0e7 ;            // cm/s (200km/s)
const double UnitMass=1.989e43 ;        // g  (e10 M_sun)
const double UnitLength=3.085678e21 ;   // cm (1 kpc)
const int N_pt=2048 ;             
const int N_grid=252 ;           
const double BoxL=10. ;                 // kpc
const double A_deltaPar=0.01 ;          // massimo scarto di densità concesso al contrasto delta

const double G=6.674e-8*UnitMass/(UnitLength*UnitVel*UnitVel) ;