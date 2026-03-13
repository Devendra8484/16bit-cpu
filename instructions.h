// instructions.h : Reading and writing the task forms

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>
#include "opcodes.h"

// Reading a task form (decoding)
// REGISTER INSTRUCTIONS

#define DECODE_OPCODE(instr)  ((Opcode)(((instr) >> 11) & 0x1F)) /*shift the instructiton by 11 bits and keep the lowest 5 bits
The (Opcode) will convert the number into Opcode enum type, so if bits are 00011, result becomes OP_ADD */

#define DECODE_DST(instr) (((instr) >> 8) & 0x7) // shift the instruction by 8 bits and keep lowest 3 bit

// | opcode | dst | src | imm |
// | 5 bits |3bits| 3bit| 5bit|    FORMAT OF INSTRUCTION

/* instr >> 8 means shift the instruction 8 bits to the right... for e.x if instr was 10101 010 011 00100
after instr >> 8, it will become 0000000010101010 , the dst bits are near the lowest bits
0x7 in binary is 0000000000000111 and & 0x7 will mask and keep only the last 3 bits and three bits will
represent the 8 registers (dst here)..SIMILARLY we Have!.....\|/ */

#define DECODE_SRC(instr)  (((instr) >> 5) & 0x7)
#define DECODE_IMM5(instr) ((instr) & 0x1F)

// JUMP INSTRUCTIONS (where registers are not used)
#define DECODE_ADDR(instr) ((instr) & 0x7FF)

/* This DECODE_ADDR(instr) is for JMP type instructions since instructions like JMP, JZ, JN,JNZ don't use the registers.
 * They use the format | opcode | address |
                       | 5 bits | 11 bits |
 * & 0x7FF will mask the lower or last 11 bits */ 

//writing a task form (encoding): Format R
static inline uint_16 ENCODE_REG(Opcode op, uint8_t dst, uint8_t src, uint8_t imm5) {
	return ((uint16_t)(op & 0x1F) << 11)| ((uint16_t)( dst & 0x7) << 8) |
	((uint16_t)(src & 0x7) << 5) || (imm5 & 0X1F);
}


/*static is to make the file-local and when other files include instruction.h, each files will have its own private ENCODE_REG
 * when we normally call a function without inline, the CPU push parameters, jump to function and then execute it
 * (Do search Function Call Overhead) since ENCODE_REG is tiny the functn call overhead will be more expensive than the function itself
 * so after using inline, there is no "function call at RUNTIME" */

// Writing a task form (encoding): Format J
static inline uint16_t ENCODE_JUMP(Opcode op, uint16_t address) {
    return ((uint16_t)(op & 0x1F) << 11) | (address & 0x7FF);
}

#endif
