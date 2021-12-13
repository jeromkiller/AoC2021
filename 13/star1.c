#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common/common.h"

typedef struct cord_struct
{
	int x;
	int y;
}cord;

int main(void)
{
	char** inputStrings = NULL;
	int numStrings = 0;
	stdinToStrArr(&inputStrings, &numStrings, 20);

	//count the amount of cordinate pairs
	int numCords;
	for(numCords = 0; inputStrings[numCords] != NULL; numCords++)
	{
	}

	//move the strings to a list of cordinates
	cord cords[numCords];
	int maxX = 0;
	int maxY = 0;
	for(int i = 0; i < numCords; i++)
	{
		int x, y;
		sscanf(inputStrings[i], "%d,%d", &x, &y);
		cords[i].x = x;
		cords[i].y = y;

		if(x > maxX)
		{
			maxX = x;
		}
		if(y > maxY)
		{
			maxY = y;
		}
	}
	maxX++;
	maxY++;

	//fill in the paper
	char paper[maxY][maxX];
	memset(paper, '.', sizeof(paper));

	for(int i = 0; i < numCords; i++)
	{
		int x = cords[i].x;
		int y = cords[i].y;
		paper[y][x] = '#';
	}

	//find out where to fold
	int paperWidth = maxX;
	int paperHeight = maxY;
	char dir;
	int pos;

	sscanf(inputStrings[numCords + 1], "fold along %c=%d", &dir, &pos);

	if(dir == 'x')
	{
		//fold left
		for(int x = paperWidth -1; x != pos; x--)
		{
			int foldLocation = (pos - x) + pos;
			for(int y = 0; y < paperHeight; y++)
			{
				char val = paper[y][x];
				if(val == '#')
				{
					paper[y][foldLocation] = val;
				}
				//printf("moved {%d, %d} to {%d, %d}\n", x, y, foldLocation, y);
			}
		}
		//after folding, we can disregard the right part of the paper
		paperWidth = pos;
	}
	else
	{
		//fold upwards
		for(int y = paperHeight -1; y != pos; y--)
		{
			int foldLocation = (pos - y) + pos;
			for(int x = 0; x < paperWidth; x++)
			{
				char val = paper[y][x];
				if(val == '#')
				{
					paper[foldLocation][x] = val;
				}
			}
		}
		//after folding, we can disregard the bottom part of the paper
		paperHeight = pos;
	}

	//count the amount of dots
	int dotcount = 0;
	for(int y = 0; y < paperHeight; y++)
	{
		for(int x = 0; x < paperWidth; x++)
		{
			dotcount += paper[y][x] == '#';
		}
	}	
	
	printf("number of dots: %d\n", dotcount);

	return 0;
}