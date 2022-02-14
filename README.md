# ECE586_Team3
Specification Document for
Simple RISC-V ISA Simulator

Team 3's final project for ECE 486/586
Portland State University, Winter 2022

Braden Harwood, Stephen Short, Michael Weston, Drew Seidel

*\*Information sourced from Dr. Faust's Final Project Description and Group Discussion*

## Description
The Simple RISC-V ISA Simulator will be an instruction set architecture level simulator for RISC-V's RV32I Base Integer Instruction Set written in C.
We will be ignoring the memory ordering instructions, the environment call and breakpoints, and hint instructions (Sections 2.7 - 2.9).
Basis of Specifications for RV32I (Chapter 2): https://riscv.org/wp-content/uploads/2019/12/riscv-spec-20191213.pdf

Our simulator will read a simple ASCII file that represents a memory image.
The ASCII file will be generated from assembly code we write and assemble with the RISC-V GNU toolchain assembler `rvas` and C code compiled with the RISC-V GNU toolchain compiler `rvgcc -fpic -march=rv32i -mabi=ilp32 -S`.

## Inputs/Outputs
### Command line input arguments:
- Input memory image file (default to program.mem)
- Starting address (default to 0)
- Stack address (default to 65535)

#### Format of Memory Image File:
Lines with hexadecimal memory address followed by a colon, then whitespace (tabs or spaces) and then the hexadecimal contents of that memory location.
- Example:
- 0: fd010113
- 4: 02812623
- 8: 03010413
- c: fca42e23

Memory Image File (prog.mem) Generated with the prog.o object file using the command:
`rvobjdump -d prog.o | grep -o '^[[:blank:]]*[[:xdigit:]]*:[[:blank:]][[:xdigit:]]*' > prog.mem`

### Outputs:
2 Modes: Verbose and Silent
- Verbose: Print PC and Hexadecimal value of each instruction as it's fetched along with the contents (in hexadecimal) of each register after the instruction's execution.
- Silent: Print the PC of the final instruction and the hexadecimal value of each register only at the end of the simulation.

You can also have your program print out debug information, but it must be suppresible during the demo without needing to recompile.

### Assumptions:
- Simulator will initialize the sp and pc based on command line arguements and initialize ra = 0.
- Simulator will continue operating until we encounter a jr ra instruction with ra == 0
- main() will be the first function written with all functions after it to ensure that our code begins at location 0 and the return from main() will trigger the previous assumption and end the simulation.
- For assembly code, we can use a jr ra instruction at the end of our code.
- Maximum program size is 64KiB or smaller.

### Extra Credit:
- Implement the ecall instruction to provide at least the three system calls read, write, and exit. View the project description for more information.
- Provide the ability to single step and print contents of register, memory, display current instruction. Optionally provide ability to set a breakpoint, "watch" a register or memory location
- Same as above with a GUI
- Instruction set extensions (e.g. M (integer multiply/divide), F (floating point)).

#### Design Plan Stages:
- Start early
- Consider incremental development
    - Get the basic memory loading working
    - Get input parameter code working
    - Get the fetch/decode/execute framework working with ability to examine registers, etc.
    - Decode each instruction type
    - Implement and debug one instruction of each type
    - Complete the remaining instructions for each instruction type
- Have a written test strategy and plan
    - Create an outline that covers all functionality (e.g. types of instructions, addressing)
    - Write 1-2 line description of each testcase
    - Include the setup conditions, the functionality being tested, the anticipated result
    - Have someone other than the coder of the functionality be the one to write the test case
    - Verify that the results are as expected
- Include useful debugging information
    - Consider debugging modes/levels
    - Have ability to turn off debugging output!
    - Useful, but not too verbose
