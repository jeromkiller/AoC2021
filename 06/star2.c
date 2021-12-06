#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/common.h"

//putting this in advanced, because i feel like the second star is going to have me deal with these things dying
typedef struct fishyInfo_struct
{
	unsigned long breedingFish[7];
	unsigned long babyFish[3];
}fishyInfo;

int simulateFishes(fishyInfo* fishes, int generations)
{
	//simulate the fishes spawning
	//loop for every generation
	for(int gen = 0; gen < generations; gen++)
	{
		//the fish are summed up in breed cycles
		//every generation a differnet group gets to spawn a bunch of new fish
		//these new fish do not get to participate, until they grow up
		//the group newly grown up fishes fall into lags one group behind breedgroup
		int breedCycle = gen % 7;
		int growupCycle = (gen -1) % 7;
		fishes->breedingFish[growupCycle] += fishes->babyFish[0];
		fishes->babyFish[0] = fishes->babyFish[1];
		fishes->babyFish[1] = fishes->babyFish[2];
		fishes->babyFish[2] = fishes->breedingFish[breedCycle];
	}

	//loop over the breed groups and count how many fish are in there
	unsigned long fishCount = 0;
	for(int i = 0; i < (int)(sizeof(fishyInfo) / sizeof(unsigned long)); i++)
	{
		fishCount += ((unsigned long*)fishes)[i];
	}

	printf("After %d generations we have %ld fish\n", generations, fishCount);
	return fishCount;
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
	fishyInfo* fishes = (fishyInfo*)malloc(sizeof(fishyInfo));
	memset(fishes, 0, sizeof(fishyInfo));
	for(int i = 0; i < elements; i++)
	{
		fishes->breedingFish[(int)startingVals[i]]++;
	}

	//we now have the input parsed, and don't need the original input anymore
	free(stringArr);
	free(startingVals);
	free(inputString);

	//perform the challange
	simulateFishes(fishes, 256);

	return 0;
}