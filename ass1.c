/****************************************************************************************************************************************
Filename: ass1.c
Version: 1.0
Author: Felipe de Paula Souza Filho
Student Number: 040843714
Course: Numerical CST8233
Lab Section: 300
Assignment number : 1
Due date: February 17 2019
Submition date: February 16 2019
Professor name: Andrew Tyler
Purpose: To investigate a less accurate but faster Maclaurin Series approximation using the formula for the movement D(t) = e^-tcos(t)
		 followed by the number of terms and range in the series specified by the user
****************************************************************************************************************************************/
// ass1.c
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum { FALSE = 0, TRUE } BOOL;

// Forward declarations
void EvaluateSeries();

/****************************************************************************************************************************************
Function name: main
Purpose: Display main message and run function to evaluate the series
In parameters: None
Out parameters: void
Version: 1.0
Author: Felipe de Paula Souza Filho
****************************************************************************************************************************************/
int main(void)
{
	int response;
	BOOL RUNNING = TRUE;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	while (RUNNING)
	{
		printf("Evaluate the Maclaurin Series approximation to exp(-t)*cos(t)\n\n1: Evaluate the series\n2: quit\n\n");
		scanf("%d", &response);

		switch (response)
		{
		case 1:EvaluateSeries(); break;
		case 2:RUNNING = FALSE; break;
		default:printf("Please enter a valid option\n\n");
			break;
		}
		getchar();

	}
	return 0;
}// end of main

/****************************************************************************************************************************************
Function name: Evaluate
Purpose: Evaluate the series according to the number of terms and range in the series specified by the user
In parameters: None
Out parameters: void
Version: 1.7
Author: Felipe de Paula Souza Filho
****************************************************************************************************************************************/
void EvaluateSeries()
{
	// Local variables
	int numberOfTerms = 0;
	double firstTerm = 0;
	double numIncrement = 0;
	double range = 0;
	double t = 0;
	double seriesValue = 0;
	double movimentD = 0;
	double exactError = 0;
	double truncationError = 0;

	//While the user wishes to continue, the user is asked to choose the number of terms in the series up to a maximum of five
	printf("\nEvaluating the series\nPlease enter the number of terms in the series (max 5 terms): ");
	scanf("%d", &numberOfTerms); //get user's term

	if (numberOfTerms <= 0 || numberOfTerms > 5) { // reject invalid integers
		printf("\nWrong input... Please choose a number betwenn 1 and 5 next time. \n\n");
		return;
	}
	if (numberOfTerms > 0 || numberOfTerms <= 5) { // make sure the number is in betwen the max of 5 terms
		printf("\nPlease enter the range of t to evaluate in 10 increments( 0.0 < t < +2.0): ");
		scanf("%lf", &range);// get user's range number 
	}

	//Then the user selects a range of t, somewhere between 0 and +2.0

	if (range <= 0 || range > 2) { // reject values outside this range
		printf("\nWrong range... Please choose a range betwenn 1 and 2 next time. \n\n");
		return;
	}

	// Display top series message
	printf("\nMACLAURIN SERIES\n");
	printf(" x\t        Series\t        Exact\t       Exact %% Error\tTrunc. %% Error\t \n");

	//the series is evaluated from 0 in ten equal increments
	for (int i = 0; i <= 10; i++) {

		// The result is aways the series value - the first term depending on the number of terms selected by the user
		if (numberOfTerms == 1) {
			seriesValue = 1;
			firstTerm = -t;
		}
		else if (numberOfTerms == 2) {
			seriesValue = 1 - t;
			firstTerm = -(-t * -t * -t) / 3;
		}
		else if (numberOfTerms == 3) {
			seriesValue = 1 - t - (-t * -t * -t) / 3;
			firstTerm = -(-t * -t * -t * -t) / 6;
		}
		else if (numberOfTerms == 4) {
			seriesValue = 1 - t - (-t * -t * -t) / 3 - (-t * -t * -t * -t) / 6;
			firstTerm = -(-t * -t * -t * -t * -t) / 30;
		}
		else if (numberOfTerms == 5) {
			seriesValue = 1 - t - (-t * -t * -t) / 3 - (-t * -t * -t * -t) / 6 - (-t * -t * -t * -t * -t) / 30;
			firstTerm = (-t * -t * -t * -t * -t * -t * -t) / 630;
		}
		else if (numberOfTerms == 6) {
			seriesValue = 1 - t - (-t * -t * -t) / 3 - (-t * -t * -t * -t) / 6 - (-t * -t * -t * -t * -t) / 30 - (-t * -t * -t * -t * -t * -t * -t) / 630;
			firstTerm = (-t * -t * -t * -t * -t * -t * -t * -t) / 2520;
		}

		// For each value of t the Maclaurin series approximation to the function is output together with the exact value calculated using the math library functions exp and cos.
		movimentD = exp(-t)*cos(t); // The formula for the movement D

		// The error that results from using the series approximation is calculated in two different ways.
		exactError = 100 * (movimentD - seriesValue) / movimentD;// From comparison with the exact value calculated using the math library functions
		truncationError = 100 * (firstTerm / seriesValue);//From the first truncated term

		// Display Maclaurin series values
		printf("%.3e\t%.5e\t%.5e\t%.5e\t%.5e\n", t, seriesValue, movimentD, exactError, truncationError);

		numIncrement = range / 10;
		t += numIncrement;

	}// end of loop
	printf("\n");

}// end of function EvaluateSeries

