// alu.c : Calculator

#include "cpu.h"
#include "opcodes.h"
#include <stdio.h>

// The function will automatically update the status board after every operation

void update_flags(CPU *cpu, uint16_t result, uint16_t a, uint16_t b, Opcode op) {
	cpu->flags = 0; //Initialized to zero	 
	
	if (result == 0) cpu->flags |= FLAG_ZERO;   //The reason behind using  | (OR) is to avoid changing other flag value
	if (result & 0x8000) cpu->flags |= FLAG_NEGATIVE;
	
	// Overflow: both inputs had the same sign, but result has a different sign	
	if (op == OP_ADD) {
		/*(a ^ result) checks whether sign of a changed ( XOR becomes 1) or not
		 * & 0x8000 is because we only need to find whether the 15bit value changed or not */
		if (( a ^ result) & (b ^ result) & 0x8000) // The leftmost bit (bit 15) is the sign bit; 0 = positive, 1 = negative
			cpu->flags |= FLAG_OVERFLOW;
		}
	if (op ==  OP_SUB || OP_CMP) {
		// OVERFLOW when sign of a and b differs & sign of a and result differs
		else if ((a ^ b) & (a ^ result) & 0x8000)
			cpu->flags |= FLAG_OVERFLOW;
		}
	}
	
	//OPERATIONS ON THE CALC
	
	uint16_t alu_execute(CPU *cpu, Opcode op, uint16_t a, uint16_t b) {
		uint16_t result = 0;
		
		switch (op) {
			case OP_ADD: result = a + b;     		  break;
			case OP_SUB:
			case OP_CMP: result = a - b;     		  break;
			case OP_AND: result = a & b;     		  break;
			case OP_OR:  result = a | b;     		  break;
			case OP_XOR: result = a ^ b;     		  break;
			case OP_NOT: result = ~a;		          break;
			case OP_SHL: result = a << (b & 0xF);     break; // here b is being limited to only the lowest 4 bits since 1111 equals 15 which is the allowed length for a.
			case OP_SHR: result = a >> (b & 0xF);	  break;
			default:
				fprintf(stderr, "Calculator Error: unknown operation 0x%X\n", op); // fprintf is used to print formatted text (stderr) instead of normal output ( stdout ) ; %X means print number in hexadecimal
				return 0; // safe fallback result
			}
			update_flags(cpu, result, a, b, op);
			return result;
		}
				
