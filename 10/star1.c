#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common/common.h"

int getCharVal(char character)
{
	switch (character)
	{
		case ')':
			return 3;
		case ']':
			return 57;
		case '}':
			return 1197;
		case '>':
			return 25137;
		default:
			printf("Unknown char\n");
			return 0;
	}
}

int parseBrackets(char** strings, int numStrings)
{
	//create a char
	genStack* stack = charStackCreate();
	int coruptionScore = 0;

	for(int line = 0; line < numStrings; line++)
	{
		genStackClear(&stack);
		int numChars = strlen(strings[line]);
		for(int character = 0; character < numChars; character++)
		{
			char corruptionFound = 0;
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
						coruptionScore += getCharVal(')');
						corruptionFound = 1;
					}
					break;
				}
				case ']':
				{
					const char outChar = charStackPop(&stack);
					if(outChar != ']')
					{
						coruptionScore += getCharVal(']');
						corruptionFound = 1;
					}
					break;
				}
				case '}':
				{
					const char outChar = charStackPop(&stack);
					if(outChar != '}')
					{
						coruptionScore += getCharVal('}');
						corruptionFound = 1;
					}
					break;
				}
				case '>':
				{
					const char outChar = charStackPop(&stack);
					if(outChar != '>')
					{
						coruptionScore += getCharVal('>');
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
	}
	return coruptionScore;
}

int main(void)
{
	//get the input, not much parsing needed this time
	char** inputStrings = NULL;
	int numStrings = 0;
	stdinToStrArr(&inputStrings, &numStrings, 120);

	//solve the puzzle
	int errorScore = parseBrackets(inputStrings, numStrings);
	printf("Syntax error score: %d\n", errorScore);

	return 0;
}