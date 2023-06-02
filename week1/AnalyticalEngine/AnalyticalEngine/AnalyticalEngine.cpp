// AnalyticalEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string.h>
#include <iostream>  
#include <string> 

#define MAX_PROGRAM_SIZE	100

//haixia: important!
//Program[Program_Index] is the place where we put our instructions step by step
//char Program[MAX_PROGRAM_SIZE][100] =
//{
//	"N0 6",
//	"N1 1",
//	"N2 1",

//	"*",
//	"L1",
//	"L0",

//	"P",
//	"S1",

//	"-",
//	"L0",
//	"L2",

//	"S0",


//	"L2",
//	"L0",

//	"CB?11",
//	"H",
//	"",
//	"",
//	"",
//	"",
//	"",
//	"",
//	""
//};
//haixia: fib
//1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, …
//add first 2 numbers, plan: save the result to the second data holder. 
//Before over-writing the second data holder, lets save the original second number
//plan: save the second number to the first dataholder.
//Before over-writing the first data holder, lets save the original first number

	//haixia
	//"N0 0", //this is the first number
	//"N1 1", // this is the second number
	//"N2 0",	//always make it 0, for the purpose of saving the second number
	//"N3 0",
	////=============
	//"+",
	//"L1",
	//"L2",
	////"P",
	//"S3",//save the second number to dataholder 3
	////=================here it does the main job===============
	//"+",// first, we need to specify operation
	//"L0",//load the value at the memory loation 0
	//"L1",//load the value at the memory loation 1
	//"P",//print the result on the Egress Axis
	//"S1",// save the current value 
	////on the Egress Axis at the specified memory location in the store (location 1)

	////=============move the second number to the first data holder
	//"+",// first, we need to specify operation
	//"L3",//load the value at the memory loation 0
	//"L2",//load the value at the memory loation 1
	////"P",//print the result on the Egress Axis
	//"S0",// save the current value 
	//
	//
	//"CB?13",//B: move backward for 15 steps
	//"H",
	//"",
	//"",
	//"",
	//"",
	//"",
	//"",
	//""
	//haixia


//Fib solution from one of our students
char Program[MAX_PROGRAM_SIZE][100] =
{
	// FIBONACCI
	// "N0 1",
	// "N1 1",

	// "+",
	// "L0",
	// "L1",

	// "S0",
	// "P",

	// "+",

	// "L0",
	// "L1",

	// "S1",
	// "P",

	// "CB?10",
	// "H"

	"N0 3",
	"N1 3",
	"N2 2",
	"N3 8",
	

	"+",
	"L0",
	"L1",

	"S0",
	"P",
	
	"+",
	"L2",
	"L3",
	"S1",
	"P",

	"*",
	"L1",
	"L0",

	"S2",
	"P",

	"H",
	"",
	"",
	"",
	"",
	"",
	""
};

//here is the program for: 
//a = (b + 3) * (c + 2) for different values of b and c
//char Program[MAX_PROGRAM_SIZE][100] =
//{
//	"N0 88",//b
//	"N1 99",//c
//	"N2 2",//b
//	"N3 3",//c
//	"N4 0",//: result a
//
//	"+",
//	"L0",
//	"L2",
//
//	"S0",//save a+2 to location 0
//	"P",
//
//	"+",
//	"L1",
//	"L3",
//
//	"S1",//save b+3 to location 1
//	"P",
//
//	"*",
//	"L0",
//	"L1",
//
//	"S4",
//	"P",
//	"H"
//};

int Program_Index;

char program_line[100];


/* Input registers to the Mill (CPU) */
int PrimedIngressAxis;
int IngressAxes;

#define INGRESS_LOAD	0
#define INGRESS_CALC	1
int Operation;

/* Output registers from the Mill (CPU) */
int PrimedEgressAxis;
int EgressAxis;

/* The carry flag */
int Run_upLever;

/* Memory */
int Store[1000];

/* The CPU related data*/
#define OPERATION_NULL		0
#define OPERATION_ADD		1
#define OPERATION_SUBTRACT	2
#define OPERATION_MULTIPLY	3
#define OPERATION_DIVIDE	4
#define OPERATION_HALT		5

int MillOperation;


