#	VARIABILI
CC = gcc
STD_CFLAGS = -Wall -O2 -std=c99
TRAP_CFLAGS = -Wall -DTRAPPIST -O2 -std=c99
LDLIBS = -lm
TARGET_S = main_sun
TARGET_T = main_trap
SRCS = main_orbite.c functions.c costanti.c
OBJS_S = $(SRCS:.c=.sun.o)		# Oggetti per il Sole
OBJS_T = $(SRCS:.c=.trap.o)		# Oggetti per Trappist-1

#	REGOLE PRINCIPALI
## Sole std 
sun: $(OBJS_S)
	$(CC) $(OBJS_S) -o $(TARGET_S) $(LDLIBS)

%.sun.o: %.c header.h
	$(CC) $(STD_CFLAGS) -c $< -o $@

## Trappist-1
trapp: $(OBJS_T)
	$(CC) $(OBJS_T) -o $(TARGET_T) $(LDLIBS)

%.trap.o: %.c header.h
	$(CC) $(TRAP_CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(TARGET_S) $(TARGET_T) $(OBJS_S) $(OBJS_T)
	rm -f bin2txt
	rm -f Pianeta*

bintotxt: bintotxt.c
	$(CC) $(STD_CFLAGS) bintotxt.c costanti.c -o bin2txt $(LDLIBS)