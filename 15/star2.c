#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "common/common.h"

typedef struct graphNode_struct
{
	long distance;
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

int getQuadBit(int x, int y, int width, int height)
{
	int xQuad = x / width;
	int yQuad = y / height;
	int bit = (1 << ((yQuad * 5) + xQuad + 4));
	return bit;
}

int getPossitionValue(int x, int y, int width, int height, int graphPoints[height][width])
{
	//in what quadrant is this point
	int xQuad = x / width;
	int yQuad = y / height;
	int quadValOffset = yQuad + xQuad;
	int val = graphPoints[y % height][x % width];
	val = ((val & 0x0F) + quadValOffset);
	if(val > 9)
	{
		val = val % 10;
		val++;
	}

	return val;
}

int findShortestPath(int width, int height, int graphPoints[height][width])
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

	graphNode* endNode = createGraphNode((width * 5) - 1, (height * 5) - 1);

	//end the end node to the list
	pQueueAddItem(NeighborList, endNode, graphCompare);
	
	graphNode* checkNode = startNode;
	int numNodes = 0;
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
			int checkX = x -1;
			int checkY = y;
			int val = getPossitionValue(checkX, checkY, width, height, graphPoints);
			if((graphPoints[checkY % height][checkX % width] & getQuadBit(checkX, checkY, width, height)) == 0)
			{
				checkGraphNode(checkX, checkY, val, NeighborList, checkNode);
			}
		}
		if(x < ((width * 5) - 1))	//check right neighbor
		{
			int checkX = x +1;
			int checkY = y;
			int val = getPossitionValue(checkX, checkY, width, height, graphPoints);
			if((graphPoints[checkY % height][checkX % width] & getQuadBit(checkX, checkY, width, height)) == 0)
			{
				checkGraphNode(checkX, checkY, val, NeighborList, checkNode);
			}
		}
		if(y > 0)	//check upper neighbour
		{
			int checkX = x;
			int checkY = y -1;
			int val = getPossitionValue(checkX, checkY, width, height, graphPoints);
			if((graphPoints[checkY % height][checkX % width] & getQuadBit(checkX, checkY, width, height)) == 0)
			{
				checkGraphNode(checkX, checkY, val, NeighborList, checkNode);
			}
		}
		if(y < ((height * 5) - 1))	//check lower neighbour
		{
			int checkX = x;
			int checkY = y +1;
			int val = getPossitionValue(checkX, checkY, width, height, graphPoints);
			if((graphPoints[checkY % height][checkX % width] & getQuadBit(checkX, checkY, width, height)) == 0)
			{
				checkGraphNode(checkX, checkY, val, NeighborList, checkNode);
			}
		}


		//mark the current item as visited
		//mark the bit for the quadrant as visited
		graphPoints[y % height][x % width] |= getQuadBit(x, y, width, height);
		//add it to the visited list
		pQueueAddItem(VisitedList, checkNode, graphCompare);

		//get the next node with the lowest priority
		checkNode = pQueuePop(NeighborList);
		numNodes++;
	}
	printf("Nodes visited: %d\n", VisitedList->numItems);

	return endNode->distance;
}

int main(void)
{
	//load all input
	char** input = NULL;
	int height = 0;
	stdinToStrArr(&input, &height, 120);

	//turn all characters into numbers and write them to an int array
	//the lowest 4 bits denote the danger level of a part of the cave
	//the higher 28 bits denote if the point has been visited in a certain quadrant
	int width = strlen(input[0]);

	int caveDistances[height][width];
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			caveDistances[i][j] = input[i][j] - '0';
		}
	}

	//perform the challange?
	int shortestPathLength = findShortestPath(height, width, caveDistances);
		
	printf("safest path found %d\n", shortestPathLength);

	return 0;
}