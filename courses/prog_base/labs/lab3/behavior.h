#ifndef __PROJ_LAB6_BEHAVIOR
#define __PROJ_LAB6_BEHAVIOR

void printArray(char *[], int);

void lengthOrder(char * [], int , int arr[10]);
char *getLongest(char * [], int);
char *getShortest(char * [], int);
void fillRandom(char * [], int, int);
void swapShLn(char * [], int);
void lessThan(char * [], int, int, char *tempStrArrForLessThan []);
void moreThan(char * [], int, int, char *tempStrArrForMoreThan []);
void wordsCount(char * [], int, int []);
int findNumInStr(char * [], int, int);
void findNumInAllStrings(char * [], int);

void drawConsole(char * [], int);

#endif
