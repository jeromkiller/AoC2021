#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/common.h"

#define BINGO_ROWS 5
#define BINGO_COLUMS 5
typedef struct bingoCard_struct
{
	int numbers[BINGO_ROWS][BINGO_COLUMS];
	char marked[BINGO_ROWS][BINGO_COLUMS];
}bingoCard;

void printBingoCard(bingoCard* card, int calledNum)
{
	for(int row = 0; row < BINGO_ROWS; row++)
	{
		for(int col = 0; col < BINGO_COLUMS; col++)
		{
			if(card->marked[row][col])
			{
				printf("\033[0;32m");
			}
			if(card->numbers[row][col] == calledNum)
			{
				printf("\033[0;31m");
			}
			printf("%2d\033[0m ", card->numbers[row][col]);
		}
		printf("\n");
	}
}

bingoCard* generateBingoCard(char** bingoStrings)
{
	//reserve space for the new bingocard
	bingoCard* newCard = (bingoCard*)malloc(sizeof(bingoCard));
	memset(newCard, 0, sizeof(bingoCard));

	for(int row = 0; row < BINGO_ROWS; row++)
	{
		//get each row
		int newRow[5];
		sscanf(bingoStrings[row], "%d %d %d %d %d", &newRow[0], &newRow[1], &newRow[2], &newRow[3], &newRow[4]);
		memcpy(newCard->numbers[row], newRow, sizeof(newRow));
	}

		return newCard;
}

char checkBingo(bingoCard* card, int row, int column)
{
	//check if there was a bingo in this row
	char rowBingo = 1;
	for(int colNum = 0; (colNum < BINGO_COLUMS); colNum++)
	{
		rowBingo &= card->marked[row][colNum];
	}
	char colBingo = 1;
	for(int rowNum = 0; (rowNum < BINGO_ROWS); rowNum++)
	{
		colBingo &= card->marked[rowNum][column];
	}

	return rowBingo | colBingo;
}

int playBingo(listItem* bingoCards, int* bingoNumbers, int numBingoRolls)
{	
	//roll all the different numbers
	listItem* currentItem = NULL;
	bingoCard* currentCard = NULL;
	char bingoGot = 0;
	int roll = 0;
	int rollVal = 0;
	for(; (roll < numBingoRolls) && (bingoGot == 0); roll++)
	{
		rollVal = bingoNumbers[roll];
		currentItem = bingoCards;
		//apply this roll to every bingo card
		while(currentItem && (bingoGot == 0))
		{
			currentCard = (bingoCard*)currentItem->item;
			//run over every bingo card number
			for(int row = 0; (row < BINGO_ROWS) && (bingoGot == 0) ; row++)
			{
				for(int col = 0; (col < BINGO_COLUMS) && (bingoGot == 0); col++)
				{
					//if this number is on the card
					if(currentCard->numbers[row][col] == rollVal)
					{
						//mark the number, and check if we got a bingo
						currentCard->marked[row][col] = 1;
						bingoGot = checkBingo(currentCard, row, col);
					}
				}
			}
			currentItem = currentItem->next;
		}
	}

	//we got a bingo, or we exhausted all the cards
	if(!bingoGot)
	{
		printf("We don't have a bingo :(\n");
		return -1;
	}	

	printf("winning card after %d numbers with number: %d\n", roll, rollVal);
	printBingoCard(currentCard, rollVal);

	//sum all the unmarked numbers on the bingo card
	int sum = 0;
	for(int row = 0; row < BINGO_ROWS; row++)
	{
		for(int col = 0; col < BINGO_COLUMS; col++)
		{
			//if this number is on the card
			if(!currentCard->marked[row][col])
			{
				sum += currentCard->numbers[row][col];
			}
		}
	}

	return sum * rollVal;
}

int main(void)
{
	char** input = NULL;
	int size = 0;
	stdinToStrArr(&input, &size, 300);

	//the first entry are the bingo numbers
	//split the bingo string into an array of numbers
	//first we make strtok a the first line a bunch of times and create a refArray to the induvidual numbers;
	//(this will be turned into a function for the common header)

	int bingoRolls = 0;
	int* bingoNumbers = NULL;
	const char* delim = ",";
	{
		//count the amount of delimiting characters to see how much tokens we have
		char** bingoStrings = NULL;
		int tokCount = 1; //assume there is at least a first item
		for(int i = 0; (*input)[i]; i++)
		{
			tokCount += (*input)[i] == *delim;
		}

		//reserve some memory for refferences to the tokens
		bingoStrings = (char**)malloc(tokCount * sizeof(char*));

		//then tokenize the strings
		bingoStrings[0] = strtok(*input, delim);
		for(int i = 1; i < tokCount; i++)
		{
			bingoStrings[i] = strtok(NULL, delim);
		}

		//now we have a string array of all the different numbers
		//let's add these to an int array
		bingoNumbers = (int*)malloc(tokCount * sizeof(int));
		for(int i = 0; i < tokCount; i++)
		{
			bingoNumbers[i] = atoi(bingoStrings[i]);
		}

		//clean up the old reflist
		free(bingoStrings);

		bingoRolls = tokCount;
	}

	//now we have parsed all of the bingo rolls
	//so we have to create the bingo cards
	int cardStringIndex = 2;
	bingoCard* newCard = generateBingoCard(input + cardStringIndex);
	listItem* CardListRoot = dRefList_AddItem(NULL, newCard);
	listItem* newItem = CardListRoot;
	for(cardStringIndex += (BINGO_ROWS + 1); cardStringIndex < size; cardStringIndex += (BINGO_ROWS + 1))
	{
		newCard = generateBingoCard(input + cardStringIndex);
		newItem = dRefList_AddItem(&newItem, newCard);
	}

	int winnersum = playBingo(CardListRoot, bingoNumbers, bingoRolls);
	
	printf("sum of unmarked numbers: %d\n", winnersum);

	return 0;
}