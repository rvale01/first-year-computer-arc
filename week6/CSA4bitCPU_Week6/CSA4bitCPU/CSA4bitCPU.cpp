// CSA4bitCPU.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

typedef unsigned char BYTE;	  /* Define 8-bit unsigned number type */
typedef unsigned char NIBBLE; /* Define 4-bit unsigned number type */

/* Opcodes */

#define OPCODE_NOP 0x00
#define OPCODE_LDI 0x01
#define OPCODE_LDD 0x02
#define OPCODE_ST 0x03
#define OPCODE_ADD 0x04
#define OPCODE_SUB 0x05
#define OPCODE_CMP 0x06
#define OPCODE_JMP 0x07
#define OPCODE_JZ 0x08
#define OPCODE_JN 0x09
#define OPCODE_JC 0x0A
#define OPCODE_JSR 0x0B
#define OPCODE_RET 0x0C
#define OPCODE_IN 0x0D
#define OPCODE_OUT 0x0E
#define OPCODE_RTI 0x0F

/* Flags */

#define Z_FLAG 0x08
#define N_FLAG 0x04
#define C_FLAG 0x02

/* Registers */

NIBBLE Accumulator; /* 4-bit Registers */
NIBBLE Status;
BYTE ProgramCounter; /* 8-bit Registers */
BYTE StackPointer;

/* Memory */
#define MEMORY_SIZE	256

NIBBLE Memory[256] =
	{
		// OPCODE_NOP,
		// OPCODE_LDI, 0xA,
		// OPCODE_LDD, 0x0, 0x3,
		// OPCODE_ST, 0x4, 0x0,
		// OPCODE_LDI, 0xB,
		// OPCODE_LDD, 0x4, 0x0,
		// OPCODE_LDI, 0x0,
		// OPCODE_JSR, 0x1, 0x6,
		// OPCODE_NOP,
		// OPCODE_NOP,
		// OPCODE_NOP,
		// OPCODE_LDI, 0xC,
		// OPCODE_ADD, 0x4, 0x0,
		// OPCODE_SUB, 0x4, 0x0,
		// OPCODE_LDI, 0x4,
		// OPCODE_CMP, 0x4, 0x0,
		// OPCODE_IN, 0x3,
		// OPCODE_OUT, 0x4,
		// OPCODE_RET
		
		OPCODE_NOP,
		OPCODE_NOP,
		OPCODE_JMP, 0x0, 0x6,
		OPCODE_NOP,
		OPCODE_ADD, 0x0, 0x9,
		0x3
	};

/* Ports */

NIBBLE InputPort[16] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
NIBBLE OutputPort[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

char fetch()
{
	NIBBLE instruction_nibble;

	instruction_nibble = Memory[ProgramCounter];
	ProgramCounter++;

	return instruction_nibble;
}

// Get address
// BYTE get_address( int mode){
// 	NIBBLE high_nibble;
// 	NIBBLE low_nibble;
// 	BYTE address;
// 	switch (mode) 
// 	{
// 		case 0: //immediate
// 			address = fetch();
// 			break;
// 		case 1: //Direct
// 	}
// }

void clear_carry_flag()
{
	Status = Status & ~C_FLAG;
}

void set_carry_flag(NIBBLE data)
{
	if ((data & 0xF0) >= 0x10)
	{
		Status = Status | C_FLAG;
	}
	else
	{
		Status = Status & ~C_FLAG;
	}
}

void set_negative_flag(NIBBLE data)
{
	if ((data & 0x08) == 0x08)
	{
		Status = Status | N_FLAG;
	}
	else
	{
		Status = Status & ~N_FLAG;
	}
}

void set_zero_flag(NIBBLE data)
{
	if (data == 0)
	{
		Status = Status | Z_FLAG;
	}
	else
	{
		Status = Status & ~Z_FLAG;
	}
}

void push(NIBBLE data)
{
	if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
		//StackPointer < MEMORY_SIZE is not necessary though, 
		//since it's initialize with a number 250, which is < MEMORY_SIZE
		Memory[StackPointer] = data;
		StackPointer--;
	}
	else {
		printf("stackpointer is invalid during pushing."); 
	}
}

NIBBLE pop()
{
	if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
		StackPointer++;
		return Memory[StackPointer];
	}	
	else {
		printf("stackpointer is invalid during popping."); 
	}
}

