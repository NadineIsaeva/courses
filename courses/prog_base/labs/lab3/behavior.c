#include "behavior.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int sortfunc(const void * a, const void * b)
{
	return (*(int*)b - *(int*) a);
}

void lengthOrder(char *myText[], int len, int arr[10]) {
	int i, myStrLen = 0;
	for (i = 0; i < len; i++) {
		myStrLen = strlen(myText[i]);
		arr[i] = myStrLen;
	}
	qsort(arr, len, sizeof(int), sortfunc);
}

char *getLongest(char *myText[], int len) {
	char *longest = myText[0];
	for (;len--;) {
		if (strlen(longest) <= strlen(myText[len])) {
			longest = myText[len];
		}
	}
	return longest;
}

char *getShortest(char *myText[], int len) {
	int i;
	char *shortest = myText[0];
	for (i = 0; i < len; i++) {
		if (strlen(myText[i]) <= strlen(shortest)) {
			shortest = myText[i];
		}
	}
	return shortest;
}

void fillRandom(char *myText [], int len, int n) {
	time_t t;
	srand((unsigned) time(&t));
	int i, j;
	char *randChars;
	for (i = 0; i < len; i++) {
		randChars = (char*)malloc(n*sizeof(char));
		for (j = -1; j < n;) {
			j++;
			if (n == j) {
				randChars[j] = '\0';
				break;
			}
			randChars[j] = (char)((rand() % 94) + 33);
		}


	}
}

void swapShLn(char * myText [], int len) {
	char *shLine, *lnLine, *temp;
	int i, shIndex, lnIndex;
	shLine = getShortest(myText, len);
	lnLine = getLongest(myText, len);
	temp = shLine;
	for (i = 0; i < len; i++) {
		if (!strcmp(myText[i], shLine)) {
			shIndex = i;
		}
		if (!strcmp(myText[i], lnLine)) {
			lnIndex = i;
		}
	}
	*(myText + shIndex) = lnLine;
	*(myText + lnIndex) = temp;
}

void lessThan(char * myText [], int len, int value, char *tempStrArrForLessThan[]) {
	int i;
	for (i = 0; i < len; i++) {
		if (strlen(myText[i]) < (size_t)value) {
			strcpy(tempStrArrForLessThan[i], myText[i]);
		}
	}
}

void moreThan(char * myText [], int len, int value, char *tempStrArrForMoreThan[]) {
	int i;
	for (i = 0; i < len; i++) {
		if (strlen(myText[i]) > (size_t)value) {
			strcpy(tempStrArrForMoreThan[i], myText[i]);
		}
	}
}

void wordsCount(char *myText [], int len, int wordsResult[]) {
	const char *invalid_characters = " 1234567890!@#$%^&*()_+=-{}[];:<>,./?|\\\"'~`";
	int words, i = 0;
	for (i = 0; i < len; i++) {
		char *c = myText[i];
		words = 0;
		while (*c) {
			if (!strchr(invalid_characters, *c)) {
				words++;
				while (!strchr(invalid_characters, *c)) {
					c++;
				}
			}
			c++;
		}
		wordsResult[i] = words;
	}
}

int findNumInStr(char * myText [], int len, int index) {
	int val;
	val = atoi(myText[index]);
	return val;
}
