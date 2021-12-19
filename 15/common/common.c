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

int stdinToStrArr(char*** stringArr, int* elements, int maxBuffer)
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
	size_t maxBufferSize = maxBuffer;

	//allow reads up to 999 characters
	//char scanformat[8];
	//sprintf(scanformat, "%%%3ds", maxBuffer);

	char* newString = (char*)malloc(maxBufferSize * sizeof(char));
	while(getline(&newString, &maxBufferSize, stdin) > 0)
	{
		//remove the a newline from the end of the string
		newString[strcspn(newString, "\n")] = 0;

		//shrink the stringbuffer to its actual length to save space
		const int strlenth = strlen(newString);
		newString = (char*)realloc(newString, strlenth + 1);

		//add the string to the array
		newArray[size++] = newString;

		//reserve some more space for the next string
		newString = (char*)malloc(maxBufferSize * sizeof(char));

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

int stdinToSingleString(char** stringRef, int maxBuffer)
{
	//get the string from stdIn
	char* newString = (char*)malloc(maxBuffer * sizeof(char));
	getline(&newString, ((size_t*)&maxBuffer), stdin);

	//chop off the newLine, and free some of the unused buffer
	newString[strcspn(newString, "\n")] = 0;
	const int strLength = strlen(newString);
	newString = (char*)realloc(newString, strLength);

	//set out parameters and return the string length
	*stringRef = newString;
	return strLength;
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
		listItem* nextItem = NULL;

		if(*insertionPoint)
		{
			//point the next of the new item to the next of the insertion point
			nextItem = (*insertionPoint)->next;
			newItem->next = nextItem;

			//point our new item to the insertion point of the old one
			(*insertionPoint)->next = newItem;
		}

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

listItem* dRefList_AddItemFront(listItem** insertionPoint, void* newRef)
{
	//create a new list node
	listItem* newItem = (listItem*)malloc(sizeof(listItem));

	//add the new refference
	newItem->item = newRef;

	//if the insertion is given
	if(insertionPoint)
	{
		//then we can set it as the next node
		newItem->next = *insertionPoint;
		listItem* prevItem = NULL;

		if(*insertionPoint)
		{
			//point the next of the new item to the next of the insertion point
			prevItem = (*insertionPoint)->prev;
			newItem->prev = prevItem;

			//point our new item to the insertion point of the old one
			(*insertionPoint)->prev = newItem;
		}

		//if nextItem is not NULL
		if(prevItem)
		{
			//we can point that back to this item
			prevItem->next = newItem;
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
		if(nextItem)
		{
			nextItem->prev = NULL;
			return nextItem;
		}
	}
	return NULL;
}

//Stack stuff
#define STACK_GROW_VALUE 25
#define MAX_ITEM_SIZE 50

genStack* genStackCreate(size_t itemSize)
{
	//limit itemsize to 50
	assert(itemSize < MAX_ITEM_SIZE);

	genStack* newStack = (genStack*)malloc(sizeof(genStack));
	newStack->itemSize = itemSize;
	newStack->stackSize = STACK_GROW_VALUE * itemSize;
	newStack->stackStart = malloc(newStack->stackSize);

	return newStack;
}

void genStackPush(genStack** stackRef, void* item)
{
	genStack* stack = *stackRef;
	//if there is no room for the item on the stack, grow the stack
	if((stack->stackPointer + stack->itemSize) < stack->stackSize)
	{
		stack->stackSize += STACK_GROW_VALUE * stack->itemSize;
		stack->stackStart = realloc(stack->stackStart, stack->stackSize);
	}

	//advance the stackpointer and push the item to the stack
	memcpy(stack->stackStart + stack->stackPointer, item, stack->itemSize);
	stack->stackPointer += stack->itemSize;
}

void* genStackPop(genStack** stackRef)
{
	//buffer to point to when returning items :P
	static char returnBuffer[MAX_ITEM_SIZE];
	genStack* stack = *stackRef;

	//check if we are able to pop items
	if((size_t)stack->stackPointer < stack->itemSize)
	{
		printf("ERROR: stack to small to pop from\n");
		return NULL;	
	}

	//lower the stackpointer and pop the item off the stack
	stack->stackPointer -= stack->itemSize;
	memcpy(returnBuffer, stack->stackStart + stack->stackPointer, stack->itemSize);

	//check if we can shrink the stack
	if(stack->stackSize - (size_t)stack->stackPointer <= (2 * STACK_GROW_VALUE * stack->itemSize))
	{
		stack->stackSize -= STACK_GROW_VALUE * stack->itemSize;
		stack->stackStart = realloc(stack->stackStart, stack->stackSize);
	}

	return returnBuffer;
}

void* genStackPeek(genStack* stackRef)
{
	static char returnBuffer[MAX_ITEM_SIZE];
	genStack* stack = stackRef;

	//check if we are able to pop items
	if((size_t)stack->stackPointer < stack->itemSize)
	{
		printf("ERROR: stack to small to peek from\n");
		return NULL;	
	}

	//lower the stackpointer and pop the item off the stack
	memcpy(returnBuffer, stack->stackStart + stack->stackPointer - stack->itemSize, stack->itemSize);

	return returnBuffer;
}

void genStackFree(genStack* stack)
{
	free(stack->stackStart);
	free(stack);
}

void genStackClear(genStack** stackRef)
{
	genStack* stack = *stackRef;
	stack->stackPointer = 0;
	stack->stackSize = STACK_GROW_VALUE * stack->itemSize;
	stack->stackStart = realloc(stack->stackStart, stack->itemSize);
}

int genStackCount(genStack* stack)
{
	return stack->stackPointer / stack->itemSize;
}

//functions to control the generic stack as a char stack
genStack* charStackCreate(void)
{
	return genStackCreate(sizeof(char));
}

void charStackPush(genStack** stackRef, char value)
{
	genStackPush(stackRef, &value);
}

char charStackPop(genStack** stackRef)
{
	return *(char*)genStackPop(stackRef);
}

char charStackPeek(genStack* stack)
{
	return *(char*)genStackPeek(stack);
}

//functions to controll the generic stack as a int stack
genStack* longStackCreate(void)
{
	return genStackCreate(sizeof(long));
}

void longStackPush(genStack** stackRef, long value)
{
	genStackPush(stackRef, &value);
}

long longStackPop(genStack** stackRef)
{
	return *(long*)genStackPop(stackRef);
}

long longStackPeek(genStack* stack)
{
	return *(long*)genStackPeek(stack);
}

//Create a Priority queue
pQueue* pQueueCreate()
{
	//create the queue
	pQueue* newQueue = (pQueue*)malloc(sizeof(pQueue));
	memset(newQueue, 0, sizeof(pQueue));
	return newQueue;
}

//add an item to the priority queue
void pQueueAddItem(pQueue* priorityQueue, void* item, int(comparFunc)(void* item1, void* item2))
{
	assert(item);
	assert(priorityQueue);

	if(priorityQueue->queueStart)
	{
		listItem* insertPoint = priorityQueue->queueStart;
		while(insertPoint)
		{
			if(comparFunc(insertPoint->item, item) > 0)
			{
				break;
			}
			insertPoint = insertPoint->next;
		}
		listItem* newItem = dRefList_AddItemFront(&insertPoint, item);

		if(NULL == newItem->prev)
		{
			//this is the new first
			priorityQueue->queueStart = newItem;
		}		
	}
	else
	{
		priorityQueue->queueStart = dRefList_AddItem(NULL, item);
	}
	priorityQueue->numItems++;
}

//peek the first item on the queue
void* pQueuePeek(pQueue* priorityQueue)
{
	//return the first item from the buffer
	return priorityQueue->queueStart->item;
}

//pop the first item from the queue
void* pQueuePop(pQueue* priorityQueue)
{
	//copy the item from the buffer
	void* returnPtr = pQueuePeek(priorityQueue);
	//then remove the item from the queue
	priorityQueue->queueStart = dRefList_RemoveItem(priorityQueue->queueStart);
	priorityQueue->numItems--;
	return returnPtr;
}