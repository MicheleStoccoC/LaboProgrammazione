CC      = gcc
VERBOSE = -Wall
LIB     = -lm
FLAGS	= -O3
FPRE	= 70. 0.3 -1. 0.7		# H0(km/s/Mpc) O_m w_EoS O_DE

HEADERS      	= $(wildcard ./*.h)
OBJ				= $(wildcard ./*.o)
DMSOURCES		= Density_midpoint.c nrutil.c nrutil.h odeint.c rk4.c rkck.c rkqs.c
DASOURCES		= Density_adaptive.c nrutil.c nrutil.h odeint.c rk4.c rkck.c rkqs.c		
FSOURCES		= Friedmann2.c nrutil.c nrutil.h odeint.c rk4.c rkck.c rkqs.c midpointfunc.c
ISOURCES		= InkDiffusion.c nrutil.c nrutil.h odeint.c rk4.c rkck.c rkqs.c
DMPROG			= DensityM
DAPROG			= DensityA
FPROG			= Friedmann
IPROG			= Diffusion


%.o: %.c $(HEADERS) Makefile
	$(CC) $(FLAGS) -c $< -o $@ 

DensityM: $(DMSOURCES)
	$(CC) $(FLAGS) -o $(DMPROG) $(DMSOURCES) $(LIB)
	@echo '  '
	./$(DMPROG)

DensityMC: $(DMSOURCES)
	$(CC) $(FLAGS) -DRHO_CONST -o $(DMPROG) $(DMSOURCES) $(LIB)
	@echo '  '
	./$(DMPROG)

DensityA: $(DASOURCES)
	$(CC) $(FLAGS) -o $(DAPROG) $(DASOURCES) $(LIB)
	@echo '  '
	./$(DAPROG)

DensityAC: $(DSOURCES)
	$(CC) $(FLAGS) -DRHO_CONST -o $(DAPROG) $(DASOURCES) $(LIB)
	@echo '  '
	./$(DAPROG)
		
Friedmann: $(FSOURCES)
	$(CC) $(FLAGS) -o $(FPROG) $(FSOURCES) $(LIB)
	@echo '  '
	./$(FPROG) $(FPRE)

Diffusion: $(ISOURCES)
	$(CC) $(FLAGS) -o $(IPROG) $(ISOURCES) $(LIB)
	@echo '  '
	./$(IPROG)
	
clean:
	rm -rf *~ $(DAPROG) $(DMPROG) $(FPROG) $(IPROG) $(OBJ)

clean_txt:
	rm -rf *.txt

clean_img:
	rm -rf *.png
	rm -rf *.jpg
