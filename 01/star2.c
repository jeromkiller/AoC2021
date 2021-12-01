#include <stdio.h>
#include <stdlib.h>
#include "common/common.h"

//the filtersize can be changed to change the size of the filter above
//1 = solution to puzzle 1
//3 = solution to puzzle 2
#define filtersize (3)

//The solution has been improved compared to the first solution,
//the previous commit featured a buffer in wich the values were saved
//but in changing back from reading from an array, we can compare to the outgoing value directly
int SensorReport(int* values, int size)
{
    int numIncreases = 0;

    for(int i = filtersize; i < size; i++)
    {
        const int curValue = values[i];
        const int outValue = values[i - filtersize];

        if(curValue > outValue)
            numIncreases++;
    }
    return numIncreases;
}

int main()
{
    int* sensorValues = NULL;
	int size = 0;
	stdinToIntArr(&sensorValues, &size);

    const int increasecount = SensorReport(sensorValues, size);

    printf("increases: %d\n", increasecount);

    free(sensorValues);
    return 0;
}