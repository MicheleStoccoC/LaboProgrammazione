CC      = gcc
VERBOSE = -Wall
LIB     = -lm
OMPFL	=  -O3
NO_OMP	=  -O3
FPRE	= 70. 0.3 -1. 0.7		# H0(km/s/Mpc) O_m w_EoS O_DE
DPRE	= 0 

HEADERS      	= $(wildcard ./*.h)
OBJ				= $(wildcard ./*.o)
DSOURCES		= Density.c nrutil.c nrutil.h odeint.c rk4.c rkck.c rkqs.c midpointfunc.c		
FSOURCES		= Friedmann2.c nrutil.c nrutil.h odeint.c rk4.c rkck.c rkqs.c midpointfunc.c	
DPROG			= Density
FPROG			= Friedmann


%.o: %.c $(HEADERS) Makefile
	$(CC) $(OMPFL) -c $< -o $@ 

Density: clean_txt $(DSOURCES)
	$(CC) $(NO_OMP) -o $(DPROG) $(DSOURCES) $(LIB)
	@echo '  '
	./$(DPROG) $(DPRE)
		
Friedmann: clean_txt $(FSOURCES)
	$(CC) $(NO_OMP) -o $(FPROG) $(FSOURCES) $(LIB)
	@echo '  '
	./$(FPROG) $(FPRE)
	
clean:
	rm -rf *~ $(DPROG) $(FPROG) $(OBJ)

clean_txt:
	rm -rf *.txt

#clean_gifs:
#	rm -rf *.gif
