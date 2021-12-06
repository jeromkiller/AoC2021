//some generic functions that will probably be usefull in more projects
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
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

int strArrToIntArr(char** stringArr, int size, int** intArr)
{
	int* newIntArr = (int*)malloc(size * sizeof(int));
	for(int i = 0; i < size; i++)
	{
		newIntArr[i] = atoi(stringArr[i]);
	}

	*intArr = newIntArr;
	return size;
}

int strArrToInt8Arr(char** stringArr, int size, char** intArr)
{
	char* newIntArr = (char*)malloc(size * sizeof(char));
	for(int i = 0; i < size; i++)
	{
		newIntArr[i] = (char)atoi(stringArr[i]);
	}

	*intArr = newIntArr;
	return size;
}

int stdinToStrArr(char*** stringArr, int* elements, const int maxBuffer)
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

	//allow reads up to 999 characters
	char scanformat[7];
	sprintf(scanformat, "%%%3ds", maxBuffer);

	char* newString = (char*)malloc(maxBuffer * sizeof(char));
	while(getline(&newString, ((size_t*)&maxBuffer), stdin) > 0)
	{
		//remove the a newline from the end of the string
		newString[strcspn(newString, "\n")] = 0;

		//shrink the stringbuffer to its actual length to save space
		const int strlenth = strlen(newString);
		newString = (char*)realloc(newString, strlenth);

		//add the string to the array
		newArray[size++] = newString;

		//reserve some more space for the next string
		newString = (char*)malloc(maxBuffer * sizeof(char));

		if(size >= maxSize)
		{
			//allocate some more
			maxSize += stepsize;
			newArray = (char**)realloc(newArray, maxSize * sizeof(char*));
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

int splitStringToArray(char* string, const char * delimiter, char*** bufferPointer)
{
	//count the amount of delimiting characters to see how much tokens we have
	
	int tokCount = 1; //assume there is at least a first item
	for(int i = 0; string[i]; i++)
	{
		tokCount += string[i] == *delimiter;
	}

	//reserve some memory for refferences to the tokens
	char** newStringArray = (char**)malloc(tokCount * sizeof(char*));

	//then tokenize the strings
	newStringArray[0] = strtok(string, delimiter);
	for(int i = 1; i < tokCount; i++)
	{
		newStringArray[i] = strtok(NULL, delimiter);
	}

	*bufferPointer = newStringArray;

	return tokCount;
}

listItem* createRefListToArr(void* Arr, const int size)
{
	//check if we have data to put into a list
	assert(Arr);

	//loop over the original array, and create an List item for each ref
	listItem* rootItem = dRefList_AddItem(NULL, Arr);

	listItem* newItem = rootItem;
	for(int i = 1; i < size; i++)
	{
		newItem = dRefList_AddItem(&newItem, Arr + (i * sizeof(void*)));
	}

	return rootItem;
}

listItem* dRefList_AddItem(listItem** insertionPoint, void* newRef)
{
	//create a new list node
	listItem* newItem = (listItem*)malloc(sizeof(listItem));

	//add the new refference
	newItem->item = newRef;

	//if the insertion is given
	if(insertionPoint)
	{
		//then we can set it as the previous node
		newItem->prev = *insertionPoint;

		//point the next of the new item to the next of the insertion point
		//if the next is NULL this is also fine
		listItem* nextItem = (*insertionPoint)->next;
		newItem->next = nextItem;

		//point our new item to the insertion point of the old one
		(*insertionPoint)->next = newItem;

		//if nextItem is not NULL
		if(nextItem)
		{
			//we can point that back to this item
			nextItem->prev = newItem;
		}
	}
	else
	{
		//then we are the first node
		newItem->prev = NULL;
		newItem->next = NULL;
	}

	return newItem;	
}

listItem* dRefList_RemoveItem(listItem* item)
{
	assert(item);

	//get the neighbours of this item
	listItem* prevItem = item->prev;
	listItem* nextItem = item->next;

	//if the privious item isn't NULL
	if(prevItem)
	{
		//link it to the next item
		//this is fine if the next item is NULL
		prevItem->next = nextItem;
	}
	//if the next item isn't NULL
	if(nextItem)
	{
		//link it to the previous item
		//this is fine if the previous item is NULL
		nextItem->prev = prevItem;
	}
	//now the links are severed, we can delete the link item
	free(item);

	if(prevItem)
	{
		return prevItem;
	}
	else
	{
		return nextItem;
	}
}