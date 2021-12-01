#include <stdio.h>
#include <stdlib.h>

#define filtersize (sizeof(filter) / sizeof(int))

//get a new point of sensor data, returns 1 if the filtered data is more than the last
//new data is added to a list, the size of the filter.
//every time a new value gets added a value gets pushed out
//the sum of values gets lowered by the ammount that gets pushed out
//and increases by the new value,
//this means we can also calculate the difference between the new value, and the old value
//if the new value is higher then the old value, then the sum increases
//this way the new sum doesn't have to be calculated which saves time when calculating the sum

//the filter used is a circular buffer
//this makes the addition if a new value in linear time, rather then O(n) when shifting the values from the end of the buffer to the beginning

int parseNewSonarPoint(int newSonarData)
{
    static int filter[3];
    static unsigned int index;

    //get the datapoints from the filter
    const int outval = filter[index];
    filter[index] = newSonarData;

    //add the new sornar point to the filter
    //the filter acts as a circular buffer
    index++;
    if(index >= sizeof(filter) / sizeof(int))
    {
        index = 0;
    }

    //check if the filter isn't filled yet
    if(outval == 0)
    {
        return 0;
    }
    
    return newSonarData > outval;
}

int main()
{
	int increasecount = 0;
	int value = 0;

	//get values directly from stdin
    while(scanf("%d", &value) > 0)
    {
        increasecount += parseNewSonarPoint(value);
    }

    printf("increases: %d\n", increasecount);

    return 0;
}