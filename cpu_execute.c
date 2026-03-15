//cpu_execute.c  FETCH -> DECODE -> EXECUTE

#include <stdio.h>
#include <inttypes.h>
#include "cpu.h"
#include "opcodes.h"
#include "instructions.h"

extern uint16_t alu_execute(CPU *cpu, Opcode op, uint16_t a, uint16_t b); // extern means this fn is defined in another file
extern uint16_t mem_read16(CPU *cpu, uint16_t address);
extern void mem_write16(CPU *cpu, uint16_t address, uint16_t value);

// In every clock pulse

void cpu_step(CPU *cpu) {
	if (cpu -> halted) return;
	
	//	FETCH: Read the Task
	uint16_t instruction = mem_read16(cpu, cpu->pc);
	
	//  DECODE: 
	Opcode opcode = DECODE_OPCODE(instruction);
	uint8_t dst = DECODE_DST(instruction);
	uint8_t src = DECODE_SRC(instruction);
	uint16_t imm5 = DECODE_IMM5(instruction);
	uint16_t addr = DECODE_ADDR(instruction);
	
	cpu -> pc += 2 //advance the program counter to next ( since 16 bit = 2 bytes so it's +=2) Fetch-> pc+2 -> Execute
	
	// EXECUTE: It's time for excution
	
	case OP_NOP: break; // No Operation
	
	case OP_LOAD:
		cpu->registers[dst] = mem_read16(cpu, cpu->pc);
        cpu->pc += 2;
        break;
 
	
	
	case OP_MOV: // COPY note from #src to #dst
		cpu->registers[dst] = cpu->registers[src];
		break;
		
	case OP_ADD: 
		cpu->registers[dst] = alu_execute(cpu, OP_ADD, cpu->registers[dst], cpu->registers[src]);
		break;
		
	case OP_SUB:
		cpu->registers[dst] = alu_eexcute(cpu, OP_SUB, cpu->registers[dst], cpu->registers[src]);
		break;
	
	case OP_AND:
        cpu->registers[dst] = alu_execute(cpu, OP_AND, cpu->registers[dst], cpu->registers[src]);
        break;

    case OP_OR:
        cpu->registers[dst] = alu_execute(cpu, OP_OR, cpu->registers[dst], cpu->registers[src]);
        break;

    case OP_XOR:
        cpu->registers[dst] = alu_execute(cpu, OP_XOR, cpu->registers[dst], cpu->registers[src]);
        break;
    
    case OP_NOT:
		cpu->registers[dst] = alu_execute(cpu, OP_NOT, cpu->registers[dst], 0);
		break;
		
	case OP_SHL:
		cpu->registers[dst] = alu_execute(cpu, OP_SHL, cpu->registers[dst], imm5);//imm5 contains the amount to be shifted
		break;
	
	case OP_SHR:
		cpu->registers[dst] = alu_execute(cpu, OP_SHR, cpu->registers[dst], imm5);
		break;
		
	case OP_CMP:
		cpu->registers[dst] = alu_execute(cpu, OP_CMP, cpu->registers[dst], cpu->registers[src]);
		break;
	
	case OP_JMP: // Skip to task #N on checklist
		cpu->pc = addr;
		break;
	
	case OP_JZ:  // Skip to task #N IF Zero light is ON
		if(cpu->flags & FLAG_ZERO) cpu->pc = addr;
		break;
		
	case OP_JNZ: // "Skip to task #N IF Zero light is off"
		if(!(cpu->flags & FLAG_ZERO)) cpu->pc = addr;
		break;
		
	case OP_JN:  // "Skip to task #N IF Negative light is on"
        if (cpu->flags & FLAG_NEGATIVE) cpu->pc = addr;
        break;
        
    case OP_LDR:  // Go to src(source) and bring the value to destination
		cpu->registers[dst] = mem_read16(cpu, cpu->registers[src]);
		break;
	
	case OP_STR:  //Store the value of source(src) to dst;
		mem_write16(cpu, cpu->registers[dst], cpu->registers[src]);
		break;
		
	case OP_PUSH:
		cpu -> sp -= 2;
		mem_write16(cpu, cpu->sp, cpu->registers[dst]);
		break;
	/*	LOW MEMORY
--------------------------------
program code
global variables
heap
           ↑ grows upward
--------------------------------
           ↓ grows downward
stack
--------------------------------
HIGH MEMORY */

	case OP_POP: // take the top value and write on dst!
		cpu->registers[dst] = mem_read16(cpu, cpu->sp);
		cpu-> sp += 2;		
		break;
		
	case OP_CALL:{ // CALL is used when you want to run a function (subroutine) and then come back to where you were(bookmarked)
		// I was reading page 100, at last it told me to go to page 400, i read page 400 and then return to pg. 102 (next to next page) pg 100-  has CALL, 101 has the target address
		uint16_t target = mem_read16(cpu, cpu->pc);
		/* CALL is a 2-word instruction
		 * Memory Layout
		 * Address   Instruction
             100       CALL
             102       200
         * after instruction is fetched pc = 102
         * so this line reads target = 200
       */
		
		cpu -> pc += 2;
		// now pc = 104 since the CPU must know where execution should continue AFTER the function returns
		
		// bookmark the return address ( pg 102 of BOOK)
		cpu-> sp -= 2;
		mem_write(cpu, cpu->sp, cpu->pc); // write address from pc to where the stack pointer points
		cpu-> pc = target;
		break;
	}
	
	case OP_RET:  //pull the bookmark from the stack
		cpu->pc = mem_read16(cpu, cpu->sp);
		cpu->sp += 2;
		break;
		
	case OP_HALT:  // Work is over
		cpu -> halted = true;
		printf("CPU is turned OFF after % " PRIu64 " tasks.\n", cpu->cycles);
		break;
		
	default:
		fprintf(stderr, "UNKNOWN TASK 0x%04X at checklist position 0x%04X\n", instruction, cpu->pc - 2);
        cpu->halted = true;
        break;
    }
    
    cpu-> cycles++;
}
// The worker keeps working until they see "Go home"
void cpu_run(CPU *cpu) {
    while (!cpu->halted) {
        cpu_step(cpu);
    }
}

	
