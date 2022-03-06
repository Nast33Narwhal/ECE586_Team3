#### Makefile
#### ECE586 - RISCV Simulator
#### Michael Weston - Braden Harwood - Stephen Short - Drew Seidel

CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = main.o wrappers.o registers.o decode.o parser.o memory.o execute.o
SRC = src/main.c src/wrappers/wrappers.c src/registers/registers.c src/decode/decode.c src/parser/parser.c src/memory/memory.c src/execute/execute.c
HDRS = src/wrappers/wrappers.h src/registers/registers.h src/decode/decode.h src/parser/parser.h src/memory/memory.h src/execute/execute.h
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

parser.o : src/parser/parser.c src/parser/parser.h
	$(CC) $(CFLAGS) -c src/parser/parser.c

registers.o : src/registers/registers.c src/registers/registers.h
	$(CC) $(CFLAGS) -c src/registers/registers.c

decode.o : src/decode/decode.c src/decode/decode.h
	$(CC) $(CFLAGS) -c src/decode/decode.c

memory.o : src/memory/memory.c src/memory/memory.h
	$(CC) $(CFLAGS) -c src/memory/memory.c
	
execute.o : src/execute/execute.c src/execute/execute.h 
	$(CC) $(CFLAGS) -c src/execute/execute.c 

# -DDEBUG will define DEBUG and recompile everything with DEBUG symbols enabled
debug : $(OBJS)
	$(CC) $(CFLAGS) -DDEBUG -o $(EXE) $(SRC)

# -DDEBUG will define DEBUG and DVERBOSE and recompile everything with DEBUG and DVERBOSE symbols enabled
verbose : $(OBJS)
	$(CC) $(CFLAGS) -DDEBUG -DVERBOSE -o $(EXE) $(SRC)	

# -DREGISTERS will define REGISTERS and recompile everything with REGISTERS symbols enabled
registers : $(OBJS)
	$(CC) $(CFLAGS) -DREGISTERS -o $(EXE) $(SRC)




#.PHONY to inform Make to not associate clean with a file named clean
.PHONY: clean
clean:
	@rm -f $(OBJS) sim.exe outfile.mem
