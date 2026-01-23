#include "header.h"

/* Evoluzione contrasto di densita' */
double contrastD(double x){
    double delta ;
    delta = A_deltaPar*sin(x*(2*PI/BoxL)-PI/2) ;
    return delta ;
}
/* Kernel function */
#ifdef TSC
double Kernel(double x){
    double W=0 ;
    if(fabs(x)<0.5){
        W=3./4. -x*x ;
    }else if(fabs(x)<3./2.){
        W=0.5*(3./2.-fabs(x))*(3./2.-fabs(x)) ;
    }
    return W ;
}
#elif CIC
double Kernel(double x){
    double W=0 ;
    if(fabs(x)<1.0){
        W=1-fabs(x) ;
    }
    return W ;
}
#else
double Kernel(double x){
    double W=0 ;
    if(fabs(x)<0.5){
        W=1. ;
    }
    return W ;
}
#endif


/* Densita' */
double density(double m, double x[], double J, double dx){
    double rho=0 ;
    for(int i=0; i<N_pt; i++){
        double D=(x[i]-J) ;
        /* CC Periodiche */
        if(D>BoxL/2.){
            D-=BoxL ;
        }else if(D<-BoxL/2.){
            D+=BoxL ;
        }

        rho=rho+(m*Kernel(D/dx)) ;
    }
    return rho ;
}

/* Inizializzazione delle Condizioni Iniziali */
void InitialConditions(double x[], double v[], FILE *f1){
    double k=2*PI/BoxL ;
    double unif=BoxL/N_pt ;
    double A=A_deltaPar/k ;

    //specifica l'inizializzazione di variabili dentro un loop...
    for(int i=0; i<N_pt; i++){
        double pos=(i+0.5)*unif ; // particelle centrate nella cella
        double Dpos=-A*sin(k*pos) ; // spostamento iniziale delle pt
        x[i]=pos+Dpos ;
        /* CC Periodiche */
        if(x[i]>=BoxL){
        x[i]-=BoxL ;
        }
        if(x[i]<0){
        x[i]+=BoxL ;
        }

       v[i]=0. ; // tutte le particelle partono da ferme.
       
       fprintf(f1, "%lf\t%lf\n", x[i], v[i]) ;
    }
}

/* Procedura di Fourier */
void ComputePotential(double *Density, double *Pot, fftw_complex *kDensity, fftw_complex *kPot, fftw_plan fft_real_fwd, fftw_plan fft_real_bck){
    // Computazione dello scarto di densita' rispetto alla media in modo da osservare il collasso della struttura
    double MedD=0. ;
    for(int i=0; i<N_grid; i++){
        MedD+=Density[i] ;
    }
    MedD/=N_grid ;
    for(int i=0; i<N_grid; i++){
        Density[i]-=MedD ;
    }

    fftw_execute( fft_real_fwd ) ;
    kPot[0][0]=0. ; // Impongo il potenziale nullo a k=0
    kPot[0][1]=0. ;

    double norm_k = 2 * PI / BoxL ;
    for( int i=1; i<(N_grid/2 +1); i++){
        double k = (i*1.0) * norm_k ;
        double green=-4.*PI*G/(k*k) ;
        kPot[i][0] = kDensity[i][0]*green ;
        kPot[i][1] = kDensity[i][1]*green ;
    }

    fftw_execute( fft_real_bck ) ;
    double norm = 1.0 / N_grid ;
    for(int i=0; i<N_grid; i++){
        Pot[i] *= norm ;
    }
    // Se si vuole studiare la densità e non lo scarto
    for(int i=0; i<N_grid; i++){
        Density[i]+=MedD ;
    }

}

/* Forze dal potenziale */
void ComputeMeshForce(double *Pot, double MF[], double dx){
    /* CC Periodiche */
    MF[0]=-(Pot[1]-Pot[N_grid-1])/(2*dx) ;
    MF[N_grid-1]=-(Pot[0]-Pot[N_grid-2])/(2*dx) ;
    for(int i=1; i<N_grid-1; i++){
        MF[i]=-(Pot[i+1]-Pot[i-1])/(2*dx) ;
    }
}
void ComputePartForce(double MF[], double PF[], double x[], double dx){
    for(int i=0; i<N_pt; i++){
        PF[i]=0 ;
        for(int j=0; j<N_grid; j++){
            double J=j*dx ;
            double D=x[i]-J ;
            /* CC Periodiche */
            if(D>BoxL/2.){
                D-=BoxL ;
            }else if(D<-BoxL/2.){
                D+=BoxL ;
            }
            PF[i]+= MF[j]*Kernel(D/dx) ;
        }
    }
}

/* Massimo di un array */
double MaxA(double Arr[], int N){
    double m=0.0 ;
    for(int i=0; i<N; i++){
        if(fabs(Arr[i])>m){
            m=fabs(Arr[i]) ;
        }
    }
    return m ;
}