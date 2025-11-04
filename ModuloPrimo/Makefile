# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

# Files
TARGET = main
OBJS = main_orbite.o

# Build executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Pattern rule: how to build any .o file from a .c file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
main.o: math_ops.h

#Cleaning procedure
clean:
	rm -f $(TARGET) $(OBJS)