#include "header.h"

char *end ;

int main(int argc, char *argv[]){
    double t=0. ;
    double t_fin=strtod(argv[1], &end) ;
    int steps=atoi(argv[2]) ;
    double dt=t_fin/steps ;
    //double Maxdt=t_fin/steps ;
    double dx=BoxL/N_grid ;
    double m=strtod(argv[4], &end) ;      // per inserire da terminale la massa in unità di UnitMass.

    double x[N_pt] ;
    double v[N_pt] ;
    //double max_v ;
    double *Density=(double*)malloc(N_grid*sizeof(double)) ;

    double MeshForce[N_grid] ;
    double PartForce[N_pt] ;

    FILE *f_grid ;
    FILE *f_pt ;
    f_grid=fopen("DataGrid.txt","w") ;
    f_pt=fopen("DataPart.txt","w") ;

    /* DEFINIZIONE CONDIZIONI INIZIALI */
    fprintf(f_grid, "# Time: %lf\n", t) ;
    fprintf(f_pt, "# Time: %lf\n", t) ;
    InitialConditions(x,v,f_pt) ;
    for(int j=0; j<N_grid; j++){
        double J=j*dx ;
        Density[j]=density(m,x,J,dx) ;
        Density[j]/=dx ;
    }
    /* END */

    /* PROCEDURA di FOURIER: inizializzazione */
    double *Pot=(double*)malloc(N_grid*sizeof(double)) ;
    
    fftw_complex *kDensity, *kPot ;
    kDensity=fftw_alloc_complex(N_grid) ;
    kPot=fftw_alloc_complex(N_grid) ;

    fftw_plan fft_real_fwd, fft_real_bck ;
    fft_real_fwd=fftw_plan_dft_r2c_1d(N_grid,Density,kDensity,FFTW_ESTIMATE) ;
    fft_real_bck=fftw_plan_dft_c2r_1d(N_grid,kPot,Pot,FFTW_ESTIMATE) ;

    ComputePotential(Density,Pot,kDensity,kPot,fft_real_fwd,fft_real_bck) ;
    ComputeMeshForce(Pot,MeshForce,dx) ;
    ComputePartForce(MeshForce,PartForce,x,dx) ;
    for(int j=0; j<N_grid; j++){
        double J=j*dx ;
        fprintf(f_grid, "%lf\t%lf\t%lf\n", J, Density[j], Pot[j]) ;
    }
    /* END */

    /* PROCEDURA di AVANZAMENTO */
    double T=strtod(argv[3], &end) ; // intervallo di tempo di scrittura sui files
    double nextT=T ;
    while(t<t_fin){

        for(int i=0; i<N_pt; i++){
            v[i]+=(PartForce[i]/m)*(dt/2.) ;
            x[i]+=v[i]*dt ;
            /* CC Periodiche */
            if(x[i]>=BoxL){
                x[i]-=BoxL ;
            }
            if(x[i]<0){
                x[i]+=BoxL ;
            }
            /* End */
        }

        for(int j=0; j<N_grid; j++){
            //Density[j]=0. ;
            double J=j*dx ;
            Density[j]=density(m, x, J, dx) ;
            Density[j]/=dx ;
        }
        ComputePotential(Density,Pot,kDensity,kPot,fft_real_fwd,fft_real_bck) ;
        ComputeMeshForce(Pot,MeshForce,dx) ;
        ComputePartForce(MeshForce,PartForce,x,dx) ;

        for(int i=0; i<N_pt; i++){
            v[i]+=(PartForce[i]/m)*(dt/2.) ;
        }
        t+=dt ;

        /* Scrittura su file */
        if(t>=nextT){
            fprintf(f_grid, "# Time: %lf\n", t) ;
            fprintf(f_pt, "# Time: %lf\n", t) ;
            for(int i=0; i<N_pt; i++){
                fprintf(f_pt, "%lf\t%lf\n", x[i], v[i]) ;
            }
            for(int j=0; j<N_grid; j++){
                double J=j*dx ;
                fprintf(f_grid, "%lf\t%lf\t%lf\n", J, Density[j], Pot[j]) ;
            }
            fflush(f_grid) ;
            fflush(f_pt) ;
            nextT+=T ;
        }
        /* End */

        /* Adaptive timestep */
        /*
        max_v = MaxA(v, N_pt) ;
        if(fabs(max_v)>0.){
            dt = 0.5*dx/max_v ;
        }
        if(dt>Maxdt){
            dt = t_fin/steps ; //Resosi necessario nelle parti iniziali del ciclo while
        }
        */
       /* End */
    }
    /* END */

    fclose(f_grid) ;
    fclose(f_pt) ;

    /* PROCEDURA di FOURIER: deallocazione */
    fftw_destroy_plan(fft_real_bck) ;
    fftw_destroy_plan(fft_real_fwd) ;
    fftw_free(kPot) ;
    fftw_free(kDensity) ; 
    free(Pot) ;
    free(Density) ; 
    
    /* END */

    // Segnale sonoro per avvisare che l'esecuzione è terminata XD
    printf("\a") ;
    fflush(stdout) ;

    return 0 ;

}