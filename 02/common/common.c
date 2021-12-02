//some generic functions that will probably be usefull in more projects
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"


int stdinToIntArr(int** intArr, int* elements)
{
	if(*intArr)
	{
		printf("stdinToIntArr(): intArr might already be created\n");
		exit(0);
	}

	int maxSize = 100;
	const int stepSize = 100;
	int size = 0;
	int* newArray = (int*)malloc(maxSize * sizeof(int)); 
    while(scanf("%d", newArray + size++) > 0)
	{
		//buffer full
		if(size >= maxSize)
		{
			//allocate some more
			maxSize += stepSize;
			newArray = (int*)realloc(newArray, maxSize * sizeof(int));
		}
	}

	//set the return values
	*intArr = newArray;
	*elements = size;

	return maxSize;
}

int stdinToStrArr(char*** stringArr, int* elements, const int stringsize)
{
	if(*stringArr)
	{
		printf("stdinToStrArr(): stringArr might already be created\n");
		exit(0);
	}

	int maxSize = 100;
	const int stepsize = 100;
	int size = 0;
	char** newArray = (char**)malloc(maxSize * sizeof(char*));

	//allow reads up to 100 characters
	char scanformat[5];
	sprintf(scanformat, "%%%2ds", stringsize);

	char* newString = (char*)malloc(stringsize * sizeof(char));
	while(getline(&newString, ((size_t*)&stringsize), stdin) > 0)
	{
		//remove the a newline from the end of the string
		newString[strcspn(newString, "\n")] = 0;

		//add the string to the array
		newArray[size++] = newString;

		//reserve some more space for the next string
		newString = (char*)malloc(stringsize * sizeof(char));

		if(size >= maxSize)
		{
			//allocate some more
			maxSize += stepsize;
			newArray = (char**)realloc(newArray, maxSize * stringsize);
		}
	}
	//release the extra buffer we didn't use
	free(newString);

	//set the return values
	*stringArr = newArray;
	*elements = size;

	return maxSize;
}

int freeStrArr(char** stringArr, const int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		free(stringArr[i]);
	}
	free(stringArr);
	return i;
}

char** splitStringArray(char** stringArr, const int size, const char* delimiter)
{
	//allocate an array for the new char pointers
	char** newArr = (char**)malloc(size * sizeof(char*));

	for(int i = 0; i < size; i++)
	{
		//first mark the end of the first token
		strtok(stringArr[i], delimiter);
		newArr[i] = strtok(NULL, delimiter);
	}
	return newArr;
}