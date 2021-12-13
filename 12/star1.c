#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "common/common.h"

//The idea of walking over a graph feels a bit intimidating
//especialy since I lost my algorithms and datastructures book when moving
//but what is a graph but a list of neighbours

typedef struct node_struct
{
	char id[6];
	char isSmallCave;
	char visited;
	int numNeighbours;
	struct node_struct* neighbours[10];
}node;

node* parseNodeList(char** startStrings, char** destStrings, int numStrings)
{
	node* nodeList[20];
	int numNodes = 0;

	for(int i = 0; i < numStrings; i++)
	{
		//find the node corospoinding to the id
		node* startNode = NULL;
		node* destNode = NULL;
		for(int n = 0; n < numNodes; n++)
		{
			if(strcmp(startStrings[i], nodeList[n]->id) == 0)
			{
				startNode = nodeList[n];
			}
			if(strcmp(destStrings[i], nodeList[n]->id) == 0)
			{
				destNode = nodeList[n];
			}
		}

		//if the node couldn't be found,
		//create a new node
		if(NULL == startNode)
		{
			node* newNode = (node*)malloc(sizeof(node));
			memset(newNode, 0, sizeof(node));
			strcpy(newNode->id, startStrings[i]);
			newNode->isSmallCave = *(startStrings[i]) >= 'a';

			nodeList[numNodes++] = newNode;
			startNode = newNode;
		}
		if(NULL == destNode)
		{
			node* newNode = (node*)malloc(sizeof(node));
			memset(newNode, 0, sizeof(node));
			strcpy(newNode->id, destStrings[i]);
			newNode->isSmallCave = *(destStrings[i]) >= 'a';

			nodeList[numNodes++] = newNode;
			destNode = newNode;			
		}

		//link these two as neighbours
		startNode->neighbours[startNode->numNeighbours++] = destNode;
		destNode->neighbours[destNode->numNeighbours++] = startNode;
	}

	//return the start node
	for(int i = 0; i < numNodes; i++)
	{
		if(strcmp(nodeList[i]->id, "start") == 0)
		{
			return nodeList[i];
		}
	}
	return NULL;
}

int traverseGraph(node* thisNode)
{
	//if we got to the end return 1;
	if(strcmp(thisNode->id, "end") == 0)
	{
		return 1;
	}

	int numPaths = 0;
	thisNode->visited = 1;

	//visit every unvisited neighbour
	for(int n = 0; n < thisNode->numNeighbours; n++)
	{
		node* neighbour = thisNode->neighbours[n];
		//if this neighbour has not been visited yet,
		//well... check it out
		if(!(neighbour->isSmallCave && neighbour->visited))
		{
			numPaths += traverseGraph(neighbour);
			//after we get back from our neighbour,
			//we have to mark it as unvisited so we can visit it
			//on our next run of the search
			neighbour->visited = 0;
		}
	}
	return numPaths;
}

int main(void)
{
	//get the input
	char** inputStrings = NULL;
	int numStrings = 0;
	stdinToStrArr(&inputStrings, &numStrings, 10);

	char** destStrings = splitStringArray(inputStrings, numStrings, "-");

	//parse the input into a graph
	node* startNode = parseNodeList(inputStrings, destStrings, numStrings);
	if(NULL == startNode)
	{
		printf("Something went wrong creating the graph\n");
	}

	int numRoutes = traverseGraph(startNode);

	printf("Number of routes: %d\n", numRoutes);

	return 0;
}