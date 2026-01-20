#include "SPH_qrutil.h"

/* Compara le posizioni di due struct particelle (a,b) */
int cmp_part(const void *a, const void *b){

    if(((struct Particle *)a)->x < ((struct Particle *)b)->x){
        return -1 ;
    }
    if(((struct Particle *)a)->x > ((struct Particle *)b)->x){
        return 1 ;
    }

    return 0 ;
}

/* Quicksearch */
double quicksearch(struct Particle *p, int N, double L_domain){
    qsort(p, N, sizeof(struct Particle), cmp_part) ;
    double Hmax ;
    int NeighN=64 ;
    int halfN=32 ;

    if(N-1<NeighN){
        fprintf(stderr, "ERRORE: esistono meno di 64 vicini.\n");
        exit(EXIT_FAILURE) ;
    }

    for(int i=0; i<N; i++){
        p[i].neigh_num=0 ; 

        for(int j=-halfN; j<=halfN; j++){
            if(j==0){
                continue ;
            }
            int iNeigh=(i+j+N)%N ;
            // evitare che la periodicità disturbi il tubo
            double d=distance(p[i],p[iNeigh],L_domain) ;
            if(fabs(d)>L_domain*0.45){
                continue ;
            }
            //
            p[i].neighbors[p[i].neigh_num]=iNeigh ;
            p[i].neigh_num++ ;
        }
        // H adattivo 
        int i_dx=(i+halfN+N)%N ;
        int i_sx=(i-halfN+N)%N ;
        double Ddx=fabs(distance(p[i],p[i_dx],L_domain)) ;
        double Dsx=fabs(distance(p[i],p[i_sx],L_domain)) ;
        double D=Ddx ;
        if(Dsx>Ddx){
            D=Dsx ;
        }
        p[i].h=D*0.5 ;
        if(p[i].h>Hmax){
            Hmax=p[i].h ;
        }
    }
    //Nota: p.neighbors salva gli indici della nuova configurazione
    return Hmax ;
}