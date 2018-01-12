/***************************************************************
Filename: ass2.cpp
Version: 1.0
Student Name: Wenjing Wang
Student Number: 040812907
Course Name/Number: Numerical Computing CST8233
Lab Section: 303
Assignment # : Assignment 2
Assignment Name: Floating Point Spy
Due Date: December 10, 2017
Submission Date: November 06, 2017
Professor's Name: Andrew Tyler
List of Source and Header Files: ass2.c
Purpose: A utility application to show a real float number in
        its normalized hexadecimal and binary representations
        together with its exponent and normalized mantissa in memory,
        to automate what is done manually in class.
***************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef enum { FALSE = 0, TRUE } BOOL;

// Forward declaration
int *binary(int , int ); 
void convert(); 

typedef union {
	float floatNum;
	unsigned char b[sizeof(float)];
	struct {
		unsigned int mantissa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	} field;
} myfloat;

/*********************************************************************
Function Name: main
Purpose: to prompt user to make a selection of their actions
Function In parameters: void
Function Out parameters: 0 for successful execution
Version: 1.0
Student Name: Wenjing Wang
*********************************************************************/
int main(void) {
	char choice;
	BOOL RUNNING = TRUE;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/* Loop to prompt user to make a selection of their actions */
	while (RUNNING)
	{
		printf("1 = convert a float\n");
		printf("2 - quit\n");
		scanf("%c", &choice);

		switch (choice)
		{
		case '1':
			convert();
			break;
		case '2':
			RUNNING = FALSE;
			printf("quit\n");
			break;
		default:
			printf("Please enter a valid option\n");
		}
		printf("\n");
		while ((choice = getchar()) != '\n' && choice != EOF);  
	}
	return 0;
}

/****************************************************************************
Function Name: *binary
Purpose: To convert the user entered number into binary.
Function In parameters: n - the value of exponent or mantissa in binary
                        i - number of bits for exponent or mantissa
Function Out parameters: none
Version: 1.0
Student Name: Wenjing Wang
****************************************************************************/
int *binary(int n, int i) {
	unsigned int counter = 0;
	int k; // the binary value be converted

	for (i--; i >= 0; i--) {
		k = n >> i;

		/* to add space after every 4 digits */
		counter++;
		if (counter == 4)
		{
			printf(" ");
			counter = 0;
		}

		/* if k is 1, then print 1, otherwise, prints 0 */
		if (k & 1)
			printf("1");
		else
			printf("0");
	}
	return 0;
}

/****************************************************************************
Function Name: convert
Purpose: To convert the user entered number into scientific notation and binary,
         big-endian hex, little-endian hex, exponent and mantissa.
Function In parameters: none
Function Out parameters: none
Version: 1.0
Student Name: Wenjing Wang
****************************************************************************/
void convert() {
	myfloat var; 
	size_t i;
	int exponent;
	float mantissa;
	char buffer[9];

	printf("\nPlease enter the number to convert: ");
	scanf("%f", &var.floatNum);

	/* print the number in scientific notation */
	printf("float number is \t %e\n", var.floatNum);

	/* to convert the floating number to binary */
	printf("Binary: \t\t ");
	printf("%d", var.field.sign); // get the sign of number
	binary(var.field.exponent, 8); // print the exponent n of number
    binary(var.field.mantissa, 23); // print the mantissa of number
	printf("\n");

	/* to convert the big-endian hex */
	printf("Big-endian Hex: \t ");
	sprintf(buffer, "%02X", *(int *)&var.floatNum);
	if (strlen(buffer) < 8) {
		printf("0");
	}
	/* to add the space in every 2 characters */
	for (i = 0; i < strlen(buffer); i++) {
		if (i > 0 && strlen(buffer) < 8 && (i+1)%2 == 0)
			printf(" ");
		else if (i > 0 && strlen(buffer) == 8 && i%2 == 0)
			printf(" ");
		printf("%c", buffer[i]);
	}
 
	printf("\n");

    /* to convert the littlle-endian hex */
	printf("Little-endian Hex: \t ");
	for (i = 0; i < sizeof(var.b); i++) {
		printf("%02X%c", var.b[i], i < sizeof(var.b) - 1 ? ' ' : '\n');
	}
	
	/* to calculate the mantissa */
	mantissa = frexpf(var.floatNum, &exponent);
	/* to calculate the exponent */
	printf("exponent = %d\n", 127 + exponent-1); 
	printf("normalised mantissa (including the hidden bit) = %.7f", fabs(mantissa*2));
	printf("\n");
}

