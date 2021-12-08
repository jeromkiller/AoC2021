#include <stdio.h>
#include <string.h>

#include "common/common.h"

unsigned char encodeStringToSegments(char* input)
{
	int numBits = strlen(input);
	unsigned char segments = 0;
	for(int bit = 0; bit < numBits; bit++)
	{
		switch(input[bit])
		{
			case 'a':
				segments |= 1;
				break;
			case 'b':
				segments |= 1 << 1;
				break;
			case 'c':
				segments |= 1 << 2;
				break;
			case 'd':
				segments |= 1 << 3;
				break;
			case 'e':
				segments |= 1 << 4;
				break;
			case 'f':
				segments |= 1 << 5;
				break;
			case 'g':
				segments |= 1 << 6;
				break;	
		}
	}
	return segments; 
}

unsigned char countBits(unsigned char value)
{
	unsigned char bits = 0;
	while(value)
	{
		bits += value & 1;
		value = value >> 1;
	}
	return bits;
}

char findMissingBit(unsigned char val1, unsigned char val2)
{
	unsigned char result = (val1 & (~val2)) & 0x7F;
	return countBits(result) == 1;
}

unsigned char findBitPattern(char compareVal, char* list, char bitCount, char* decodedSegs, int lookingFor)
{
	for(int i = 0; i < 10; i++)
	{
		if(countBits(list[i]) == bitCount)
		{
			if(findMissingBit(compareVal, list[i]))
			{
				//check if this number was already found
				char numFound = 0;
				for(int j = 0; j < 10; j++)
				{
					numFound |= decodedSegs[j] == list[i];
				}

				if(!numFound)
				{
					return list[i];
				}
			}
		}
	}
	printf("Hmm... looks like we couldn't find a the patern for this\n");
	return 0;
}

int decodeSegments(char* inputSegments, char* outputSegments)
{
	//save wich combination of segments make which numbers
	char decodedSegs[10];
	memset(decodedSegs, -1, sizeof(decodedSegs));

	//first find the numbers 1, 4, 7 and 8
	for(int i = 0; i < 10; i++)
	{
		switch(countBits(inputSegments[i]))
		{
			case 2:
				decodedSegs[1] = inputSegments[i];
				break;
			case 3:
				decodedSegs[7] = inputSegments[i];
				break;
			case 4:
				decodedSegs[4] = inputSegments[i];
				break;
			case 7:
				decodedSegs[8] = inputSegments[i];
		}
	}

	//with these we can figure out the rest of the characters
	decodedSegs[6] = findBitPattern(decodedSegs[1], inputSegments, 6, decodedSegs);
	decodedSegs[5] = findBitPattern(decodedSegs[6], inputSegments, 5, decodedSegs);
	decodedSegs[0] = findBitPattern(decodedSegs[5], inputSegments, 6, decodedSegs);
	decodedSegs[9] = findBitPattern(decodedSegs[0], inputSegments, 6, decodedSegs);
	decodedSegs[3] = findBitPattern(decodedSegs[9], inputSegments, 5, decodedSegs);
	decodedSegs[2] = findBitPattern(decodedSegs[3], inputSegments, 5, decodedSegs);

	//now we can decode the values
	int retval = 0;
	for(int i = 0; i < 4; i++)
	{
		retval *= 10;
		for(int j = 0; j < 10; j++)
		{
			if(outputSegments[i] == decodedSegs[j])
			{
				retval += j;
			}
		}
	}
	return retval;
}

int main(void)
{
	//parse the input
	char** encodedInputStrings = NULL;
	int numInputStrings = 0;
	stdinToStrArr(&encodedInputStrings, &numInputStrings, 100);

	//split the encoded numbers, from the garbled numbers
	char** encodedOutputStrings = splitStringArray(encodedInputStrings, numInputStrings, "|");

	//split these off as well, into their own string arrays
	char** InputStrings[numInputStrings];
	char** OutputStrings[numInputStrings];

	for(int i = 0; i < numInputStrings; i++)
	{
		splitStringToArray(encodedInputStrings[i], " ", &(InputStrings[i]));
		splitStringToArray(encodedOutputStrings[i], " ", &(OutputStrings[i]));
	}

	//now encode these into binary
	char InputSegments[numInputStrings][10];
	char OutputSegments[numInputStrings][4];
	
	for(int i = 0; i < numInputStrings; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			InputSegments[i][j] = encodeStringToSegments(InputStrings[i][j]);
		}
		for(int j = 0; j < 4; j++)
		{
			OutputSegments[i][j] = encodeStringToSegments(OutputStrings[i][j]);
		}
	}

	int totalSum = 0;

	for(int i = 0; i < numInputStrings; i++)
	{
		totalSum += decodeSegments(InputSegments[i], OutputSegments[i]);
	}

	printf("the decoded segments summed up: %d\n", totalSum);

	return 0;
}