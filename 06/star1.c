#include <stdio.h>
#include <stdlib.h>
#include "common/common.h"

//putting this in advanced, because i feel like the second star is going to have me deal with these things dying
typedef struct fishyInfo_struct
{
	char spawnCycle;
}fishyInfo;

int simulateFishes(listItem* rootFish, int generations)
{
	//simulate the fishes spawning
	listItem* firstFish = rootFish;
	//loop for every generation
	for(int gen = 0; gen < generations; gen++)
	{
		//walk over the fish list, and spawn new fish when needed
		listItem* curFish = firstFish;
		while(curFish)
		{
			fishyInfo* fish = (fishyInfo*)curFish->item;
			if(--(fish->spawnCycle) < 0)
			{
				//reset the spawncycle and spawn a fish
				fish->spawnCycle = 6;

				//spawn a new fish, and add it to the list -> the assignment tells me to add it to the end of the list, but in the middle is faster
				fishyInfo* newFish = (fishyInfo*)malloc(sizeof(newFish));
				newFish->spawnCycle = 8;
				curFish = dRefList_AddItem(&curFish, newFish);
			}
			curFish = curFish->next;
		}
	}

	//now count all the nodes in the list
	listItem* countItem = firstFish;
	int listCount = 0;
	while(countItem)
	{
		listCount++;
		countItem = countItem->next;
	}

	printf("After %d generations we have %d fish\n", generations, listCount);
	return listCount;
}

int main(void)
{
	//parse the incomming data to something we can work with
	char* inputString = (char*)malloc(1000 * sizeof(char));
	scanf("%s", inputString);

	char** stringArr = NULL;
	int elements = splitStringToArray(inputString, ",", &stringArr);

	char* startingVals = NULL;
	strArrToInt8Arr(stringArr, elements, &startingVals);

	//put the initial values into the fishy struct, and put those in a list
	fishyInfo* fish = (fishyInfo*)malloc(sizeof(fishyInfo));
	fish->spawnCycle = startingVals[0];
	listItem* rootFishItem = dRefList_AddItem(NULL, fish);
	listItem* newFishItem = rootFishItem;
	for(int i = 1; i < elements; i++)
	{
		fish = (fishyInfo*)malloc(sizeof(fishyInfo));
		fish->spawnCycle = startingVals[i];
		newFishItem = dRefList_AddItem(&newFishItem, fish);
	}

	//we now have the input parsed, and don't need the original input anymore
	free(stringArr);
	free(startingVals);
	free(inputString);

	//perform the challange
	simulateFishes(rootFishItem, 80);

	return 0;
}