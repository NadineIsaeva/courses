#include <stdlib.h>
#include <stdio.h> //for fgets
#include <string.h>
#include <ctype.h>

int main(void)
{
    char * inputString = (char *)malloc(50 * sizeof(char));
    int * i = (int *)malloc(sizeof(int));
    char * result = (char *)malloc(sizeof(char));
    *i = 50;
    *result = 0;
    printf("Enter your string, please: ");
    fgets(inputString, *i, stdin);
    for(*i = 0; *i < strlen(inputString) - 1; (*i)++)
        {
            if(islower(inputString[*i]))
            *result = inputString[*i];
        }
    if (*result == 0)
    {
       puts("0");
    }
     else
     {
         puts (result);
     }
    free(inputString);
    free(i);
    free(result);
    return EXIT_SUCCESS;
}
