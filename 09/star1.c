#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "common/common.h"

#define heightMapBorder 2

//unsigned char val = heightMap[j + (i * width)];

//the heightmap is bordered in memory, the pointer points to the start of the original heightmap
int countLowPoints(unsigned char* heightmap, int height, int width)
{
	int riskLevel = 0;

	for(int i = 1; i < height - 1; i++)
	{
		for(int j = 1; j < width - 1; j++)
		{
			//check the points around this point
			const unsigned char val = heightmap[(j) + (i * width)];
			char isLowest = 1;
			
			isLowest &= (val < (heightmap[(j - 1) + ((i + 0) * width)]));
			isLowest &= (val < (heightmap[(j + 1) + ((i + 0) * width)]));
			isLowest &= (val < (heightmap[(j + 0) + ((i - 1) * width)]));
			isLowest &= (val < (heightmap[(j + 0) + ((i + 1) * width)]));

			//sum it up if it was higher
			if(isLowest)
			{
				riskLevel += (val + 1);
			}
		}
	}

	return riskLevel;
}

int main(void)
{
	//read all the input into a string array
	char** inputStrings = NULL;
	int numStrings = 0;
	stdinToStrArr(&inputStrings, &numStrings, 105);

	int StringLength = strlen(*inputStrings);

	//reserve space for the heightmap and an edge around it
	//the border will be 255 so i don't have to deal with the literal edge and corner cases :P
	int width = StringLength + 2;
	int height = numStrings + 2;
	int mallocSize = (width) * (height) * sizeof(unsigned char);
	unsigned char* heightMap = (unsigned char*)malloc(mallocSize);
	memset(heightMap, UCHAR_MAX, mallocSize);

	//fill the heightmap
	for(int i = 0; i < numStrings; i++)
	{
		for(int j = 0; j < StringLength; j++)
		{
			unsigned char val = 0;
			sscanf(&(inputStrings[i][j]), "%1hhd", &val);
			heightMap[(j + 1) + (width * (i + 1))] = val;
		}
	}

	int riskLevel = countLowPoints(heightMap, height, width);

	printf("RiskLevel in this cave: %d\n", riskLevel);

	return 0;
}