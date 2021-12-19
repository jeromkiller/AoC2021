#pragma once
//some generic functions that will probably be usefull in more projects

//parses stdin and returns array
//out: int* intArr, array of intergers
//out: int* elements, number of elements in the array
//returns: int, elements of the array including extra buffer
int stdinToIntArr(int** intArr, int* elements);

//parses a string array into a int array
//this function allocates new memory for the int array
//in: char** stringArr, string array to convert to an int array
//in: int size, number of ellements in the string array
//out: int** intArr, refference to save the int array to
//returns: int, amount of items added to the list
int strArrToIntArr(char** stringArr, int size, int** intArr);

//parses a string array into a int array
//this function allocates new memory for the int array
//in: char** stringArr, string array to convert to an int array
//in: int size, number of ellements in the string array
//out: int** intArr, refference to save the int array to
//returns: int, amount of items added to the list
int strArrToInt8Arr(char** stringArr, int size, char** intArr);

//parses stdin and returns array
//out: int* stringArr, array of character pointers
//out: int* elements, number of elements in the array
//in: int maxBuffer, the max size of the buffer for each string
//returns: int, elements of the array including extra buffer
int stdinToStrArr(char*** stringArr, int* elements, int maxBuffer);

//Reads a single line from stdin and returns it as a new string
//out: char**, refference to where you want to keep the string
//in: int maxBuffer, max amount of characters to read
//returns: int, string length
int stdinToSingleString(char** stringRef, int maxBuffer);

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

//perfoms strtok() on an entire string and places all tokens in an array
//new buffers don't get created for the split string,
//freeing the original string will also free the data pointed to in the array.
//in: char* string, string to tokenize
//in: const char* delimiter, the delimiting character for the strtok() opperation
//out: char*** bufferPointer, refference to save set the new string array to
//returns: ammount of items in the array
int splitStringToArray(char* string, const char * delimiter, char*** bufferPointer);

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

//the same as above, but instead places the item in front of the insertion point
listItem* dRefList_AddItemFront(listItem** insertionPoint, void* newRef);

//removes an item from the list, when an item is removed from the middle, the neighbours will be linked together
//in: listItem* item, the node to remove
//returns: listItem* the previous item, if its not null
listItem* dRefList_RemoveItem(listItem* item);

//TODO: create a function to remove all items and free the list 

//Generic Stack structure, can be used to store 
typedef struct genericStack_struct
{
	void* stackStart;	//pointer to the stack data
	size_t stackSize;	//number of bytes in the stack
	size_t itemSize;	//number of bytes for each item on the stack
	int stackPointer;	//possition for the top item
}genStack;

//greate a generic stack, has room for 25 items
//in: size_t itemSize, size of the items you want to store on the stack
//returns: genStack*, a pointer to your newly created generic stack
genStack* genStackCreate(size_t itemSize);

//push an item onto the generic stack
//the stack grows as needed
//in: genStack** stackRef, A refference to the stack so it can be modified to grow
//in: void* item, pointer to an item to copy to the stack
void genStackPush(genStack** stackRef, void* item);

//pop an item from the generic stack
//the stack shrinks as needed
//in: genStack** stackRef, A refference to the stack so it can be modified to shrink
//returns: void*, a pointer to the item just popped from the stack (to be derefferenced as needed by the user)
void* genStackPop(genStack** stackRef);

//peek at the top item on the stack
//in: genStack* stack, pointer to the stack
//returns: void*, a pointer to the item just peeked from the stack (to be derefferenced as needed by the user)
void* genStackPeek(genStack* stack);

//frees the stack and then the stack object itself
//in: genStack*, a pointer to the stack to free
void genStackFree(genStack* stack);

//clear the items off the stack,
//in: genStack** stackRef, a refference to the stack so it can be modified to shrink
void genStackClear(genStack** stackRef);

//get the number of items on the stack
//in: genStack* a pointer to the stack
int genStackCount(genStack* stack);


//functions to control the generic stack as a char stack
//see above for a better discription

//create a stack for char
genStack* charStackCreate(void);

//push a char to the stack
void charStackPush(genStack** stackRef, char value);

//pop a char from the stack
char charStackPop(genStack** stackRef);

//peek a char from the stack
char charStackPeek(genStack* stack);

//functions to control the generic stack as an int stack
//create a stack for longs
genStack* longStackCreate(void);

//push a long to the stack
void longStackPush(genStack** stackRef, long value);

//pop a long from the stack
long longStackPop(genStack** stackRef);

//peek a long from the stack
long longStackPeek(genStack* stack);


//struct for a priority queue using the doubly linked list we created earlier
typedef struct pQueue_struct
{
	listItem* queueStart;
	int numItems;
	char returnBuffer[50]; //should be enough space :P
}pQueue;

//Create a Priority queue
pQueue* pQueueCreate();

//add an item to the priority queue
void pQueueAddItem(pQueue* priorityQueue, void* item, int(comparFunc)(void*, void* ));

//peek the first item on the queue
void* pQueuePeek(pQueue* priorityQueue);

//pop the first item from the queue
void* pQueuePop(pQueue* priorityQueue);
