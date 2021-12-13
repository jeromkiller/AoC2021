#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common/common.h"

#define MAP_SIZE 1000

int mapVents(char** input, int size)
{
	//create the big map
	int map[MAP_SIZE][MAP_SIZE];
	memset(map, 0, sizeof(map));

	//run over all the input and map the vents
	//only the horizontal and vertical ones
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	for(int i = 0; i < size; i++)
	{
		sscanf(input[i], "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);

		//is this a horizontal line?
		if(y1 == y2)
		{
			//move x from x1, to x2
			for(int x = x1; x != x2; x += (x1 > x2 ? -1 : 1))
			{
				map[x][y1] += 1;
			}
			//don't forget to set the last one
			map[x2][y2] += 1;
		}//else, is this a vertical line?
		else if(x1 == x2)
		{
			//move y from y1, to y2
			for(int y = y1; y != y2; y += (y1 > y2 ? -1 : 1))
			{
				//mark this line
				map[x1][y] += 1;
			}
			//don't forget to set the last one
			map[x2][y2] += 1;
		}
		else // else this is a diagonal line
		{
			int x = x1;
			int y = y1;

			while(x != x2)
			{
				map[x][y] += 1;
				x += (x1 > x2 ? -1 : 1);
				y += (y1 > y2 ? -1 : 1);
			}
			//don't forget to set the last one
			map[x2][y2] += 1;
		}
	}

	//now count all area's of the map with 2 or more overlapping vent
	int ventCount = 0;
	for(int x = 0; x < MAP_SIZE; x++)
	{
		for(int y = 0; y < MAP_SIZE; y++)
		{
			ventCount += map[x][y] >= 2;
		}
	}

	return ventCount;
}

int main(void)
{
	//read the input
	char** input = NULL;
	int size = 0;
	stdinToStrArr(&input, &size, 25);

	//do the challange
	int DangerZones = mapVents(input, size);
	printf("Number of dangerous area's: %d\n", DangerZones);

	//clean up after ourselves
	freeStrArr(input, size);

	return 0;
}