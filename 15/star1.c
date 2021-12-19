#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "common/common.h"

typedef struct graphNode_struct
{
	int distance;
	int posX;
	int posY;
	struct graphNode_struct* prevNode;
}graphNode;

int graphCompare(void* node1, void* node2)
{
	int n1 = ((graphNode*)node1)->distance;
	int n2 = ((graphNode*)node2)->distance;

	return n1 - n2;
}

graphNode* findAndRemoveNodeFromList(pQueue* queue, int x, int y)
{
	//just get the list from the queue, that will itterate easier
	listItem* list = queue->queueStart;
	while(list)
	{
		graphNode* node = (graphNode*)list->item;
		if(node->posX == x && node->posY == y)
		{
			if(list == queue->queueStart)
			{
				queue->queueStart = list->next;
			}
			dRefList_RemoveItem(list);
			queue->numItems--;
			return node;
		}
		list = list->next;
	}
	return NULL;
}

graphNode* createGraphNode(int x, int y)
{
	//create a new node
	graphNode* newNode = (graphNode*)malloc(sizeof(graphNode));
	newNode->distance = INT_MAX;
	newNode->posX = x;
	newNode->posY = y;
	newNode->prevNode = NULL;

	return newNode;
}

graphNode* checkGraphNode(int x, int y, int val, pQueue* NeighborList, graphNode* checkNode)
{
	graphNode* neighborNode = findAndRemoveNodeFromList(NeighborList, x, y);
	if(neighborNode == NULL)
	{
		neighborNode = createGraphNode(x, y);
	}
	int newDist = checkNode->distance + val;
	if(newDist < neighborNode->distance)
	{
		//assign the right distance
		neighborNode->distance = newDist;
		neighborNode->prevNode = checkNode;
	}

	//and put it back in so it's in the right place now
	pQueueAddItem(NeighborList, neighborNode, graphCompare);
	return neighborNode;
}

int findShortestPath(char** graphPoints, int numLines)
{
	//make two priority queues,
	//one for points we have to deal with,
	//the other for points he have visited
	pQueue* NeighborList = pQueueCreate();
	pQueue* VisitedList = pQueueCreate();

	//add the start and final point to the queue
	//start at {0, 0}
	graphNode* startNode = createGraphNode(0, 0);
	startNode->distance = 0;

	int width = strlen(graphPoints[0]);
	graphNode* endNode = createGraphNode(width - 1, numLines - 1);

	//end the end node to the list
	pQueueAddItem(NeighborList, endNode, graphCompare);
	
	graphNode* checkNode = startNode;

	while(NeighborList->numItems > 0)
	{
		//if we expanded into the end node, that means we found the shortest path
		if(checkNode == endNode)
		{
			break;
		}
		int x = checkNode->posX;
		int y = checkNode->posY;
		//check if the neighbours of the node have been visited
		//if not, calculate its distance and push it on the queue
		if(x > 0)	//check left neighbour
		{
			char val = graphPoints[y][x - 1];
			if(val < 10)
			{
				checkGraphNode(x - 1, y, val, NeighborList, checkNode);
			}
		}
		if(x < width - 1)	//check right neighbor
		{
			char val = graphPoints[y][x + 1];
			if(val < 10)
			{
				checkGraphNode(x + 1, y, val, NeighborList, checkNode);
			}
		}
		if(y > 0)	//check upper neighbour
		{
			char val = graphPoints[y - 1][x];
			if(val < 10)
			{
				checkGraphNode(x, y - 1, val, NeighborList, checkNode);
			}
		}
		if(y < numLines - 1)	//check lower neighbour
		{
			char val = graphPoints[y + 1][x];
			if(val < 10)
			{
				checkGraphNode(x, y + 1, val, NeighborList, checkNode);
			}
		}


		//mark the current item as visited
		graphPoints[y][x] += 10;
		//add it to the visited list
		pQueueAddItem(VisitedList, checkNode, graphCompare);

		//get the next node with the lowest priority
		checkNode = pQueuePop(NeighborList);
	}


	printf("Path to end node:\n");

	for(int y = 0; y < numLines; y++)
	{
		for(int x = 0; x < width; x++)
		{
			graphNode* returnNode = endNode;
			while(returnNode)
			{
				if(x == returnNode->posX && y == returnNode->posY)
				{
					printf("\033[0;31m");
				}
				returnNode = returnNode->prevNode;
			}
			int val = graphPoints[y][x];
			printf("%d\033[0m", val < 10 ? val : val -10);
		}
		printf("\n");
	}

	return endNode->distance;
}

int main(void)
{
	//load all input
	char** input = NULL;
	int numLines = 0;
	stdinToStrArr(&input, &numLines, 120);

	//turn all characters into numbers
	int strLength = strlen(input[0]);
	for(int i = 0; i < numLines; i++)
	{
		for(int j = 0; j < strLength; j++)
		{
			input[i][j] = input[i][j] - '0';
		}
	}

	//perform the challange?
	int shortestPathLength = findShortestPath(input, numLines);
		
	printf("shorted path found %d\n", shortestPathLength);

	return 0;
}