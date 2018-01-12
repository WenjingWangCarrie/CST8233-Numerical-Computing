/***************************************************************
Filename: ass1.cpp
Version: 1.0
Student Name: Wenjing Wang
Student Number: 040812907
Course Name/Number: Numerical Computing CST8233
Lab Section: 303
Assignment # : Assignment 1
Assignment Name: Catastrophic Vibration
Due Date: November 26, 2017
Submission Date: November 24, 2017
Professor's Name: Andrew Tyler
List of Source and Header Files: ass1.cpp
Purpose: To investigate the series approximation to
the motion for its accuracy over initial
times up to 4 seconds after the start of the vibration.
***************************************************************/
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
bool running = true;

// Forward declaration
void evaluate();

/*********************************************************************
Function Name: main
Purpose: main function to execute and display the maclaurin series
Function In parameters: void
Function Out parameters: 0 for successful execution
Version: 1.0
Student Name: Wenjing Wang
*********************************************************************/
int main(void) {
	char choice;
	bool running = true;

	/* Loop to prompt user to make a selection of their actions */
	while (running) {
		cout << "Evaluate the Maclaurin Series approximation to D(t) = exp(t)*cos(t)\n" << endl;
		cout << "1: Evaluate the series\n2: quit\n" << endl;

		cin >> choice;

		switch (choice) {
		case '1':
			evaluate();
			break;
		case '2':
			running = false;
			cout << "quit" << endl;
			break;
		default:
			cout << "Please enter a valid option" << endl;
		}
		cout << endl;
	}
	return 0;
}

/****************************************************************************
Function Name: evaluate
Purpose: To execute the maclaurin series based on user enterd terms and range
Function In parameters: none
Function Out parameters: none
Version: 1.0
Student Name: Wenjing Wang
****************************************************************************/
void evaluate() {
	double range, increments;
	int terms;

	cout << "Evaluating the series" << endl;
	/* to prompt user to enter non-zero terms they want */
	do {
		cout << "Please enter the number of (non-zero) terms in the series (1, 2, 3, 4, 5 or 6):" << endl;
		cin >> terms;
		cout << endl;
	} while (terms <= 0 || terms > 6);

	/* to prompt user to enter the range of t_v they want */
	do {
		cout << "Please enter the range of t to evaluate in 10 increments (0.0 < t < +4.0):" << endl;
		cin >> range;
		cout << endl;
	} while (range < 0.0 || range > 4.0);

	double t_v, exact_v, ser_v, first_trun, rExactE, rSerE;
	t_v = exact_v = ser_v = rExactE = rSerE = 0.0;

	cout << "MACLAURIN SERIES" << endl;
	cout << setw(10) << " t " << setw(20) << " D(t) Series " << setw(20) << " D(t) Exact " << setw(20) << " %RExactE " << setw(20) << " %RSerE " << endl;
	/* while t_v equals to 0 */
	ser_v = 1;
	exact_v = exp(t_v) * cos(t_v);

	/* To display the t value as scientific notation 3 digits */
	cout << setprecision(3) << std::scientific;
	cout << t_v << setw(20);
	/* To display the rest values as scientific notation 5 digits */
	cout << setprecision(5) << std::scientific;
	cout << ser_v << setw(20) << exact_v << setw(20) << rExactE << setw(20) << rSerE << endl;

	/* Loop to calculate the t value, series value, exact value, exact error and series error */
	for (int i = 1; i <= 10; i++) {
		increments = range / 10;
		t_v = t_v + increments;

		/* The different situations when user entered terms number */
		if (terms == 1) {
			ser_v = 1;
			first_trun = t_v;
		}
		else if (terms == 2) {
			ser_v = 1 + t_v;
			first_trun = -(t_v * t_v * t_v) / 3;
		}
		else if (terms == 3) {
			ser_v = 1 + t_v - (t_v * t_v * t_v) / 3;
			first_trun = -(t_v * t_v * t_v * t_v) / 6;
		}
		else if (terms == 4) {
			ser_v = 1 + t_v - (t_v * t_v * t_v) / 3 - (t_v * t_v * t_v * t_v) / 6;
			first_trun = -(t_v * t_v * t_v * t_v * t_v) / 30;
		}
		else if (terms == 5) {
			ser_v = 1 + t_v - (t_v * t_v * t_v) / 3 - (t_v * t_v * t_v * t_v) / 6 - (t_v * t_v * t_v * t_v * t_v) / 30;
			first_trun = (t_v * t_v * t_v * t_v * t_v * t_v * t_v) / 630;
		}
		else if (terms == 6) {
			ser_v = 1 + t_v - (t_v * t_v * t_v) / 3 - (t_v * t_v * t_v * t_v) / 6 - (t_v * t_v * t_v * t_v * t_v) / 30 + (t_v * t_v * t_v * t_v * t_v * t_v * t_v) / 630;
			first_trun = (t_v * t_v * t_v * t_v * t_v * t_v * t_v * t_v) / 2520;
		}

		/* The formula to calculate exact_v, RExactE and RSerE */
		exact_v = exp(t_v) * cos(t_v);
		rExactE = 100 * (exact_v - ser_v) / exact_v;
		rSerE = 100 * first_trun / ser_v;

		/* To display the t value as scientific notation 3 digits */
		cout << setprecision(3) << std::scientific;
		cout << t_v << setw(20);
		/* To display the rest values as scientific notation 5 digits */
		cout << setprecision(5) << std::scientific;
		cout << ser_v << setw(20) << exact_v << setw(20) << rExactE << setw(20) << rSerE << endl;
	}
}