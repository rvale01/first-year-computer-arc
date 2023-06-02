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

int score;

bool landerThruster(double height)
{
	static int time = 0;
	static int old_time = 0;
	static double old_height = 0;

	double velocity = old_height - height;
	bool thruster_on = false;
	static double old_velocity = 0;
	static double acceleration = 0;
	acceleration = old_velocity - velocity;

	if (height >= 670 && velocity < 50.0)
	{
		thruster_on = false;
	}
	else if (height < 6500 && velocity > 107)
	{
		thruster_on = true;
	}
	else if (height < 2530)
	{
		if (velocity >= 4.5)
		{
			thruster_on = true;
		}
		else
		{
			thruster_on = false;
		}
	}
	else if (velocity > 48.5 && height < 1300)
	{
		thruster_on = true;
	}
	else if (acceleration > 0.1)
	{
		thruster_on = false;
	}
	// else if(velocity<13 && velocity>4 && height<40){
	// 	thruster_on = false;
	// }
	else if (height < 6500 && velocity > 107)
	{
		thruster_on = true;
	}
	else if (velocity > 115)
	{
		thruster_on = true;
	}
	else
	{
		thruster_on = false;
	}

	old_height = height;
	old_velocity = velocity;

	/* thruster_on = true; turns the thruster on and thruster_on = false; turns the thruster off */

	/* YOU ADD YOUR CODE HERE - REMEMBER ONLY ADD CODE TO THIS FUNCTION */

	time++; // Increment the number of times that this function has been called

	return thruster_on;
}
int drifted = 0;
int crashed = 0;
int lost = 0;

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
		if (landerThruster(h) && (f > 0.0))
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
		printf("Your lander has been lost in space\n");
		MyFile << "lost";
		MyFile << "\n\n";
		lost++;
	}
	else if (h < 5)
	{
		if ((v <= 0) && (v >= -5))
		{
			printf("Your lander has successfully landed\n");
			printf("%.2f", v);
			MyFile << "landed";
			MyFile << "\n\n";
			score++;
		}
		else
		{
			printf("Your lander has crashed\n");
			printf("%.2f", v);
			MyFile << "crashed";
			MyFile << "\n\n";
			crashed++;
		}
	}
	else
	{
		printf("Your lander is drifting above the surface\n");
		printf("%.2f", v);
		MyFile << "drifting";
		MyFile << "\n\n";
		drifted++;
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

	for (i = 0; i < 1000; i++)
	{
		simulation();
	}

	printf("\n");
	printf("Score = %d\n", (6 * score) / 100);
	printf("%d %d %d %d", score, lost, crashed, drifted);
}
