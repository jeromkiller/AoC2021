#pragma once
//some generic functions that will probably be usefull in more projects

//parses stdin and returns array
//out: int* intArr, array of intergers
//out: int* elements, number of elements in the array
//returns: elements of the array including extra buffer
int stdinToIntArr(int** intArr, int* elements);