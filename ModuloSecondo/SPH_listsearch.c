#include "SPH_rutil.h"

double Hmax(struct Particle *p, int N){
//Trova il massimo tra le h
// p: vettore di particelle
// n: numero di particelle

    double hmax=-1. ;
    for(int i=0; i<N; i++){
        if(p[i].h>hmax){
            hmax=p[i].h ;
        }
    }
    return hmax ;
}

int cmp_pair(const void *a, const void *b){
//Determina la relazione tra due elementi di tipo Pair per riordinarli

    double diff=((struct Pair*)a)->d - ((struct Pair*)b)->d ;
    int cmp=(diff>0)-(diff<0) ;
    return cmp ;
}

void di_sort(double *d, int *idx, int N){
//Ordina l'array d ed i rispettivi indici in ordine di distanza crescente
// d: array distanze
// idx; array di indici
// N: dimensione degli array

    struct Pair *arr=malloc(N*sizeof(struct Pair)) ;
    if(!arr){
        fprintf(stderr, "Errore: memoria insufficiente per allocare l'array di coppie.\n") ;
        exit(EXIT_FAILURE) ;
    }

    for(int i=0; i<N; i++){
        arr[i].d=d[i] ;
        arr[i].idx=idx[i] ;
    }

    qsort(arr,N,sizeof(struct Pair),cmp_pair) ;

    for(int i=0; i<N; i++){
        d[i]=arr[i].d ;
        idx[i]=arr[i].idx ;
    }

    free(arr) ;
}


void makelist(struct Particle *p, struct Particle **Griglia, int N, double dc, int Ncelle){
    
    for(int i=0; i<Ncelle; i++){
        Griglia[i]=NULL ;
    }

    for(int i=0; i<N; i++){
        int icell=(int)(p[i].x/dc) ;
        if(icell>=Ncelle){
            icell=Ncelle-1 ;
        }
        if(icell<0){
            icell=0 ;
        }
        p[i].next=Griglia[icell] ;
        Griglia[icell]=&p[i] ;
    }

}

/* Listsearch */
double listsearch(struct Particle *p, int N, double L_domain){
// p: vettore di particelle
// n: numero di particelle
// L_domain: lunghezza del tubo
// dc: dimensione della cella 
    
    double H=Hmax(p,N) ;
    double dc=2.*H ;

    if(dc<L_domain/110.){
        dc=L_domain/110. ;
    }

    int Ncelle=(int)(L_domain/dc)+1 ;
    struct Particle **Griglia=(struct Particle **)malloc(Ncelle*sizeof(struct Particle *)) ;

    makelist(p,Griglia,N,dc,Ncelle) ;

    int maxNeigh=1000 ; 
    double *tempD=(double *)malloc(maxNeigh*sizeof(double)) ;
    int *temp_i=(int *)malloc(maxNeigh*sizeof(int)) ;

    for(int i=0; i<N; i++){
        int icell=(int)(p[i].x/dc) ;
        if(icell>=Ncelle){
            icell=Ncelle-1 ;
        }
        if(icell<0){
            icell=0 ;
        }

        int NeighN=0 ;

        for(int offset=-1; offset<=1; offset++){

            int target=icell+offset ;
            //CC NON Periodiche
            if(target<0 || target>=Ncelle){
                continue ;
            }

            struct Particle *attuale=Griglia[target] ;
            while(attuale!=NULL){
                int j=attuale->i ;
                double D=distance(p[i],*attuale,L_domain) ;
                if (fabs(D)<2.*p[i].h){
                    if(NeighN<maxNeigh){
                        tempD[NeighN]=fabs(D) ;
                        temp_i[NeighN]=j ;
                        NeighN++ ;
                    }
                }
                attuale=attuale->next ;
            }
        }
        //Vogliamo i 64 vicini (al max 64)
        if(NeighN>0){
            di_sort(tempD,temp_i,NeighN) ;
            int L=NeighN ;
            if(NeighN>110){
                L=110 ;
            }
            p[i].neigh_num=L ;
            for(int j=0; j<L; j++){
                p[i].neighbors[j]=temp_i[j] ;
            }
        }else{
            p[i].neigh_num=0 ;
        }
    }

    free(temp_i) ;
    free(tempD) ;
    free(Griglia) ;

    return Hmax(p,N) ;
}
