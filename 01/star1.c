
#include <stdio.h>
#include <stdlib.h>

//this function loops over a input array of given size and counts how many times the value increases compared to the last time
int SensorReport(int* values, int size)
{
    int prevValue = values[0];
    int numIncreases = 0;

    for(int i = 1; i < size; i++)
    {
        const int curValue = values[i];

		if(curValue > prevValue)
			numIncreases++;
		
		prevValue = curValue;
    }
    return numIncreases;
}

int main()
{
	//write all incomming values to an array, increase size as neccicary
	int maxSize = 100;
	int size = 0;
	int* sensorValues = (int*)malloc(maxSize * sizeof(int)); 
    while(scanf("%d", sensorValues + size++) > 0)
	{
		//buffer full
		if(size >= maxSize)
		{
			//allocate some more
			maxSize += 100;
			sensorValues = (int*)realloc(sensorValues, maxSize * sizeof(int));
		}
	}

	//perform the challange
    const int sensorReport = SensorReport(sensorValues, size);

    printf("increases: %d\n", sensorReport);

    return 0;
}