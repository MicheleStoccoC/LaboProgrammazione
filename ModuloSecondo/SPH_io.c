#include "SPH_rutil.h"

//FUNZIONI DI LETTURA/SCRITTURA

void set_IC(struct Particle *pts, int n_lz, int n_rz, double L_domain){
//Imposta le condizioni iniziali per le particelle
// particles: vettore di particelle
// n_lz-n_rz: numero di particelle a sinistra/destra rispettivamente
// L_domain: lunghezza tubo	
    int N=n_lz+n_rz ;

    //Zona 4 (sx): x<0 (high U)
    double rho4=1. ;
    double press4=1. ;
    double vel4=0. ;
    //Zona 1 (dx): x>0 (low U)
    double rho1=0.1 ;
    double press1=0.125 ;
    double vel1=0. ;

    //Energia interna
    double U4=press4/((GAMMA-1.)*rho4) ;
    double U1=press1/((GAMMA-1.)*rho1) ;
    
    //Zona 4 (sx)
	for(int i=0; i<n_lz; i++){
        pts[i].i=i; 
        pts[i].h=0.005 ;     //32.*L_domain/N
        pts[i].x=((double)i/n_lz)*L_domain*0.5 ;
        pts[i].v=vel4 ;
        pts[i].rho=rho4 ;
        pts[i].P=press4 ;
        pts[i].u=U4 ;
        pts[i].ax=0.;
        pts[i].au=0. ;
        pts[i].neigh_num=0 ;

    }
    //Zona 1 (dx)
    for(int i=0; i<n_rz; i++){
        int j=n_lz+i ;
        pts[j].i=j ;
        pts[j].h=0.005 ;        //32.*L_domain/N     
        pts[j].x =(1.+(double)i/n_rz)*L_domain*0.5 ;
        pts[j].v=vel1 ;
        pts[j].rho=rho1 ; 
        pts[j].P=press1 ; 
        pts[j].u=U1 ;
        pts[j].ax=0. ;
        pts[j].au=0. ;
        pts[j].neigh_num=0 ;
    }
}


void snap_time(struct Particle *pts, int N, int step){
//Funzione che, a tempi tipici, effettua uno snap della situazione
// particles: vettore di particelle
// n: numero di particelle
// step: step temporale in cui siamo

    char filename[64] ;
    sprintf(filename, "snapshot_%04d", step) ;
    FILE *fp = fopen(filename, "wb") ;
    if(!fp){
        perror("Failed to open file") ;
        exit(EXIT_FAILURE) ;
    }
    fwrite(pts, sizeof(struct Particle), N, fp) ;
    fclose(fp) ;
}

void snap_last(struct Particle *pts, int N){
//Funzione che, ad ogni step, effettua uno snap della situazione sovrascrivendo il precedente
// particles: vettore di particelle
// n: numero di particelle

    const char file[]="snap_last" ;
    FILE *fp=fopen(file, "wb") ;
    if (!fp) {
        perror("Failed to open file") ;
        exit(EXIT_FAILURE) ;
    }
    fwrite(pts, sizeof(struct Particle), N, fp) ;
    fclose(fp) ;	
}
