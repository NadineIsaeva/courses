#include <stdio.h>
#include <stdlib.h>

int main()

{
char arr1[10] = "abcdefghij";
char arr2[10] = "klmnoprstu";
char res[10];
int i;
for (i=0; i<10; ++i) {
    res[i] = arr1[i] - arr2[i];
}
for (i=0; i<10; ++i)
{
printf("%i ", res[i]);
}
}
