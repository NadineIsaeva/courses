#include <stdio.h>
#include <stdlib.h> // for malloc and free
#include <ctype.h> // for islower and isalpha
#include <string.h>

int main(void)
{
    char * inputString = NULL;
    char * resultString = NULL;
    inputString = (char *) malloc(50 * sizeof(char));
    resultString = (char *) malloc(5 * sizeof(char));

    if (NULL == inputString || NULL == resultString)
    {
        printf("Error of memory allocation");
        return EXIT_FAILURE;
    }

    printf("Enter your string, please: ");
    scanf("%s", inputString);

    while(NULL != *inputString)
    {
        if (islower(*inputString) != 0)
        {
            *resultString = *inputString;
            resultString[1] = '\0';
        }
        *inputString++;
    }

    if (isalpha(resultString[0]) == 0)
    {
        putchar('0');
    }
    else
    {
        printf("The last lower letter is: ");
        putchar(resultString[0]);
    }

    free(inputString);
    free(resultString);
    return EXIT_SUCCESS;
}

