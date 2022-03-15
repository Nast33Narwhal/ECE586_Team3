# ECE586_Team3
Team 3's final project for ECE 486/586
Portland State University, Winter 2022

Braden Harwood, Stephen Short, Michael Weston, Drew Seidel

*\*Information sourced from Dr. Faust's Final Project Description and Group Discussion*
## Table of Contents
- Objective
- Directory Organization
- Getting Started
- Usage
- Test Plan

## Objective
To be written

## Directory Organization
- docs
  - Contains documentation relating to the project including our specifications document, edge cases tracking, test plan, and table of timing constraints.
- src
  - Contains all of our source files including the main program (main.c (note could change to risc_sim.c etc.)) and all of the various supporting ADTs, wrappers, and functions.
- testing
  - to be written

## Getting Started
1. Clone the repository to your computer
   ```sh
   git clone https://github.com/your_username_/ECE586_Team3.git
   ```
2. Run make to compile the project
   ```sh
   make
   ```
3. For a basic simulation, run the following:
   ```sh
   ./sim.exe 
   ```
   By default, program reads from 'program.mem' in directory as input file. By default program counter is 0, stack pointer is 65535. Output will be generated and sent to stdout
   
   For more advanced use, see the Usage section for different flags that can be set during runtime.
   A few examples:
   
   - Will set the start program counter to 4, and the stack pointer to 4096.
   ```sh
   ./sim.exe -pc 4 -sp 4096
   ```
   
   - Will read the file 'prog1.mem' into memory. Will set the start program counter to 4, and the stack pointer to 4096.
   ```sh
    ./sim.exe prog1.mem -pc 4 -sp 4096
   ```
 <!--- 
   - Will run the simulator using the default scheduling policy.
   ```sh
   ./sim.exe testing/traces/trace.txt
   ```
  
   - Will run the simulator as described above with the optimized policy and will also print out statistics on reads, writes, and instruction fetches at the end of the output.
   ```sh
   ./sim.exe -stat -opt testing/traces/trace.txt
   ```
  --> 
   
## Usage
### sim.exe
The simulation program sim.exe has the following flags:
- to be written

### make
make also has additional targets:
- \<none>    : No target provided defaults to the basic compilation of all
- all        : Compiles the simulator sim.exe
- verbose    : Compiles the simulator sim.exe but adds additional text to the output to give more information about what is happening.
- debug      : Compiles the simulator sim.exe and adds all possible additional text to the output for debugging purposes.
- clean      : Removes all object files and the executable generated by make to clean the directory.

## Test Plan
Go through the most recent RISCV specifications document and test each implemented function according to its particular specifications.
