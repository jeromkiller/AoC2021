#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "common/common.h"

//since the polymer is going to grow exponentialy
//i'm not going to create a big list again for all the characters
//instead i'm just going to keep track of the polymer pairs in a hashmap
//this will be my first time playing around with something like that in C
//so its probably not that space efficient or convinient to use

//structure for storing the polymer pairs and the new results
typedef struct polyPair_struct
{
	char pair[3];
	char insertChar;
	char result1[3];
	char result2[3];
	unsigned long count;
}polyPair;

//hash a string, using a polynimial rolling hash
//the table will have nearly 1000 entries, but that should fit any two letter combination (alphabetized)
//in testing with my testInput this should not result in any collisions
//thanks to https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
//for helping my cover for my lack of cryptograpy knowlegde
int hashfunc(char* key)
{
    const int p = 31;
    const int m = 997;
    int power_of_p = 1;
    int hash_val = 0;
 
    // Loop to calculate the hash value
    // by iterating over the elements of string
    for (int i = 0; i < (int)strlen(key); i++) {
        hash_val = (hash_val + (key[i] - 'A' + 1) * power_of_p)  % m;
        power_of_p = (power_of_p * p) % m;
    }
   
  //return positive remainder only
    return (hash_val%m + m) % m;
}

//parse the input line into the polypair struct
polyPair* createPolyPair(char* line)
{
	//get the different values from the line
	char string[3];
	char insertChar;
	sscanf(line, "%2s -> %c", string, &insertChar);
	
	//create and fill the new pair
	polyPair* newPair = (polyPair*)malloc(sizeof(polyPair));
	strcpy(newPair->pair, string);
	newPair->count = 0;
	newPair->insertChar = insertChar;
	
	//also fill in the resulting values
	strcpy(newPair->result1, string);
	strcpy(newPair->result2, string);
	newPair->result1[0] = insertChar;
	newPair->result2[1] = insertChar;

	return newPair;
}

void clearTableCounts(polyPair** table, int tableSize)
{
	for(int i = 0; i < tableSize; i++)
	{
		polyPair* pair = table[i];
		if(pair)
		{
			pair->count = 0;
		}
	}
}

void insertPolymerLetter(polyPair** toTable, polyPair** fromTable, int tableSize, unsigned long* insertCharTable)
{
	//clear the numbers on the fromTable
	clearTableCounts(toTable, tableSize);

	for(int i = 0; i < tableSize; i++)
	{
		polyPair* pair = fromTable[i];
		if(pair)
		{
			char insertionChar = pair->insertChar;
			char* insertResult1 = pair->result1;
			char* insertResult2 = pair->result2;

			insertCharTable[insertionChar - 'A'] += pair->count;

			int hash = hashfunc(insertResult1);
			toTable[hash]->count += pair->count;
			
			hash = hashfunc(insertResult2);
			toTable[hash]->count += pair->count;

		}
	}
}

int main(void)
{
	//parse the input
	char** inputStrings = NULL;
	int numStrings = 0;
	stdinToStrArr(&inputStrings, &numStrings, 15);

	//create a "hashtable"
	polyPair* hashTable1[997];
	polyPair* hashTable2[997];
	memset(hashTable1, 0, sizeof(hashTable1));
	memset(hashTable2, 0, sizeof(hashTable2));
	//then fill it
	for(int i = 2; i < numStrings; i++)
	{
		polyPair* newPair = createPolyPair(inputStrings[i]);
		int hash = hashfunc(newPair->pair);
		hashTable1[hash] = newPair;
		
		//also allocate a copy for the second table
		newPair = createPolyPair(inputStrings[i]);
		hashTable2[hash] = newPair;
	}

	//add the number of pairs
	for(int i = 0; i < (int)strlen(inputStrings[0]) - 1; i++)
	{
		char pair[3];
		sscanf(&(inputStrings[0][i]), "%2s", pair);
		int hash = hashfunc(pair);
		hashTable1[hash]->count++;
	}

	//keep count of the amount of each char
	unsigned long chars[26];
	memset(chars, 0, sizeof(chars));
	for(int i = 0; i < (int)strlen(inputStrings[0]); i++)
	{
		int charIndex = inputStrings[0][i] - 'A';
		chars[charIndex]++;
	}

	//perform the challange
	for(int i = 0; i < 10; i++)
	{
		if(i % 2)
		{
			insertPolymerLetter(hashTable1, hashTable2, 997, chars);
		}
		else
		{
			insertPolymerLetter(hashTable2, hashTable1, 997, chars);
		}
	}
	
	//find the highest and lowest counts
	unsigned long high = 0, low = ULONG_MAX;
	for(int i = 0; i < 26; i++)
	{
		unsigned long count = chars[i];
		if(count != 0)
		{
			if(high < count)
			{
				high = count;
			}
			if(low > count)
			{
				low = count;
			}
		}
	}

	unsigned long result = high - low;
	printf("result: %ld\n", result);

	return 0;
}
