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