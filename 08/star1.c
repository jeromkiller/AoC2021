#include <stdio.h>
#include <string.h>

#include "common/common.h"

int main(void)
{
	//parse the input
	char** inputStrings = NULL;
	int numInputStrings = 0;
	stdinToStrArr(&inputStrings, &numInputStrings, 100);

	//split the encoded numbers, from the garbled numbers
	char** garbledNums = splitStringArray(inputStrings, numInputStrings, "|");

	//for the first challange, just loop over the garbled output and count the stringsize
	int nums = 0;
	for(int i = 0; i < numInputStrings; i++)
	{
		char** looseNums = NULL;
		int numLooseNums = splitStringToArray(garbledNums[i], " ", &looseNums);

		for(int j = 0; j < numLooseNums - 1; j++)
		{
			switch(strlen(looseNums[j]))
			{
				case 2:
				case 3:
				case 4:
				case 7:
					nums++;
					break;
			}
		}
	}

	printf("number of 1,4,7 and 8: %d\n", nums);

	return 0;
}