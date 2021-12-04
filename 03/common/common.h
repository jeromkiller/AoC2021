#pragma once
//some generic functions that will probably be usefull in more projects

//parses stdin and returns array
//out: int* intArr, array of intergers
//out: int* elements, number of elements in the array
//returns: int, elements of the array including extra buffer
int stdinToIntArr(int** intArr, int* elements);

//parses stdin and returns array
//out: int* stringArr, array of character pointers
//out: int* elements, number of elements in the array
//in: int stringsize, the size of the buffer for each string
//returns: int, elements of the array including extra buffer
int stdinToStrArr(char*** stringArr, int* elements, int stringsize);

//free's all the strings in an array, then frees itself
//in: char** stringArr, the string array to free
//in: int size, the size of the array;
//returns: int, the mount of ellements removed
int freeStrArr(char** stringArr, const int size);

//performs strtok() on all ellements of the array,
//and returns an array of pointers to the second element
//New buffers don't get created for the new array,
//freeing the original array will also free the freed array
//in: char** stringArr, array of strings
//in: int size, the size of the stringArray
//in: int delimiter, the delimiting character for the strtok() opperation
//returns char**, array of second tokens of the original array
char** splitStringArray(char** stringArr, const int size, const char * delimiter);

//doubly linked list
typedef struct t_listItem
{
	void* item;
	struct t_listItem* prev;
	struct t_listItem* next;
}listItem;

//turn a pointer array into a list
//removing items does not remove them from the original array
//in: void*, array of pointers to add to create a doubly linked list from
//in: const int size, ammount of items in the array
//returns listItem*: a pointer to the first item in the list
listItem* createRefListToArr(void* Arr, const int size);

//add an item to a doubly linked list
//this can be used to create the first node, append to the end or insert in the middle
//in: listItem**, pointer to an item to place the new refference behind
//insertionPoint can be NULL, this essentialy creates the first item
//in: void* newRef, pointer to add to the list
//returns: listItem*, a pointer to the newly created item
listItem* dRefList_AddItem(listItem** insertionPoint, void* newRef);

//removes an item from the list, when an item is removed from the middle, the neighbours will be linked together
//in: listItem* item, the node to remove
//returns: listItem* the next item in the list
listItem* dRefList_RemoveItem(listItem* item);

//TODO: create a function to remove all items and free the list 