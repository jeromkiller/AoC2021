#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common/common.h"

int getCharVal(char character)
{
	switch (character)
	{
		case ')':
			return 1;
		case ']':
			return 2;
		case '}':
			return 3;
		case '>':
			return 4;
		default:
			printf("Unknown char\n");
			return 0;
	}
}

//courtesy of Ophir Carmi on Stack exchange (https://stackoverflow.com/questions/17638499/using-qsort-to-sort-an-array-of-long-long-int-not-working-for-large-nos/26428052)
int cmpfunc (const void * a, const void * b)
{
    if( *(long long int*)a - *(long long int*)b < 0 )
        return -1;
    if( *(long long int*)a - *(long long int*)b > 0 )
        return 1;
    return 0;
}

long parseBrackets(char** strings, int numStrings)
{
	//create a char
	genStack* stack = charStackCreate();
	genStack* scoreStack = longStackCreate();	//I don't want to create a growing buffer, so i'm going to missuse my brand new stack

	for(int line = 0; line < numStrings; line++)
	{
		char corruptionFound = 0;
		genStackClear(&stack);
		int numChars = strlen(strings[line]);
		for(int character = 0; character < numChars; character++)
		{
			switch(strings[line][character])
			{
				//open brackets, push the closing version to the stack
				case '(':
					charStackPush(&stack, ')');
					break;
				case '[':
					charStackPush(&stack, ']');
					break;
				case '{':
					charStackPush(&stack, '}');
					break;
				case '<':
					charStackPush(&stack, '>');
					break;
				//close brackets, check if we have the closing version on the stack
				case ')':
				{
					const char outChar = charStackPop(&stack);
					if(outChar != ')')
					{
						corruptionFound = 1;
					}
					break;
				}
				case ']':
				{
					const char outChar = charStackPop(&stack);
					if(outChar != ']')
					{
						corruptionFound = 1;
					}
					break;
				}
				case '}':
				{
					const char outChar = charStackPop(&stack);
					if(outChar != '}')
					{
						corruptionFound = 1;
					}
					break;
				}
				case '>':
				{
					const char outChar = charStackPop(&stack);
					if(outChar != '>')
					{
						corruptionFound = 1;
					}
					break;
				}
			}
			if(corruptionFound)
			{
				break;
			}
		}
		if(!corruptionFound)
		{
			//if the line is incomplete
			//calculate the autocomplete score
			long lineScore = 0;
			while(stack->stackPointer > 0)
			{
				lineScore *= 5;
				lineScore += getCharVal(charStackPop(&stack));
			}
			//add the score to the stack
			longStackPush(&scoreStack, lineScore);
		}
	}

	//sort the items on the stack, like i said, i'm abusing the stack i created
	const int numItems = genStackCount(scoreStack);
	qsort(scoreStack->stackStart, numItems, scoreStack->itemSize, cmpfunc);

	//check out the middle item of the stack
	int middleIndex = numItems / 2;
	return *(long*)(scoreStack->stackStart + (middleIndex * scoreStack->itemSize));
}

int main(void)
{
	//get the input, not much parsing needed this time
	char** inputStrings = NULL;
	int numStrings = 0;
	stdinToStrArr(&inputStrings, &numStrings, 120);

	//solve the puzzle
	long errorScore = parseBrackets(inputStrings, numStrings);
	printf("AutoComplete score: %ld\n", errorScore);

	return 0;
}