#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/common.h"

int calculatePossition(char** commands, char** values, int size)
{
	int depth = 0;
	int forward = 0;

	for(int i = 0; i < size; i++)
	{
		//we can check the direction by checking the first character in the command
		char dir = commands[i][0];
		int val = values[i][0] - '0'; //quick and dirty convertion from char to int (works as long as the value is below 10)
		switch(dir)
		{
			case 'f':
				forward += val;
				break;
			case 'd':
				depth += val;
				break;
			case 'u':
				depth -= val;
				break;
			default:
				printf("Error, unknown direction");
				break;

		}
	}
	printf("depth: %d\nforward: %d\n", depth, forward);

	return depth * forward;
	
}

int main(void)
{
	//write all incomming values to an array
	char** commands = NULL;
	int size = 0;
	stdinToStrArr(&commands, &size, 20);

	//split the numbers from the commands
	const char* delim = " ";
	char** nums = splitStringArray(commands, size, delim);

	//perform the challange
	int pos = calculatePossition(commands, nums, size);

    printf("possition: %d\n", pos);

	//cleanup afterwards
	freeStrArr(commands, size);
	free(nums);

	return 0;
}