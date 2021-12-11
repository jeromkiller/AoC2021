#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "common/common.h"

//use this function to 
void printSquidmap(unsigned char* squidmap, int mapWidth, int mapHeight)
{
	for(int i = 0; i < mapHeight; i++)
	{
		for(int j = 0; j < mapWidth; j++)
		{
			unsigned char val = squidmap[j + (i * mapWidth)];
			if(val > 50)
			{
				//blue for the border
				printf("\033[0;34m%3d ", val);
			}
			else if(val == 0 || val > 9)
			{	
				//green for the popped squids
				printf("\033[0;32m%3d ", val);
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

void popSquid(unsigned char* squidmap, int x, int y, int mapWidth)
{
	//increment the surounding squids, if they haven't popped already
	for(int i = 0; i < 9; i++)
	{
		const int xOffset = (i % 3) - 1;
		const int yOffset = (i / 3) - 1;
		
		//go over all neighbours (not ourselves)
		if(!((xOffset == 0) && (yOffset == 0)))
		{
			const unsigned char val = squidmap[(x + xOffset) + ((y + yOffset) * mapWidth)];
			if(val < 10)
			{
				if(++squidmap[(x + xOffset) + ((y + yOffset) * mapWidth)] > 9)
				{
					popSquid(squidmap, x + xOffset, y + yOffset, mapWidth);
				}
			}
			
		}
	}
}

//loop over all the squids and increase their count
void simulateSquids(unsigned char* squidmap, int mapWidth, int mapHeight)
{
	for(int y = 1; y < mapHeight - 1; y++)
	{
		for(int x = 1; x < mapWidth - 1; x++)
		{
			const unsigned char val = squidmap[(x) + (y * mapWidth)];

			if(val < 10)
			{
				//increment the squid and see if it pops
				if(++squidmap[(x) + (y * mapWidth)] > 9)
				{
					popSquid(squidmap, x, y, mapWidth);
				}
			}
		}
	}
}

int resetPoppedSquids(unsigned char* squidmap, int mapWidth, int mapHeight)
{
	int squidPops = 0;
	for(int y = 1; y < mapHeight - 1; y++)
	{
		for(int x = 1; x < mapWidth - 1; x++)
		{
			const unsigned char val = squidmap[(x) + (y * mapWidth)];

			if(val > 9)
			{
				squidmap[(x) + (y * mapWidth)] = 0;
				squidPops++;
			}
		}
	}
	return squidPops;
}

int main(void)
{
	//copied the input parsing from day 9

	//read all the input into a string array
	char** inputStrings = NULL;
	int numStrings = 0;
	stdinToStrArr(&inputStrings, &numStrings, 105);

	int StringLength = strlen(*inputStrings);

	//reserve space for the squidMap and an edge around it
	//the border will be 255 so i don't have to deal with the literal edge and corner cases :P
	int width = StringLength + 2;
	int height = numStrings + 2;
	int mallocSize = (width) * (height) * sizeof(unsigned char);
	unsigned char* squidMap = (unsigned char*)malloc(mallocSize);
	memset(squidMap, UCHAR_MAX, mallocSize);

	//fill the squidMap
	for(int i = 0; i < numStrings; i++)
	{
		for(int j = 0; j < StringLength; j++)
		{
			unsigned char val = 0;
			sscanf(&(inputStrings[i][j]), "%1hhd", &val);
			squidMap[(j + 1) + (width * (i + 1))] = val;
		}
	}

	int squidPops = 0;
	for(int loops = 0; loops < 100; loops++)
	{
		simulateSquids(squidMap, width, height);
		squidPops += resetPoppedSquids(squidMap, width, height);
	}

	printf("number of squid glowups: %d\n", squidPops);

	return 0;
}