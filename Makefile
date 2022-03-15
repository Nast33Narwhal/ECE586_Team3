#### Makefile
#### ECE586 - RISCV Simulator
#### Michael Weston - Braden Harwood - Stephen Short - Drew Seidel

CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = main.o wrappers.o registers.o decode.o parser.o memory.o execute.o userInterface.o
SRC = src/main.c src/wrappers/wrappers.c src/registers/registers.c src/decode/decode.c src/parser/parser.c src/memory/memory.c src/execute/execute.c src/userInterface/userInterface.c
HDRS = src/wrappers/wrappers.h src/registers/registers.h src/decode/decode.h src/parser/parser.h src/memory/memory.h src/execute/execute.h src/userInterface/userInterface.h
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

userInterface.o : src/userInterface/userInterface.c src/userInterface/userInterface.h
	$(CC) $(CFLAGS) -c src/userInterface/userInterface.c

registers.o : src/registers/registers.c src/registers/registers.h
	$(CC) $(CFLAGS) -c src/registers/registers.c

decode.o : src/decode/decode.c src/decode/decode.h
	$(CC) $(CFLAGS) -c src/decode/decode.c

memory.o : src/memory/memory.c src/memory/memory.h
	$(CC) $(CFLAGS) -c src/memory/memory.c
	
execute.o : src/execute/execute.c src/execute/execute.h src/execute/execute_I.c src/execute/execute_R.c src/execute/execute_BJ.c src/execute/execute_SU.c 
	$(CC) $(CFLAGS) -c src/execute/execute.c 

# -DDEBUG will define DEBUG and recompile everything with DEBUG symbols enabled
debug : $(OBJS)
	$(CC) $(CFLAGS) -DDEBUG -o $(EXE) $(SRC)

# -DREG_MEM will define DEBUG and DREG_MEM and recompile everything with DEBUG and DREG_MEM symbols enabled
reg_mem : $(OBJS)
	$(CC) $(CFLAGS) -DDEBUG -DREG_MEM -o $(EXE) $(SRC)	

# -DVERBOSE will define RVERBOSE and recompile everything with REGISTERS symbols enabled
verbose : $(OBJS)
	$(CC) $(CFLAGS) -DVERBOSE -o $(EXE) $(SRC)

# helpful printout for makefile
.PHONY: help
help: 
	$(info )
	$(info The following options are available for make)
	$(info )
	$(info make debug)
	$(info Recompiles everything with DEBUG symbols enabled (debug messages))
	$(info )
	$(info make reg_mem)
	$(info Recompiles everything with DEBUG and DREG_MEM symbols enabled (register and memory contents for every command and debug messages))
	$(info )
	$(info make verbose)
	$(info Recompiles everything with REGISTERS symbols enabled (register contents for every command))
	$(info )
	$(info make clean)
	$(info Removes all object files associated with the simulator)
	$(info )

#.PHONY to inform Make to not associate clean with a file named clean
.PHONY: clean
clean:
	@rm -f $(OBJS) sim.exe 
