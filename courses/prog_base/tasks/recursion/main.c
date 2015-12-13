#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char recFunc (char * strStart, char * strCur)
{
    if (strStart > strCur - 1) return 0;
    else if (*strCur == *(strCur - 1)) return *strCur;
    else return recFunc(strStart, strCur - 1);
}

int main (void)
{
    char str[100];
    char * strStart;
    char * strCur;
    printf("Enter your string, pls: ");
    fflush(stdin);
    fgets(str, strlen(str), stdin);
    printf("The last character repeated more than once: %c\n", recFunc(str, str + strlen(str)-1));
    return 0;
}
