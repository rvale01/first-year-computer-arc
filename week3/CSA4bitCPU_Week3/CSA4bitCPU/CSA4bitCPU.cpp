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

NIBBLE Memory[256] = {
	OPCODE_LDI, 8,
	OPCODE_LDI, 9,
	OPCODE_LDI, 0,
	OPCODE_LDD, 0, 0,
	OPCODE_ST, 2, 0,
	OPCODE_LDD, 0, 1,
	OPCODE_ST, 2, 1,
	OPCODE_NOP
};

/* Ports */

NIBBLE InputPort[16];
NIBBLE OutputPort[16];

char fetch()
{
	NIBBLE instruction_nibble;

	instruction_nibble = Memory[ProgramCounter];
	ProgramCounter++;

	return instruction_nibble;
}

void clear_carr_flag()
{
	Status = Status & ~Z_FLAG;
}

void test_neg_flag(NIBBLE value)
{
	if ((value & 0x08) == 0x08)
	{
		Status = Status | N_FLAG; //negative number
	}
	else
	{
		Status = Status & ~N_FLAG; //positive number
	}
}
void test_zero_flag(NIBBLE value)
{
	if (value == 0)
	{
		Status = Status | Z_FLAG; // Zero number
	}
	else
	{
		Status = Status & ~Z_FLAG; //non-zero number
	}
}

void execute(NIBBLE opcode)
{
	BYTE address;
	NIBBLE Hi;
	NIBBLE Lo;

	switch (opcode)
	{
	case OPCODE_NOP: //no operation
		printf(" NOP ");
		break;

	case OPCODE_LDI: //load immediate
		printf(" LDI ");
		Accumulator = fetch(); //fetch the data and load it in the accumulator
		clear_carr_flag();
		test_neg_flag(Accumulator);
		test_zero_flag(Accumulator);
		break;

	case OPCODE_LDD:
		printf(" LDD ");
		Hi = fetch();
		Lo = fetch();
		address = (Hi << 4) + Lo;
		Accumulator = Memory[address];
		clear_carr_flag();
		test_neg_flag(Accumulator);
		test_zero_flag(Accumulator);
		break;

	case OPCODE_ST:
		printf(" ST ");
		Hi = fetch();
		Lo = fetch();
		address = (Hi << 4) + Lo;
		Memory[address] = Accumulator;
		break;

	case OPCODE_ADD:
		break;
	case OPCODE_SUB:
		break;
	case OPCODE_CMP:
		break;
	case OPCODE_JMP:
		break;
	case OPCODE_JZ:
		break;
	case OPCODE_JN:
		break;
	case OPCODE_JC:
		break;
	case OPCODE_JSR:
		break;
	case OPCODE_RET:
		break;
	case OPCODE_IN:
		break;
	case OPCODE_OUT:
		break;
	case OPCODE_RTI:
		break;
	default:
		break;
	}

	printf("0x%X 0x%X/n", Accumulator, Status);
}

int main()
{
	int sanity;
	NIBBLE opcode;

	printf("CSA 4-bit CPU Emulator\n");

	/* Initialise Registers */

	Accumulator = 0;
	Status = 0;
	ProgramCounter = 0;
	StackPointer = 0xFB;

	/* Main Fetch/Decode/Execute Loop */

	sanity = 0;

	while (sanity < 100)
	{
		opcode = fetch();
		execute(opcode);

		sanity++; // We stop the emulator after 100 cycles, in reality the CPU would run forever
	}
}
