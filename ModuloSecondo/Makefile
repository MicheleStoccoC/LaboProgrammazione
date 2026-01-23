
CC      = gcc
P		= py
VERBOSE = -Wall -Wextra
LIB     = -lm
OMPFL	=  -O3 -march=native -mtune=native -funroll-loops -ftree-vectorize -fopenmp
NO_OMP	=  -O3 -march=native -mtune=native -funroll-loops -ftree-vectorize 
PRESPH	= 4000 0.8 3

HEADERS      	= $(wildcard ./*.h)
OBJ				= $(wildcard ./*.o)
SOURCES			= SPH_io.c SPH_main.c SPH_rutil.c SPH_rutil.h SPH_listsearch.c SPH_phys.c
QSOURCES		= SPH_qio.c SPH_qmain.c SPH_qrutil.c SPH_qrutil.h SPH_quicksearch.c SPH_qphys.c
PROG			= SPH
QPROG			= QSPH
SNAPS			= snapshot_*


%.o: %.c $(HEADERS) Makefile
	$(CC) $(OMPFL) -c $< -o $@ 

SPH_quick: clean_snaps $(QSOURCES)
	$(CC) $(NO_OMP) -o $(QPROG) $(QSOURCES) $(LIB)
	@echo '  '
	./$(QPROG) $(PRESPH)
		
SPH_list: clean_snaps $(SOURCES)
	$(CC) $(NO_OMP) -o $(PROG) $(SOURCES) $(LIB)
	@echo '  '
	./$(PROG) $(PRESPH)
	
clean:
	rm -rf *~ $(PROG) $(QPROG) $(OBJ)

clean_snaps:
	rm -rf snap*

clean_gifs:
	rm -rf *.gif
