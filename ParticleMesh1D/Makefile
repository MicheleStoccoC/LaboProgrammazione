#	VARIABILI
CC = gcc
NGP_CFLAGS = -Wall -O2 -std=c99
TGP_CFLAGS = -Wall -DTGP -O2 -std=c99
CIC_CFLAGS = -Wall -DCIC -O2 -std=c99
LDLIBS = -lfftw3 -lm
TARGET_N = 1dpm_ngp
TARGET_T = 1dpm_tgp
TARGET_C = 1dpm_cic
SRCS = main_pm.c functions.c parameters.c
OBJS_N = $(SRCS:.c=.ngp.o)		
OBJS_T = $(SRCS:.c=.tgp.o)
OBJS_C = $(SRCS:.c=.cic.o)		

#	REGOLE PRINCIPALI
## 1D_PM NGP 
ngp: $(OBJS_N)
	$(CC) $(OBJS_N) -o $(TARGET_N) $(LDLIBS)

%.ngp.o: %.c header.h
	$(CC) $(NGP_CFLAGS) -c $< -o $@

## 1D_PM TGP
tgp: $(OBJS_T)
	$(CC) $(OBJS_T) -o $(TARGET_T) $(LDLIBS)

%.tgp.o: %.c header.h
	$(CC) $(TGP_CFLAGS) -c $< -o $@

## 1D_PM CIC
cic: $(OBJS_C)
	$(CC) $(OBJS_C) -o $(TARGET_C) $(LDLIBS)

%.cic.o: %.c header.h
	$(CC) $(CIC_CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(TARGET_N) $(TARGET_T) $(TARGET_C) $(OBJS_N) $(OBJS_T) $(OBJS_C)
