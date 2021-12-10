#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "common/common.h"

void printHeightmap(unsigned char* heightmap, int mapWidth, int mapHeight)
{
	for(int i = 0; i < mapHeight; i++)
	{
		for(int j = 0; j < mapWidth; j++)
		{
			unsigned char val = heightmap[j + (i * mapWidth)];
			if(val > 30)
			{
				//blue for the border
				printf("\033[0;34m%3d ", val);
			}
			else if(val > 9)
			{
				//green for the filled basins
				printf("\033[0;32m%3d ", val - 10);
			}
			else
			{
				//normal color for the rest
				printf("\033[0m%3d ", val);
			}
		}
		printf("\n\033[0m");
	}
}

//find bassin size
//for this i'm going to use a depth first search bucket fill
//also known as my second recursive function
int bucketFill(unsigned char* heightmap, int x, int y, int mapWidth)
{
	//'color in' this point
	heightmap[x + (y * mapWidth)] += 10;
	int basinSize = 1;

	//check if we can move to our neighbours if they are part of the basin
	//the we stop at the edge '9', and a tile is marked if its > 9
	//by checking this we won't go over the same neighbour twice and stop at the edge
	if(heightmap[x + ((y - 1) * mapWidth)] < 9)	//check top neighbour
	{
		basinSize += bucketFill(heightmap, x, y - 1, mapWidth);
	}
	if(heightmap[(x + 1) + (y * mapWidth)] < 9)	//check right neighbour
	{
		basinSize += bucketFill(heightmap, x + 1, y, mapWidth);
	}
	if(heightmap[x + ((y + 1) * mapWidth)] < 9)	//check down neighbour
	{
		basinSize += bucketFill(heightmap, x, y + 1, mapWidth);
	}if(heightmap[(x - 1) + (y * mapWidth)] < 9)	//check left neighbour
	{
		basinSize += bucketFill(heightmap, x - 1, y, mapWidth);
	}

	//return the amount of tiles filled
	return basinSize;
}

//the heightmap is bordered in memory, the pointer points to the start of the original heightmap
int countLowPoints(unsigned char* heightmap, int height, int width)
{
	int basins[3] = {0, 0, 0};
	for(int i = 1; i < height - 1; i++)
	{
		for(int j = 1; j < width - 1; j++)
		{
			//check the points around this point
			const unsigned char val = heightmap[(j) + (i * width)];
			
			if(val < 9)
			{
				char isLowest = 1;
				isLowest &= (val < (heightmap[(j - 1) + ((i + 0) * width)]));
				isLowest &= (val < (heightmap[(j + 1) + ((i + 0) * width)]));
				isLowest &= (val < (heightmap[(j + 0) + ((i - 1) * width)]));
				isLowest &= (val < (heightmap[(j + 0) + ((i + 1) * width)]));

				//if this was a low point, check how large the basin
				if(isLowest)
				{
					int basinSize = bucketFill(heightmap, j, i, width);
					//put it in the list of highest basins if it fits in there
					int lowIndex = 0;
					for(int k = 0; k < 3; k++)
					{
						if(basins[lowIndex] > basins[k])
						{
							lowIndex = k;
						}
					}
					if(basins[lowIndex] < basinSize)
					{
						basins[lowIndex] = basinSize;
					}
				}
			}		
		}
	}
	int largestBasins = 1;
	for(int i = 0; i < 3; i++)
	{
		printf("largest: %d\n", basins[i]);
		largestBasins *= basins[i];
	}
	return largestBasins;
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