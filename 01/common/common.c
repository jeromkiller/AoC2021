//some generic functions that will probably be usefull in more projects
#include <stdlib.h>
#include <stdio.h>
#include "common.h"


int stdinToIntArr(int** intArr, int* elements)
{
	if(*intArr)
	{
		printf("stdinToIntArr(): intArr might already be created");
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