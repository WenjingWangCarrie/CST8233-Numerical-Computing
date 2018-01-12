/************************************************
Filename: ass0.c
Version: 1.0
Student Name: Wenjing Wang
Student Number: 040812907
Course Name/Number: Numberical Computing CST8233
Lab Section: 303
Assignment # : Assignment 0
Assignment Name: Animation Project in C
Due Date: September 24, 2017
Submission Date: September 22, 2017
Professor's Name: Andrew Tyler
List of Source and Header Files: ass0.c
Purpose: To write a simple C language console application that
         holds the data of an animation application using
         a forward list in dynamic memory for its data. It can be insert,
         display and delete the Frames in the Animation.
*************************************************/
// ass0.c
#define _CRT_SECURE_NO_WARNINGS

#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum { FALSE = 0, TRUE } BOOL;

struct Frame {
	char* fileName;
	struct Frame* pNext;
};

struct Animation {
	struct Frame* frames;
};

// Forward declarations
void initAnimation(struct Animation*);
void insertFrame(struct Animation*);
void deleteFrames(struct Animation*);
void runFrames(struct Animation*);

int main(void)
{
	char response;
	BOOL RUNNING = TRUE;
	struct Animation A;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	initAnimation(&A);

	while (RUNNING)
	{
		printf("MENU\n 1. Insert a Frame\n 2. Delete all the Frames\n 3. Run the Animation\n 4. Quit\n");
		scanf("%c", &response);
		switch (response)
		{
		case '1':insertFrame(&A); break;
		case '2':deleteFrames(&A); break;
		case '3':runFrames(&A); break;
		case '4':RUNNING = FALSE; deleteFrames(&A); break;
		default:printf("Please enter a valid option\n");
		}
		printf("\n");
		while ((response = getchar()) != '\n' && response != EOF);// clear input buffer
	}
	return 0;
}

void runFrames(struct Animation* pA)
{
	int counter = 0;
	time_t startsec, oldsec, newsec;
	struct Frame* iterator = pA->frames;

	if (pA->frames == 0)
	{
		printf("No frames in the animation\n");
		return;
	}

	printf("Run the Animation\n");
	startsec = oldsec = time(NULL);
	while (iterator)
	{
		newsec = time(NULL);
		if (newsec > oldsec)
		{
			printf("Frame #%d, time = %d sec\n", counter++, newsec - startsec);
			printf("Image file name = %s\n", iterator->fileName);
			iterator = iterator->pNext;
			oldsec = newsec;
		}
	}
}

/*****************************************
Function Name: initAnimation
Purpose: To initialize the variables in the struct Animation.
Function In parameters: an Animation pointer
Function Out parameters: the empty content of Animation
Version: 1.0
Student Name: Wenjing Wang
*****************************************/
void initAnimation(struct Animation* pA)
{
	pA->frames = NULL; // to initialize the Animation
}

/*****************************************
Function Name: insertFrame
Purpose: To add a new Frame to Animation at a specified position.
Function In parameters: the pointer in the Animation
Function Out parameters: returned the frames inserted into Animation
Version: 1.0
Student Name: Wenjing Wang
*****************************************/
void insertFrame(struct Animation *pA)
{
	char fname[100]; 
	int counter;
	int index;

	struct Frame *iterator;
	iterator = (struct Frame *) malloc(sizeof(struct Frame)); // allocate memory for iterator
	int size = strlen(fname) + 1; // get the length of fileName
	iterator->fileName = (char *)malloc(size); // to allocate memory for fileName

	printf("Insert a Frame in the Animation\n");
	printf("Please enter the Frame filename: ");
	scanf("%s,", &fname); // catched user entered filename
	strcpy(iterator->fileName, fname); // to copy the user entered fname into the fileName that in the Frame

	struct Frame *current;
	current = pA->frames; // make the current pointer points to the Animation
	struct Frame *prev;

	if (pA->frames == NULL) // if list is empty, insert into the first position
	{
		printf("This is the first Frame in the list\n");
		iterator->pNext = pA->frames;
		pA->frames = iterator;
		return;
	}

	else // there are nodes in the list, to insert at user specified position
	{
		counter = 0;
		current = pA->frames;
		while (current != NULL) // calculate the length of the list
		{
			current = current->pNext;
			counter++;
		}

		current = pA->frames;	
		
		printf("There is %d Frame(s) in the list.  Please specify the position(<= %d) to insert at: ", counter, counter);
		scanf("%d", &index);

		if (index == 0) // only one frame in the list
		{
			iterator->pNext = pA->frames;
			pA->frames = iterator;
			return;
		}

		int counts = 0;
		current = pA->frames;
		while (counts < index) 
		{
			prev = current; // reassign the location of frame
			current = current->pNext; 
			counts++;
		}

		prev->pNext = iterator; // reassign the location of frame
		iterator->pNext = current;
		return;
	}
}

/*****************************************
Function Name: deleteFrames
Purpose: To delete all the frames in the Animation.
Function In parameters: the pointer in the Animation
Function Out parameters: return the empty frames in the Animation
Version: 1.0
Student Name: Wenjing Wang
*****************************************/
void deleteFrames(struct Animation* pA) 
{
	struct Frame* iterator; 
	
	if (pA->frames == NULL) // No node exists in the Frame - empty list
	{
		printf("");
	}	
	else // There are nodes exist in the list
	{
		iterator = pA->frames;

		while ((iterator = pA->frames) != NULL) 
		{
			pA->frames = iterator->pNext;

			free(iterator->fileName); // release all the memory of fileName
			free(iterator); // release all the memory in the Animation
		}
		printf("Delete all the Frames from the Animation");
	}

}