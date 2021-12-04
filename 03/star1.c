#include <stdio.h>
#include <string.h>
#include "common/common.h"

int calcPowerConsumption(char** input, int size)
{
	const int numBits = strlen(input[0]);
	int bitCounts[numBits];
	memset(bitCounts, 0, sizeof(int) * numBits);

	//go over every line
	for(int line = 0; line < size; line++)
	{	
		//and check every bit
		for(int bit = 0; bit < numBits; bit++)
		{	
			//add to the counter for this bit if it is set
			bitCounts[bit] += (input[line][bit] == '1');
		}
	}

	//calculate gamma
	int gamma = 0;
	for(int bit = 0; bit < numBits; bit++)
	{
		//set the bit if more than half of the bits are set to 1
		gamma = (gamma << 1) | (bitCounts[bit] > size / 2);
	}

	//calculate epsilon
	//epsilon is gamma inverted,
	//apply a mask to, because the input may not be 32 bit (int)
	const int mask = (1 << numBits) - 1;
	const int epsilon = (~gamma) & mask;

	return gamma * epsilon;
}


int main(void)
{
	char** input = NULL;
	int size = 0;
	stdinToStrArr(&input, &size, 20);

	//do the challange
	int powerConsumption = calcPowerConsumption(input, size);

	//print the result
	printf("Power consumption: %d\n", powerConsumption);

	freeStrArr(input, size);

	return 0;
}