#include "SPH_rutil.h"

/* Segno */
double sign(double x){ 
	int s=(x>0)-(x<0) ;
	return s ; 
}

/* Distanza data PBC */
double distance(struct Particle p1, struct Particle p2, double L_domain){
// x1 - x2: particelle tra cui calcolare la distanza
// L_domain: lunghezza del tubo

	double dx=p1.x-p2.x ;
	// CC Periodiche
	/*
	if(dx>0.5*L_domain){  
		dx -= L_domain ;
	}else if(dx<-0.5*L_domain){  
		dx += L_domain ;
	}
	*/

	return dx ;
}


/* Kernel Cubic Spline 1D */
double kernel(double r, double h){
// r: distanza tra due particelle
// h: raggio di interazione della particella

    double q=fabs(r)/h ;
    double sigma=2./(3.*h) ; 

	if(q<=1.0){
		double W=sigma*(1. - 1.5*q*q + 0.75*q*q*q) ;
		return W ;
    }else if(q<=2.){
		double W=sigma*0.25*(2.-q)*(2.-q)*(2.-q) ;
		return W ;
    }else{
		return 0. ;
	}
}

/* Derivata del kernel */
double kern_der(double r, double h){
// r: distanza tra due particelle
// h: raggio di interazione della particella

	double q=fabs(r)/h ;
    double sigma= 2./(3.*h*h) ; 

	if(q<=1.){
		double dW=sigma*(-3.*q + 2.25*q*q)*sign(r) ;
		return dW ;
    }else if(q<=2.){
		double dW=-sigma*0.75*(2.-q)*(2.-q)*sign(r) ;
		return 	dW ;
    }else{
		return 0. ;
	}
}

/*Viscosita' tra due particelle */
double ComputeViscosity(struct Particle a, struct Particle b, double L_domain){
// a - b: particelle tra cui calcolare lo smoothing
// h: raggio di interazione della particella
// L_domain: lunghezza del tubo

	double v_ab=(a.v)-(b.v) ;
	double x_ab=distance(a,b,L_domain) ;
	
	if(v_ab*x_ab<0){
		double mu_ab=a.h*x_ab*v_ab/(x_ab*x_ab + EPSILON*a.h*a.h) ;
		double inv_rho_a=1./(a.rho) ;
		double inv_rho_b=1./(b.rho) ;
		double inv_rho_ab_med=2./(a.rho+b.rho) ;
		double c_s_ab=0.5*(sqrt(GAMMA*(a.P)*inv_rho_a) + sqrt(GAMMA*(a.P)*inv_rho_b)) ;
		double V=(-alpha*c_s_ab*mu_ab + beta*mu_ab*mu_ab)*inv_rho_ab_med ;
		return V ;
	}else{
		return 0. ;
	}
}

/* Tassi di cambiamento posizione ed energia */
void ComputeXLR8(struct Particle *p, int N, double L_domain){
// p: vettore di particelle
// n: numero di particelle
// h: raggio di interazione della particella
// L_domain: lunghezza del tubo
	
	for(int i=0; i<N; i++){
		
		p[i].ax=0. ;
		p[i].au=0. ;
		double inv_rho_i=1./p[i].rho ;
		
		for(int j=0; j<p[i].neigh_num; j++){
			double inv_rho_j=1./p[p[i].neighbors[j]].rho ;
			double r=distance(p[i],p[p[i].neighbors[j]],L_domain) ;
				
			p[i].ax -= M*(p[i].P*inv_rho_i*inv_rho_i + p[p[i].neighbors[j]].P*inv_rho_j*inv_rho_j + ComputeViscosity(p[i],p[p[i].neighbors[j]],L_domain))*kern_der(r,p[i].h) ;
			p[i].au += M*(p[i].P*inv_rho_i*inv_rho_i + 0.5*ComputeViscosity(p[i],p[p[i].neighbors[j]],L_domain))*kern_der(r,p[i].h)*(p[i].v-p[p[i].neighbors[j]].v) ;
		}
	}
}