void initMill()
{
	int i;

	Program_Index = 0;

	PrimedIngressAxis = 0;
	IngressAxes = 0;
	Operation = INGRESS_LOAD;

	PrimedEgressAxis = 0;
	EgressAxis = 0;
	Run_upLever = 0;

	for (i = 0; i < 1000; i++)
	{
		Store[i] = 0;
	}

	MillOperation = OPERATION_NULL;
}
/*Run - Up Lever : The Run - Up Lever is important for evaluating booleansand loops.The lever switches from its normal down position into its up position in either of the following two cases :
The sign on the result of the equation is different then the sign on the first number in the equation, on Ingress Axis 1. Thus, if you do the equation 4 – 9, the run up lever will be set because the result(-5) has a different sign then Ingress Axis 1 (the number 4.)
The resulting answer is greater than 50 digits long.If you try and divide a 100 digit number by a 2 digit number, the run up lever will be set.*/
void setRunupLever(int first, int second, int result) {
	if ((first>0 && result<0) || (first<0 && result >0) || result>55){
		Run_upLever = 0;//stop running
	}
	else {
		Run_upLever = 1;// 1: means: we can keep running
	}
}
void doCalculation(int store_index)
{
	int  debug;

	debug = 0;

	switch (MillOperation)
	{
	case OPERATION_ADD:
		EgressAxis = IngressAxes + Store[store_index];
		//Run_upLever = 0; /* Not implemented correctly */
		setRunupLever(IngressAxes, Store[store_index], EgressAxis);
		break;

	case OPERATION_SUBTRACT:
		EgressAxis = IngressAxes - Store[store_index];
		if (IngressAxes < Store[store_index])
		{
			Run_upLever = 1;
		}
		else
		{
			Run_upLever = 0;
		}
		break;

	case OPERATION_MULTIPLY:
		EgressAxis = IngressAxes * Store[store_index];
		Run_upLever = 0;
		break;

	case OPERATION_DIVIDE:
		EgressAxis = IngressAxes / Store[store_index];
		Run_upLever = 0;
		break;

	////haixia: Fib
		//Wrong! we want to do Fib just using the operations we already have: sub, sum, 
	//case OPERATION_FIB:  
	//{int n1 = 0, n2 = 1, n3, i, number;//we need the outer {}, otherwise, we wil get an error: n1 and n2 ...by default
	//for (int i = 2; i < 10; ++i) //output the first 10 numbers in the fibonacci sequence
	//{
	//	n3 = n1 + n2;
	//	std::cout << n3 << " ";
	//	n1 = n2;
	//	n2 = n3;
	//}
	//break;
	//}

	default:
		break;
	}

	if (debug == 1) printf("Egress Axis = %d, Run Up Lever = %d\n", EgressAxis, Run_upLever);
}



