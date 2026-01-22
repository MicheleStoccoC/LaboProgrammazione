#include "SPH_qrutil.h"

// Per complilare ed eseguire il codice usare:
// make SPH 		(usa liste linkate)
// make SPH_quick   (usa quicksearch)

int main(int argc, char *argv[]){
	struct Particle *p;			//Vettore di particelle
	double dt;					//Passo temporale 
	double length = 1.;			//Dimensioni tubo
	double time = 0.;			//Contatore del tempo
	int step = 0;				//Numero di step per il salvataggio del plot
	clock_t Tstart, Tend ;		//Contatori per le tempistiche di esecuzione


	if(argc<4){
    	printf("ERRORE: Utilizzo Sbagiato\n") ;
    	printf("\nUtilizzo corretto: <eseguibile> <Numero di particelle> <Rateo di particelle (sx/totale)> <Numero di step da aspettare prima di salvare uno snapshot>") ;
    	exit(-1) ;
    }

	
	int N 		 = atoi(argv[1]) ;
	double ratio = atof(argv[2]) ;
	int savestep = atoi(argv[3]) ;
	
	
	if(ratio>1){
		printf("ERRORE: Utilizzo Sbagliato - Rateo>1 \n") ;
		printf("\n argv[2] deve essere compreso tra 0 e 1, rappresenta N_sx/N_tot") ;
		exit(-1) ;
	}

	int n_lz=N*ratio ;
	int n_rz=N-n_lz ;
	double h=0.005 ;
	
	printf("Tempo di stop: %lf\n", FINAL_TIME) ;
	
	/* Allocazione memoria */
	p=(struct Particle *)malloc(N*sizeof(struct Particle)) ;
	if(!p){
		printf("Errore nell'allocazione della memoria delle particelle\n") ;
		exit(-1) ;
	}

	/* Condizioni Iniziali */
	set_IC(p,n_lz,n_rz,length) ;
    snap_time(p,N,0) ;
	
    h=quicksearch(p,N,length) ;
	
	ComputeDensPress(p,N,length) ; 
	ComputeXLR8(p,N,length) ;
	dt=ComputeTimeStep(p,N,h) ;	
	
	Tstart=clock() ;
    //Integrazione del sistema
	while(time<FINAL_TIME){
		printf("\r%3d%% completed... siamo al tempo %lf sec, dt e' %lf sec, step numero %d", (int)(100.*time/FINAL_TIME), time, dt, step) ;
		fflush(stdout) ;
		KDK(p,N,dt,h,length) ;		
		time += dt ;
		dt=ComputeTimeStep(p,N,h) ;
		step++ ;
		if(!(step%savestep)){
			snap_time(p,N,step) ;
		}
		snap_last(p,N) ;
	}
	Tend=clock() ;
	double Ttot=((double)(Tend-Tstart))/CLOCKS_PER_SEC ;

	printf("\n\t100%% completato... tempo simulato: %lf sec \n", time) ;
	printf("Tempo impiegato ad integrare il sistema: %lf sec \n", Ttot) ;
	
    //Libero memoria
	free(p) ;

	printf("\a");
    fflush(stdout);

	return 0 ;

}