/* Calcolo di densità e pressione */
void ComputeDensPress(struct Particle *p, int N, double L_domain){
// p: vettore di particelle
// n: numero di particelle
// h: raggio di interazione della particella
// L_domain: lunghezza del tubo

	for(int i=0; i<N; i++){
		p[i].rho=0. ;
		for(int j=0; j<p[i].neigh_num; j++){
			double r=distance(p[i],p[p[i].neighbors[j]],L_domain) ;
			p[i].rho += kernel(r,p[i].h)*M ;
		}

		p[i].P=(GAMMA-1.)*p[i].rho*p[i].u ;

		if(p[i].P<=1e-10 || p[i].rho<=1e-10){
			fprintf(stderr, "\nERRORE: Pressione (%lf) o densità (%lf) troppo piccola o negativa per la particella %d, di energia %lf\n", p[i].P, p[i].rho, i, p[i].u) ;
			printf("Posizione: %lf, Velocità: %lf, Smoothing: %lf\n", p[i].x, p[i].v, p[i].h) ;
			for(int j=0; j<p[i].neigh_num; j++){
				printf("Vicino %d: Posizione: %lf, Velocità: %lf, Smoothing: %lf\n", p[i].neighbors[j], p[p[i].neighbors[j]].x, p[p[i].neighbors[j]].v, p[p[i].neighbors[j]].h) ;
			}
			exit(EXIT_FAILURE) ;
		}
	}
}

/* Passo temporale */
double ComputeTimeStep(struct Particle *p, int N, double h){
// p: vettore di particelle
// n: numero di particelle
// h: raggio di interazione della particella

	double dt=10. ;
	for(int i=0; i<N; i++){
		double dt_temp=K*h*sqrt(p[i].rho/(GAMMA*p[i].P)) ;
		if(dt_temp<dt){
			dt=dt_temp ;
		}
	}
	
	if (dt<1e-8){
		fprintf(stderr, "\nERRORE: passo temporale troppo piccolo: %lf", dt) ;
		exit(EXIT_FAILURE) ;
	}
	
	return dt ;
}

/* Kick-Drift-Kick */
void KDK(struct Particle *p, int N, double dt, double h, double L_domain){
// p: vettore di particelle
// n: numero di particelle
// dt: step temporale
// h: raggio di interazione della particella
// L_domain: lunghezza del tubo

	double hh=0.5*dt ;
	
	for(int i=0; i<N; i++){
		
		p[i].v += p[i].ax*hh ; 
		p[i].u += p[i].au*hh ;

		if(p[i].u<=0.){
				printf("\nWARNING: energia negativa (%lf) per %d\n", p[i].u, i) ;
				printf("Posizione: %lf, Velocità: %lf, Smoothing: %lf\n", p[i].x, p[i].v, p[i].h) ;
				for(int j=0; j<p[i].neigh_num; j++){
					printf("Vicino %d: Posizione: %lf, Velocità: %lf, Smoothing: %lf\n", p[i].neighbors[j], p[p[i].neighbors[j]].x, p[p[i].neighbors[j]].v, p[p[i].neighbors[j]].h) ;
				}
		}
	
		p[i].x += p[i].v*dt ; 
		//Pareti Riflettenti
		if(p[i].x<0.){
			p[i].x=-p[i].x ;
			p[i].v=-p[i].v ;
		}
		if(p[i].x>L_domain){
			p[i].x=L_domain-(p[i].x-L_domain) ;
			p[i].v=-p[i].v ;
		}
	}
	
	double hmax=listsearch(p,N,L_domain) ;

	ComputeDensPress(p,N,L_domain) ;
	ComputeXLR8(p,N,L_domain) ;

	for(int i=0; i<N; i++){
		p[i].i=i ;
		
		p[i].v +=  p[i].ax*hh ; 
		p[i].u +=  p[i].au*hh ;

		//Controllo sull'energia
		if(p[i].u<=0.){
				printf("\nWARNING: energia negativa (%lf) per %d\n", p[i].u, i) ;
				printf("Posizione: %lf, Velocità: %lf, Smoothing: %lf\n", p[i].x, p[i].v, p[i].h) ;
				for(int j=0; j<p[i].neigh_num; j++){
					printf("Vicino %d: Posizione: %lf, Velocità: %lf, Smoothing: %lf\n", p[i].neighbors[j], p[p[i].neighbors[j]].x, p[p[i].neighbors[j]].v, p[p[i].neighbors[j]].h) ;
				}
		}
	}	
}