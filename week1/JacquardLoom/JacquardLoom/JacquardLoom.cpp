// JacquardLoom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <math.h>
#define NUMBER_OF_INSTRUCTIONS 12
#define PATTERN_WIDTH 20
#define PATTERN_LENGTH 48

// int pattern[NUMBER_OF_INSTRUCTIONS][PATTERN_WIDTH] =
// 	{
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
// 		{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
// 		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
// 		{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
// 		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// };

// pattern n.1
// int main()
// {
// 	int height = 10;
// 	(height%2==0)? height += 1 : NULL;

// 	printf("\n");
// 	printf("Jacquard loom\n");
// 	printf("\n");

// 	// task: code the 3rd pattern
// 	// task 1: handle width
// 	for (int l = 0; l < 4; l++)
// 	{
// 		for (int x = 1; x <= height; x += 2)
// 		{
// 			for (int y = 0; y < x; y++)
// 			{
// 				printf("*");
// 			}

// 			for (int z = 0; z <= (2 * height - 2 * x); z++)
// 			{
// 				printf(" ");
// 			}

// 			for (int y = 0; y < x; y++)
// 			{
// 				printf("*");
// 			}
// 			printf("\n");
// 		}
// 		// for(int x = height+1; x>=0; x--){
// 		// 	printf("*");
// 		// }

// 		for (int x = height-2; x >= 0; x -= 2)
// 		{
// 			for (int y = x; y > 0; y--)
// 			{
// 				printf("*");
// 			}
// 			for (int z = 0; z <= (2 * height - 2 * x); z++)
// 			{
// 				printf(" ");
// 			}

// 			for (int y = 0; y < x; y++)
// 			{
// 				printf("*");
// 			}
// 			printf("\n");
// 		}
// 		printf("\n\n");
// 	}
// 	// task 2: handle height
// 	printf("Hit any key to exit> ");
// 	getchar();
// }

// pattern 2
int main()
{
	int height = 10;
	(height % 2 == 0) ? height += 1 : NULL;

	printf("\n");
	printf("Jacquard loom\n");
	printf("\n");

	for (int l = 0; l < 4; l++)
	{
		for (int x = 0; x <= height; x -= 2)
		{
			for (int z = 0; z >= x; z++)
			{
				printf("*");
			}
			// printf("     ");

			// for (int y = 0; y >= height - x; y++)
			// {
				// printf("*");
			// }
			printf("\n");
		}
		// for (int x = 1; x <= height; x += 2)
		// {
		// 	for (int y = 0; y < x; y++)
		// 	{
		// 		printf("*");
		// 	}

		// 	for (int z = 0; z <= (2 * height - 2 * x); z++)
		// 	{
		// 		printf(" ");
		// 	}

		// 	for (int y = 0; y < x; y++)
		// 	{
		// 		printf("*");
		// 	}
		// 	printf("\n");
		// }
		// for(int x = height+1; x>=0; x--){
		// 	printf("*");
		// }

		// for (int x = height-2; x >= 0; x -= 2)
		// {
		// 	for (int y = x; y > 0; y--)
		// 	{
		// 		printf("*");
		// 	}
		// 	for (int z = 0; z <= (2 * height - 2 * x); z++)
		// 	{
		// 		printf(" ");
		// 	}

		// 	for (int y = 0; y < x; y++)
		// 	{
		// 		printf("*");
		// 	}
		// 	printf("\n");
		// }
		printf("\n\n");
	}
	// task 2: handle height
	printf("Hit any key to exit> ");
	getchar();
}

// pattern n.3
// int main()
// {
// 	int width = 10;

// 	printf("\n");
// 	printf("Jacquard loom\n");
// 	printf("\n");

// 	// task: code the 3rd pattern
// 	// task 1: handle width

// 	for (int l = 0; l < 4; l++)
// 	{
// 		for (int x = 0; x <= width; x += 2)
// 		{
// 			for (int z = 0; z < 2; z++)
// 			{
// 				// print the blank
// 				for (int y = 0; y <= (width - x) / 2; y++)
// 					printf(" ");

// 				// print the triangle
// 				for (int y = 0; y <= x; y++)
// 					printf("*");

// 				// print the blank
// 				for (int y = 0; y <= (width - x) / 2; y++)
// 				{
// 					printf(" ");
// 				}
// 				printf(" ");
// 			}
// 			printf("\n");
// 		}
// 		printf("\n\n");
// 	}
// 	// task 2: handle height
// 	printf("Hit any key to exit> ");
// 	getchar();
// }

// pattern n.4
// int main()
// {
// 	int width = 10;

// 	printf("\n");
// 	printf("Jacquard loom\n");
// 	printf("\n");

// 	// task: code the 3rd pattern
// 	// task 1: handle width

// 	for (int l = 0; l < 4; l++)
// 	{
// 		for (int x = 0; x <= width; x += 2)
// 		{
// 			// print the blank
// 			for (int y = 0; y <= (width - x) / 2; y++)
// 				printf(" ");

// 			// print the triangle
// 			for (int y = 0; y <= x; y++)
// 				printf("*");

// 			printf("   ");
// 			for (int y = (width - x); y >= 0; y--)
// 				printf("*");

// 			printf("   ");
// 			for (int y = 0; y <= x; y++)
// 				printf("*");
// 			printf("\n");
// 		}
// 		printf("\n\n");
// 	}
// 	// task 2: handle height
// 	printf("Hit any key to exit> ");
// 	getchar();
// }
