#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "common/common.h"

int calcfuelConsumption(int* crabPossitions, int numCrabs, int possition)
{
	int fuelConsumption = 0;
	for(int i = 0; i < numCrabs; i++)
	{
		fuelConsumption += abs(crabPossitions[i] - possition); 
	}
	return fuelConsumption;
}

//ohhh look at that, babies first recursive function
int findLowestFuelConsumption(int* crabPossitions, int numCrabs, int rangeLow, int rangeHigh, int compare, char* ret)
{
	//ret gets set to -1 if the found value is the compare value
	*ret = 0;

	//calculate the fuel consumption to move the crabs towards the middle of the bounds
	int middlePos = ((rangeHigh - rangeLow) / 2) + rangeLow;
	int middleFuelConsumption = calcfuelConsumption(crabPossitions, numCrabs, middlePos);

	//if the range is done
	if(rangeLow == rangeHigh)
	{
		return middleFuelConsumption;
	}

	//is this fuel consumption higher than in the parent function
	if(middleFuelConsumption > compare)
	{
		//then we aren't on the right side
		*ret = -1;
		return middleFuelConsumption;
	}

	//create two variables to save the return values of the two checks
	int lowEnd = INT_MAX;
	int highEnd = INT_MAX;
	
	//check the value on the lower side of this middle is lower then the power consumption for this point
	lowEnd = findLowestFuelConsumption(crabPossitions, numCrabs, rangeLow, middlePos, middleFuelConsumption, ret);
	//if if the returned value was higher then their compare value check the same for the higher part
	if(*ret == -1)
	{
		highEnd = findLowestFuelConsumption(crabPossitions, numCrabs, middlePos, rangeHigh, middleFuelConsumption, ret);
	}

	//if this is also higher, that means we skipped over the lowest point
	if(*ret == -1)
	{
		//continue the search on the side with the lowest result
		//by calling it a second time, with its own return val to compare to
		//will make the function nest a step deeper
		if(highEnd > lowEnd)
		{
			lowEnd = findLowestFuelConsumption(crabPossitions, numCrabs, rangeLow, middlePos, lowEnd, ret);
		}
		else
		{
			highEnd = findLowestFuelConsumption(crabPossitions, numCrabs, middlePos, rangeHigh, highEnd, ret);
		}
	}

	//return the lowest value
	return highEnd > lowEnd ? lowEnd : highEnd;
}

//added an brute force search to check against in case the binary search ran into a local minimum
int exhaustiveSearch(int* crabPossitions, int numCrabs, int maxPos)
{
	int lowest = INT_MAX;
	for(int i = 0; i < maxPos; i++)
	{
		int val = calcfuelConsumption(crabPossitions, numCrabs, i);
		if(val < lowest)
		{
			lowest = val;
		}
	}
	return lowest;
}

int main(void)
{
	//parse the input
	char* inputString = NULL;
	stdinToSingleString(&inputString, 4000);

	char** looseNumbers = NULL;
	int numCrabs = splitStringToArray(inputString, ",", &looseNumbers);

	int* crabPossitions = NULL;
	numCrabs = strArrToIntArr(looseNumbers, numCrabs, &crabPossitions);

	//perform the challange
	char ret = 0;
	int lowestFuelConsumption = 0;
	lowestFuelConsumption = findLowestFuelConsumption(crabPossitions, numCrabs, 0, 2000, INT_MAX, &ret);
	printf("lowest fuel consumption: %d\n", lowestFuelConsumption);

	//lowestFuelConsumption = exhaustiveSearch(crabPossitions, numCrabs, 2000);
	//printf("lowest fuel found through brute force: %d\n", lowestFuelConsumption);

	return 0;
}