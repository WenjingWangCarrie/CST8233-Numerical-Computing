/***************************************************************
Filename: ass3.cpp
Version: 1.0
Student Name: Wenjing Wang
Student Number: 040812907
Course Name/Number: Numerical Computing CST8233
Lab Section: 303
Assignment # : Assignment 3
Assignment Name: Numerical Earthquake Simulation
Due Date: January 7, 2018
Submission Date: January 7, 2018
Professor's Name: Andrew Tyler
List of Source and Header Files: ass3.cpp
Purpose: This application uses a file of earthquake data
to run a simulation of the effect it would have on
a building.
***************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <crtdbg.h>

using namespace std;
bool running = true;

#define SIZE 256		

// Forward declaration
void calculate();

/*********************************************************************
Function Name: main
Purpose: main function to execute and display the earthquake information
Function In parameters: void
Function Out parameters: 0 for successful execution
Version: 1.0
Student Name: Wenjing Wang
*********************************************************************/
int main() {
	char choice; 
	bool running = true;

	/* to check memory leak */
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	while (running) {
		cout << "Earthquake Simulation" << endl;
		cout << "1. run the simulation\n" << "2. Quit" << endl;
		cin >> choice; 

		switch (choice) {
		case '1':
			calculate();
			break;

		case '2':
			running = false;
			cout << "Quit" << endl;
			break;

		default:
			cout << "Please enter valid choice" << endl;
			break;
		}
		cout << endl;
	} 
	return 0;
}


/****************************************************************************
Function Name: calculate
Purpose: To read file and calculate the ground acceleration associated with the
ground displacement at each time
Function In parameters: none
Function Out parameters: none
Version: 1.0
Student Name: Wenjing Wang
****************************************************************************/
void calculate() {
	char fileName[SIZE];
	char X[SIZE];
	char Y[SIZE];

	/* to open an user specified text file */
	cout << "Please enter the name of the earthquake file to open: ";
	cin >> fileName;

	/* to check if a file is exist */
	FILE *fp;
	if ((fp = fopen(fileName, "r")) == NULL) {
		cout << "Failed to open an file!" << endl;
		return;
	}
	/* to calculate the lines of a file */
	int lines = 0;
	while ((fscanf(fp, "%s", X)) != EOF && (fscanf(fp, "%s", Y)) != EOF)
		lines++;
	cout << "File opened; " << lines << " rows of data" << endl;

	/* to calculate the data */
	int i = 0;
	double* time;
	double* groundMovement;
	double* acceleration;
	double* velocity;
	double* buildingMovement;
	float k = 20.0, b = 10.0;
	float v = 0, x = 0, movement = 0;
	float step, g, acc;

	time = new double[lines]; 
	groundMovement = new double[lines];  
	acceleration = new double[lines];  
	velocity = new double[lines]; 
	buildingMovement = new double[lines];    
	acceleration[0] = 0;
	buildingMovement[0] = 0;
	velocity[0] = 0;

	rewind(fp);

	while ((fscanf(fp, "%s", X)) != EOF && (fscanf(fp, "%s", Y)) != EOF) {
		time[i] = atof(X);
		groundMovement[i] = atof(Y);
		i++;
	}

	/* to calculate the accleration first */
	for (int i = 1; i < lines - 1; ++i) {
		acc = (float)((groundMovement[i + 1] - (2 * groundMovement[i]) + groundMovement[i - 1])
			/ ((time[i] - time[i - 1])*(time[i] - time[i - 1]))) / 100;
		acceleration[i] = acc;  	
	}

	/* to use Heun’s method to calculate x and v */
	for (int i = 0; i < lines - 2; ++i) {
		step = (float)(time[i + 1] - time[i]);  
		g = (float)(acceleration[i] - (k * buildingMovement[i]) - (b * velocity[i]));  
		v = (float)(velocity[i] + (g * step)); // to get the V'i+1
		x = (float)(buildingMovement[i] + ((velocity[i] + v) / 2.0) * step); // to get the X'i+1
		movement = (float)(acceleration[i + 1] - (k * x) - (b * v)); // to get the f'(X i+1,V'i+1)
		velocity[i + 1] = velocity[i] + ((g + movement) / 2.0) * step; // to get building velocity
		buildingMovement[i + 1] = buildingMovement[i] + ((velocity[i] + v) / 2.0) * step; // to get building movement
	}

	fclose(fp);

	/* to sava data into a new file */
	FILE *fptr;
	cout << "OPEN FILE TO SAVE\n";
	cout << "Please enter the name of the file to open: ";
	cin >> fileName;
	fptr = fopen(fileName, "w");

	/* to ckeck is a file is saved successfully */
	if (fptr == NULL) {
		cout << "Error to save the file! ";
		return;
	}

	/* to save 5 columns into a file */
	for (int i = 0; i < lines - 1; ++i) {
		fprintf(fptr, "%f \t%f \t%f \t%f \t%f\n", time[i], groundMovement[i], acceleration[i], buildingMovement[i], velocity[i]);
	}
	fclose(fptr);

	/* to free all the memory in heap */
	delete[] (time);
	delete[] (groundMovement);
	delete[] (acceleration);
	delete[] (velocity);
	delete[] (buildingMovement);
}

