// cpu.h : The office blueprint

#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_REGISTERS  8 // 8 sticky notes on the desk
#define MEMORY_SIZE 65536  //64 KB filing cabinet ( 64 * 1024 = 65536 bytes)

// Status borad lights
#define FLAG_ZERO   (1 << 0) // THE answer was zero
#define FLAG_NEGATIVE  (1 << 1) //The answer was negaitve
#define FLAG_OVERFLOW (1 << 2) //The  number wrapped around

  typedef struct {
   uint16_t registers[NUM_REGISTERS]; //The 8 sticky notes  (R0-R7), INTERNAL CPU Storage
   uint16_t pc;  //Task checklist position or PROGRAM COUNTER...To address 2^16 bits, we need 16 bits
   uint16_t sp; // Inbox tray position ( stack pointer)..since the stack is stored inside the same memory so 16 bits
   uint16_t flags; //Status board(Z, N,  lights)
   uint8_t  memory[MEMORY_SIZE]; //The filing cabinet
   bool  halted;
   uint64_t cycles; //How many tasks completed
  } CPU;  // structure name becomes CPU.... NOW CPU contains CPU.pc, CPU.sp, CPU.cycles, etc.

  #endif

 // if address bus memory or program counter has 16 bits, we can get at max memory = 2^16 =  64 KB only!! Program counters refers to a memory
 // flag status only requires 3 bit, using 16bits is convenient since CPU word size is 16 bits,..Real CPU also stores flags inside a status register
 // memory stors instr, program data, stack data... Computers use byte-addressable memory..that is memory[0] -> 1 byte
 // why 64 bits for cycle? Program may run for billions of instructions..using 64 bits allows 2^64 = 18 quintillion
