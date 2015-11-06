#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <math.h>

void fillRand2(int arr[], int size)
{
    srand(time(NULL));
    int i;
    for (i=0; i < size; i++)
        {
        arr[i] = rand() % 511 - 255;
        }
}

int checkRand2(int arr[], int size)
 {
    int i;
    for (i=0; i < size; i++)
    {
            if(arr[i] < -255 || arr[i] > 255)
                {
                    return 0;
                }
    }
    return 1;
}

float meanValue(int arr[], int size)
{
    int sum = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum / (float)size;
 }

 int minValue(int arr[], int size)
 {
    int min = arr[0];
    int i;
    for (i = 1; i < size; i++)
        {
            if (arr[i] < min)
            {
                min = arr[i];
            }
        }
    return min;
 }

 int meanIndex(int arr[], int size)
 {
    float mean = meanValue(arr, size);
    int index = 0;
    float median = fabs(mean - arr[0]);

    int i;
    for (i = 1; i < size; i++)
    {
       float tempMedian = fabs(mean - arr[i]);
       if (tempMedian < median)
       {
           index = i;
           median = tempMedian;
       }
    }
    return index;

 }

 int minIndex(int arr[], int size)
 {
     int min = minValue(arr, size);
     int i;
     for (i = 0; i < size; i++)
        {
         if (arr[i] == min)
            {
             return i;
            }
        }
}

int maxOccurance(int arr[], int size)
{
    int currMax = 0;
    int currOccur = 0;

    int i,y;
    for (i = 0; i < size; i++)
    {
        int tempOccur = 1;
            for(y = i; y < size; y++)
                {
                    if (arr[i] == arr[y])
                    {
                        tempOccur++;
                    }
                }
            if (tempOccur > currOccur)
            {
                currOccur = tempOccur;
                currMax = arr[i];
            }
            else
            if (tempOccur == currOccur && currMax < arr[i])
            {
                currMax = arr[i];
            }
}

    return currMax;
}

int diff(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        res[i] = arr1[i] - arr2[i];
    }
    for (i = 0; i < size; i++)
    {
        if (res[i] != 0)
        {
            return 0;
        }
    }
    return 1;
}

void add(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        res[i] = arr1[i] + arr2[i];
    }
}

int gteq(int arr1[], int arr2[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr1[i] < arr2[i])
        {
            return 0;
        }
    }
    return 1;
}

void land(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        res[i] = arr1[i] & arr2[i];
    }
}

int main(){}

