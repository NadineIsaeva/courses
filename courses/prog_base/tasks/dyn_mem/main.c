#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char * inputString = (char *) calloc(50, sizeof(char));
    printf("Enter your string, please: ");
    gets(inputString);

    while (*inputString)
        {
            if ((*(inputString + 1)) == '\0')
            {
                if (*inputString >= 'a' && *inputString <= 'z')
                {
                    printf("%c", *inputString);
                    break;
                }
                else
                {
                    putchar('0');
                    break;
                }
            }
        *inputString++;
        }

 free(inputString);

return 0;
}
