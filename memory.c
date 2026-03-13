// memory.c

#include <string.h>
#include <stdio.h>
#include "cpu.h"

// function to initialize the entire CPU state when the emulator starts (powering ON the processor)

void cpu_init(CPU *cpu) { //here we have created the pointer cpu which will transverse through elements of struct CPU
	memset(cpu->registers, 0, sizeof(cpu->registers));
	
	/* memset fills a block of memory with a specific value
	 * for e.g. void *memset(void *ptr, int value, size_t size) WILL fill memory starting at ptr with value for size bytes
	 * so this line will set all registers to zero, we could have written size of cpu->reg but let the compiler calculate it. */
	 
	 memset(cpu->memory, 0, sizeof(cpu->memory)); // this clears the entire RAM
	 
	 cpu->pc = 0x0000;
	 cpu->sp = 0xFFFF;
	 cpu->flags = 0;
	 cpu->halted = false;
	 cpu->cycles = 0;
 }
 
 /* My RAM is defined for 8 bits(1 byte) but CPU Inststructions and many values are 16-bit numbers
  * so, we must combine two bytes into one 16-bit number */
 // we want a 16-bit value from memory 
 
 uint16_t mem_read16(CPU cpu*, uint16_t address) {
	 uint16_t low = cpu->memory[address]; //Even though memory stores uint8_t, we store it in a 16-bit variable so we can safely combine it later
	 uint16_t high = cpu->memory[address + 1];
	 return (high << 8) | low;
	// high << 8 occupies bits 15-8 and low occupies 7-0
 }
 
 void mem_write16(CPU cpu*, uint16_t address, uint16_t value) {
	 cpu->memory[address] = value & 0xFF; //STORE the low 8 bytes
	 cpu-> memory[address + 1] = (value >> 8) & 0xFF; //Stores the high 8 bytes
 }
 