void execute(NIBBLE opcode)
{
	NIBBLE high_nibble;
	NIBBLE low_nibble;
	BYTE address;
	NIBBLE data;
	NIBBLE port;

	/* Decode using a switch statement */

	switch (opcode)
	{
	case OPCODE_NOP: /* No Operation */
		break;

	case OPCODE_LDI: /* Load Immediate */
		Accumulator = fetch();
		clear_carry_flag();
		set_negative_flag(Accumulator);
		set_zero_flag(Accumulator);
		break;

	case OPCODE_LDD: /* Load Direct */
		/* Read the address to get data from */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		/* Write data to the Accumulator and set the flags */
		Accumulator = Memory[address];
		clear_carry_flag();
		set_negative_flag(Accumulator);
		set_zero_flag(Accumulator);
		break;

	case OPCODE_ST: /* Store */
		/* Read the address to write the data to */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		/* Write the Accumulator to memory */
		Memory[address] = Accumulator;
		break;

	case OPCODE_ADD: /* Addition */
		/* Read the address to get data from */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		/* Do the addition and set the flags (Note there is now a set_carry_flag() routine) */
		Accumulator = Accumulator + Memory[address];
		set_carry_flag(Accumulator);
		set_negative_flag(Accumulator);
		set_zero_flag(Accumulator);
		/* Remove any overflow from the Accumulator */
		Accumulator = Accumulator & 0x0F;
		break;

	case OPCODE_SUB: /* Subtraction */
		/* Read the address to get data from */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		/* Do the subtraction and set the flags (Note there is now a set_carry_flag() routine) */
		Accumulator = Accumulator - Memory[address];
		set_carry_flag(Accumulator);
		set_negative_flag(Accumulator);
		set_zero_flag(Accumulator);
		/* Remove any overflow from the Accumulator */
		Accumulator = Accumulator & 0x0F;
		break;

	case OPCODE_CMP: /* Compare */
		/* Read the address to get data from */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		/* Do the subtraction and set the flags, remember not to set the Accumulator */
		data = Accumulator - Memory[address];
		set_carry_flag(data);
		set_negative_flag(data);
		set_zero_flag(data);
		break;

	case OPCODE_JMP:
		// get the address to jump to
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		break;

	case OPCODE_JZ:
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		if (Status & Z_FLAG == Z_FLAG)
		{
			ProgramCounter = address;
		}
		break;

	case OPCODE_JN:
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		if (Status & N_FLAG == N_FLAG)
		{
			ProgramCounter = address;
		}
		break;

	case OPCODE_JC:
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		if (Status & C_FLAG == C_FLAG)
		{
			ProgramCounter = address;
		}
		break;

	case OPCODE_JSR: /* Jump to subroutine */
		/* Read the address to jump to */
		high_nibble = fetch();
		low_nibble = fetch();
		address = (high_nibble << 4) + low_nibble;
		/* Save the Program Counter on the stack */
		high_nibble = (ProgramCounter >> 4) & 0x0F;
		low_nibble = ProgramCounter & 0x0F;
		push(high_nibble);
		push(low_nibble);
		/* Jump to the address simply by placing it in the Program Counter */
		ProgramCounter = address;
		break;

	case OPCODE_RET: /* Return from subroutine */
		/* Pop the address off of the stack */
		low_nibble = pop();
		high_nibble = pop();
		address = (high_nibble << 4) + low_nibble;
		/* Jump to the address simply by placing it in the Program Counter */
		ProgramCounter = address;
		break;

	case OPCODE_IN: /* Read from port */
		/* Read port number */
		port = fetch();
		/* Read from port */
		Accumulator = InputPort[port];
		/* Set flags */
		clear_carry_flag();
		set_negative_flag(Accumulator);
		set_zero_flag(Accumulator);
		break;

	case OPCODE_OUT: /* Write to port */
		/* Read port number */
		port = fetch();
		/* Write to port */
		OutputPort[port] = Accumulator;
		break;

	case OPCODE_RTI: /* Return from interrupt */
		/* Pop the status register off of the stack */
		Status = pop();
		/* Pop the accumulator off of the stack */
		Accumulator = pop();
		/* Pop the address off of the stack */
		low_nibble = pop();
		high_nibble = pop();
		address = (high_nibble << 4) + low_nibble;
		/* Jump to the address simply by placing it in the Program Counter */
		ProgramCounter = address;
		break;

	default:
		break;
	}
}

int main()
{
	int sanity;
	int i;
	NIBBLE opcode;

	printf("CSA 4-bit CPU Emulator\n");
	printf("\n");

	/* Initialise Registers */

	Accumulator = 0;
	Status = 0;
	ProgramCounter = 0;
	StackPointer = 0xFB;

	/* Main Fetch/Decode/Execute Loop */

	sanity = 0;

	printf("        A Z N C PC SP    Input Ports                        Output Ports\n");

	while (sanity < 100)
	{
		printf("%02X: ", ProgramCounter); /* Memory location */

		opcode = fetch();

		switch (opcode)
		{
		case OPCODE_NOP:
			printf("NOP ");
			break;
		case OPCODE_LDI:
			printf("LDI ");
			break;
		case OPCODE_LDD:
			printf("LDD ");
			break;
		case OPCODE_ST:
			printf("ST  ");
			break;
		case OPCODE_ADD:
			printf("ADD ");
			break;
		case OPCODE_SUB:
			printf("SUB ");
			break;
		case OPCODE_CMP:
			printf("CMP ");
			break;
		case OPCODE_JMP:
			printf("JMP ");
			break;
		case OPCODE_JZ:
			printf("JZ  ");
			break;
		case OPCODE_JN:
			printf("JN  ");
			break;
		case OPCODE_JC:
			printf("JC  ");
			break;
		case OPCODE_JSR:
			printf("JSR ");
			break;
		case OPCODE_RET:
			printf("RET ");
			break;
		case OPCODE_IN:
			printf("IN  ");
			break;
		case OPCODE_OUT:
			printf("OUT ");
			break;
		case OPCODE_RTI:
			printf("RTI ");
			break;
		default:
			break;
		}

		execute(opcode);

		printf("%1X ", Accumulator); /* Accumulator */
		if ((Status & Z_FLAG) == Z_FLAG)
			printf("1 ");
		else
			printf("0 "); /* zero flag */
		if ((Status & N_FLAG) == N_FLAG)
			printf("1 ");
		else
			printf("0 "); /* negative flag */
		if ((Status & C_FLAG) == C_FLAG)
			printf("1 ");
		else
			printf("0 ");				 /* carry flag */
		printf("%02X ", ProgramCounter); /* Program Counter */
		printf("%02X ", StackPointer);	 /* Stack Pointer */
		printf("   ");
		for (i = 0; i < 16; i++)
			printf("%1X ", InputPort[i]); /* Input Ports */
		printf("   ");
		for (i = 0; i < 16; i++)
			printf("%1X ", OutputPort[i]); /* Output Ports */
		printf("\n");

		sanity++; // We stop the emulator after 100 cycles, in reality the CPU would run forever
	}
}
