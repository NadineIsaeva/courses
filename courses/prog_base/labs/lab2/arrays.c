#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void fillRand2(int arr[], int size)
{
    int i;
	time_t t;
	srand((unsigned) time(&t));
	for (i = 0; i < size; i++){
		arr[i] = rand() % 511-255;
	}

}
int checkRand2(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++){
		if ((arr[i]<-255) || (arr[i]>255)){
			return 0;
		}
	}
	return 1;
}

float meanValue(int arr[], int size)
{
	int i, sum = 0;
	for (i = 0; i < size; i++){
		sum += arr[i];
	}
	return sum / (float)size;
}

int minValue(int arr[], int size)
{
	int i;
	int minval = arr[0];
	for (i = 0; i < size; i++){
		if (arr[i] < minval){
			minval = arr[i];
		}
	}
	return minval;
}

int meanIndex(int arr[], int size)
{

}


