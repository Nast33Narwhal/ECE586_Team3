#### Makefile
#### ECE586 - RISCV Simulator
#### Michael Weston - Braden Harwood - Stephen Short - Drew Seidel

CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = main.o wrappers.o registers.o
SRC = src/main.c src/wrappers/wrappers.c src/registers/registers.c 
HDRS = src/wrappers/wrappers.h	src/registers/registers.h
EXE  = sim.exe


#.PHONY to inform Make to not associate all with a file named all
.PHONY: all
all: sim

sim : $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXE) $(SRC)

main.o : src/main.c
	$(CC) $(CFLAGS) -c src/main.c

wrappers.o : src/wrappers/wrappers.c src/wrappers/wrappers.h
	$(CC) $(CFLAGS) -c src/wrappers/wrappers.c

registers.o : src/registers/registers.c src/registers/registers.h
	$(CC) $(CFLAGS) -c src/registers/registers.c

# -DDEBUG will define DEBUG and recompile everything with DEBUG symbols enabled
debug : $(OBJS)
	$(CC) $(CFLAGS) -DDEBUG -DVERBOSE -o $(EXE) $(SRC)



#.PHONY to inform Make to not associate clean with a file named clean
.PHONY: clean
clean:
	@rm -f $(OBJS) sim.exe