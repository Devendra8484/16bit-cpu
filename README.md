# 16-bit CPU Emulator (Learning Project)

This project is my attempt to understand how a CPU works internally by building a simple **16-bit CPU emulator in C**.

Currently implemented:

- CPU structure (`cpu.h`)
- 8 general purpose registers
- Program Counter (PC)
- Stack Pointer (SP)
- CPU flags (Zero, Negative, Overflow)
- 64 KB memory
- Cycle counter

## CPU Structure

The CPU currently contains:

- **Registers** – 8 registers (R0–R7) storing 16-bit values  
- **Program Counter (PC)** – points to the next instruction  
- **Stack Pointer (SP)** – tracks the stack location in memory  
- **Flags** – status indicators (Zero, Negative, Overflow)  
- **Memory** – 64 KB byte-addressable memory  
- **Cycles** – counts number of executed instructions  

## Learning Source

This project is being built while learning from the following repository:

https://github.com/vixhal-baraiya/16bit-cpu

The implementation here is written by me for learning purposes while studying how CPU emulators work.

## Next Steps

Planned components:

- ALU implementation
- Memory read/write functions
- Instruction format
- CPU execution cycle (Fetch–Decode–Execute)
- Simple assembler
