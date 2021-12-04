#include <stdio.h>
#include <string.h>
#include "common/common.h"

int filterSupportStatus(listItem* listStart, int numBits, char useHighest)
{
	listItem* listRoot = listStart;
	int listCount = 0;
	//loop over each bit
	for(int bit = 0; (bit < numBits) && (listCount != 1); bit++)
	{
		//count how many 1's we have, and how many items we have left in the list
		int oneCount = 0;
		listCount = 0;

		listItem* currentItem = listRoot;
		while(currentItem)
		{
			char* string = *(char**)currentItem->item;
			oneCount += (string[bit] == '1');
			currentItem = currentItem->next;
			listCount++;
		}

		//check wich char we have to keep
		char keepchar = (oneCount >= (listCount - oneCount)) ^ useHighest ? '0' : '1';
		//roll over the list again, and remove the unneeded items
		currentItem = listRoot;
		while(currentItem)
		{
			char* string = *(char**)currentItem->item;
			if(string[bit] != keepchar)
			{
				//toss out this entry in the list
				currentItem = dRefList_RemoveItem(currentItem);
				listCount--;
				
				if(NULL != currentItem)
				{
					//if we deleted the root node
					if(NULL == currentItem->prev)
					{
						//then this is the new root node
						listRoot = currentItem;
					}
				}
			}
			else
			{
				//item should be kept
				currentItem = currentItem->next;
			}
		}
	}

	//synthesize the int value of the string
	int value = 0;
	for(int bit = 0; bit < numBits; bit++)
	{
		value = (value << 1) | ((*(char**)(listRoot->item))[bit] == '1');
	}

	//free the final list item
	dRefList_RemoveItem(listRoot);

	return value;
}

int calcLifeSupportStatus(char** input, int size)
{
	//create a ref lists to remove items from
	listItem* O2List = createRefListToArr(input, size);
	listItem* Co2List = createRefListToArr(input, size);

	//how many bits are in the string?
	const int numBits = strlen(*(char**)(O2List->item));

	const int o2Rating = filterSupportStatus(O2List, numBits, 1);
	const int Co2Rating = filterSupportStatus(Co2List, numBits, 0);

	printf("ratings: %d, %d\n",o2Rating, Co2Rating);

	return o2Rating * Co2Rating;
}


int main(void)
{
	char** input = NULL;
	int size = 0;
	stdinToStrArr(&input, &size, 20);

	//do the challange
	int lifeSupportStatus = calcLifeSupportStatus(input, size);

	//print the result
	printf("Life Support Status: %d\n", lifeSupportStatus);

	freeStrArr(input, size);

	return 0;
}