void executeInstruction(char* program_line)
{
	int  store_index;
	int  number;
	int  direction;
	int  debug;
	char backwards_forwards;
	char conditional;

	debug = 0;

	if (sscanf(program_line, "N%d %d", &store_index, &number) == 2)
	{
		if ((store_index >= 0) && (store_index < 1000))
		{
			Store[store_index] = number;
			if (debug == 1) printf("Store %d in Store[%d]\n", number, store_index);
		}
		else
		{
			printf("Store index out of range [0 - 999]\n");
		}
	}
	else if (strcmp(program_line, "+") == 0)
	{
		MillOperation = OPERATION_ADD;
		if (debug == 1) printf("Set Mill (CPU) for Add\n");
	}
	else if (strcmp(program_line, "-") == 0)
	{
		MillOperation = OPERATION_SUBTRACT;
		if (debug == 1) printf("Set Mill (CPU) for Subtract\n");
	}
	else if (strcmp(program_line, "x") == 0)
	{
		MillOperation = OPERATION_MULTIPLY;
		if (debug == 1) printf("Set Mill (CPU) for Multiply\n");
	}
	else if (strcmp(program_line, "*") == 0)
	{
		MillOperation = OPERATION_MULTIPLY;
		if (debug == 1) printf("Set Mill (CPU) for Multiply\n");
	}
	else if (strcmp(program_line, "/") == 0)
	{
		MillOperation = OPERATION_DIVIDE;
		if (debug == 1) printf("Set Mill (CPU) for Divide\n");
	}
	//else if (strcmp(program_line, "/") == 0)
	//{
	//	MillOperation = OPERATION_FIB;//haixia added
	//	if (debug == 1) printf("Set Mill (CPU) for Fib\n");
	//}
	else if (sscanf(program_line, "L%d", &store_index) == 1)
	{
		if ((store_index >= 0) && (store_index < 1000))
		{
			switch (Operation)
			{
			case INGRESS_LOAD:
				IngressAxes = Store[store_index];
				if (debug == 1) printf("Load Ingress Axes from Store[%d]\n", store_index);
				Operation = INGRESS_CALC;
				break;

			case INGRESS_CALC:
				if (debug == 1) printf("Calculate...\n");
				doCalculation(store_index);
				Operation = INGRESS_LOAD;
				break;

			default:
				Operation = INGRESS_LOAD;
				break;
			}
			//if (debug == 1) printf("Operation = %d\n", Operation);
		}
		else
		{
			printf("Store index out of range [0 - 999]\n");
		}
	}
	else if (sscanf(program_line, "Z%d", &store_index) == 1)
	{
		if ((store_index >= 0) && (store_index < 1000))
		{
			switch (Operation)
			{
			case INGRESS_LOAD:
				IngressAxes = Store[store_index];
				if (debug == 1) printf("Load Ingress Axes from Store[%d]\n", store_index);
				Operation = INGRESS_CALC;
				break;

			case INGRESS_CALC:
				if (debug == 1) printf("Calculate...\n");
				doCalculation(store_index);
				Operation = INGRESS_LOAD;
				break;

			default:
				Operation = INGRESS_LOAD;
				break;
			}
			Store[store_index] = 0;
		}
		else
		{
			printf("Store index out of range [0 - 999]\n");
		}
	}
	else if (sscanf(program_line, "S%d", &store_index) == 1)
	{
		if ((store_index >= 0) && (store_index < 1000))
		{
			Store[store_index] = EgressAxis;
			if (debug == 1) printf("Store Egress Axis to Store[%d]\n", store_index);
		}
		else
		{
			printf("Store index out of range [0 - 999]\n");
		}
	}
	else if (sscanf(program_line, "L%d'", &store_index) == 1)
	{
		if ((store_index >= 0) && (store_index < 1000))
		{
			PrimedIngressAxis = Store[store_index];
			if (debug == 1) printf("Load Primed Ingress Axis from Store[%d]\n", store_index);
		}
		else
		{
			printf("Store index out of range [0 - 999]\n");
		}
	}
	else if (sscanf(program_line, "Z%d'", &store_index) == 1)
	{
		if ((store_index >= 0) && (store_index < 1000))
		{
			PrimedIngressAxis = Store[store_index];
			if (debug == 1) printf("Load Primed Ingress Axis from Store[%d]\n", store_index);
			Store[store_index] = 0;
		}
		else
		{
			printf("Store index out of range [0 - 999]\n");
		}
	}
	else if (sscanf(program_line, "S%d'", &store_index) == 1)
	{
		if ((store_index >= 0) && (store_index < 1000))
		{
			Store[store_index] = PrimedEgressAxis;
			if (debug == 1) printf("Store Primed Egress Axis to Store[%d]\n", store_index);
		}
		else
		{
			printf("Store index out of range [0 - 999]\n");
		}
	}
	else if (sscanf(program_line, "C%c%c%d", &backwards_forwards, &conditional, &number) == 3)
	{
		if (debug == 1) printf("Jump");

		switch (backwards_forwards)
		{
		case 'B':
		case 'b':
			direction = -1;
			if (debug == 1) printf(" backwards");
			break;

		case 'F':
		case 'f':
			direction = 1;
			if (debug == 1) printf(" forwards");
			break;

		default:
			direction = 0;
			break;
		}

		switch (conditional)
		{
		case '+':
			Program_Index = Program_Index + direction * number - 1;
			if (debug == 1) printf(" unconditionally\n");
			break;

		case '?'://haixia: see how it performes 'if' statement using Run_upLever
			if (Run_upLever == 1) Program_Index = Program_Index + direction * number - 1;
			if (debug == 1) printf(" conditionally\n");
			break;

		default:
			break;
		}
	}
	else if (strcmp(program_line, "B") == 0)
	{
		printf("Beep\n");
	}
	else if (strcmp(program_line, "H") == 0)
	{
		printf("Halt\n");
		MillOperation = OPERATION_HALT;
	}
	else if (strcmp(program_line, "P") == 0)
	{
		printf("Output = %d\n", EgressAxis);
	}
}


void fetchInstruction()
{
	strcpy(program_line, Program[Program_Index]);

	printf("Executing %3d: %s\n", Program_Index, program_line);

	Program_Index++;
}


int main()
{
	initMill();

	printf("Babbage's Analytical Engine\n");

	Program_Index = 0;

	while ((MillOperation != OPERATION_HALT) && (Program_Index < MAX_PROGRAM_SIZE))
	{
		fetchInstruction();//haixia: 
		//Program[Program_Index] is the place where we put our instructions step by step
		executeInstruction(program_line);
	}

	printf("Press any key to exit> ");
	getchar();
}


