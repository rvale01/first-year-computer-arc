// SpaceLander.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

ofstream MyFile("filename.txt");

double f_start = 100.0;
double t_max = 500.0;

double A_start = 5.0;
double h_start = 10000.0;
double v_start = -100.0;
double g = 0.3;

double delta_f = 2.0;
double delta_t = 1.0;

int score, crashed, lost, drifting;

bool landerThruster(double height, double vel)
{
	static int time = 0;
	static double old_height = 0;
	double velocity;

	bool thruster_on = true;
	thruster_on = true;

	if (height > 810 && velocity > 45)
	{
		if (time % 3 == 1 || time % 3 == 2)
		{
			thruster_on = true;
		}
		else
		{
			thruster_on = false;
		}
	}
	if (height < 685 && velocity > 4.8)
	{
		if (time % 3 == 1 || time % 3 == 2)
		{
			thruster_on = true;
		}
		else
		{
			thruster_on = false;
		}
	}
	if (height < 500 && velocity > 35)
	{
		thruster_on = true;
	}
	if (height > 50 && height < 200 && velocity > 8)
	{
		thruster_on = true;
	}
	/* thruster_on = true; turns the thruster on and thruster_on = false; turns the thruster off */

	/* YOU ADD YOUR CODE HERE - REMEMBER ONLY ADD CODE TO THIS FUNCTION */

	// printf("%.2f  %.2f %d  %.2f\n", height, vel, thruster_on, old_height);
	MyFile << vel;
	MyFile << "  ";
	MyFile << height;
	MyFile << "\n";
	MyFile << thruster_on;
	MyFile << "\n";
	time++; // Increment the number of times that this function has been called

	return thruster_on;
}

void simulation()
{
	double h;
	double h0;
	double v;
	double v0;
	double f;
	double f0;
	double a;
	double A;
	bool thrust_on = false;
	double t;
	double t0;

	A_start = 2.5 + (double)(rand() % 3);
	h_start = 5000.0 + (double)(rand() % 8000);
	v_start = -125.0 + (double)(rand() % 50);
	g = 0.1 + (double)(rand() % 3) / 10.0;

	h = h_start;
	v = v_start;
	f = f_start;
	A = A_start;
	t = 0.0;

	while ((h <= 2 * h_start) && (h >= 0) && (t <= t_max))
	{
		t0 = t;
		v0 = v;
		h0 = h;
		f0 = f;

		if (landerThruster(h, v) && (f > 0.0))
		{
			// Update acceleration

			a = A - g;

			// Update fuel

			f = f0 - delta_f * delta_t;
		}
		else
		{
			// Update acceleration

			a = -g;
		}

		// Update velocivy

		v = v0 + a * delta_t;

		// Update height

		h = h0 + v0 * delta_t + (a * delta_t * delta_t) / 2;

		// Update time

		t = t0 + delta_t;

		//printf("%f\t%f\t%f\t%f\n", h, v, a, f);
	}

	if (h >= 2 * h_start)
	{
		// MyFile << "Your lander has been lost in space\n";
		printf("Your lander has been lost in space\n");
		lost++;
	}
	else if (h < 5)
	{
		if ((v <= 0) && (v >= -5))
		{
			// MyFile << "Your lander has successfully landed\n";
			printf("Your lander has successfully landed\n");
			score++;
		}
		else
		{
			// MyFile << "Your lander has crashed\n";
			printf("Your lander has crashed\n");
			crashed++;
		}
	}
	else
	{
		// MyFile << "Your lander is drifting above the surface\n";
		printf("Your lander is drifting above the surface\n");
		drifting++;
	}
}

int main()
{
	time_t t;
	int i;

	score = 0;

	/* Intializes random number generator */
	srand((unsigned)time(&t));

	printf("The UWE Landing Algorithm \n\n");

	for (i = 0; i < 4; i++)
	{
		simulation();
	}

	printf("\n");
	// printf("Score = %d\n", (6 * score) / 100);
	// printf("Score = %d\n", (6 * drifting) / 100);
	// printf("Score = %d\n", (6 * crashed) / 100);
	// printf("Score = %d\n", (6 * lost) / 100);
	printf(" %d  %d  %d  %d", score, drifting, crashed, lost);
}
