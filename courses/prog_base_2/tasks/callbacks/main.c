#include <stdio.h>
#include <string.h>

typedef void (*CharAlertCB)(char a, char b, const char *message);
typedef void (*CharCompareCB)(char a, char b, CharAlertCB alertCB);

void alertChars(char a, char b, const char *message) {
    printf("'%c' is < '%c': %s\n", a, b, message);
}

void compareChars(char a, char b, CharAlertCB alertCB) {
    if (a < b)
        alertCB(a, b, "Muhahahha");
}

void check(const char *str, CharCompareCB checkCB) {
    int i;
    for (i = 0; i < strlen(str) - 1; ++i)
        checkCB(str[i], str[i + 1], alertChars);
}

int main()
{
    check("Lorem ipsum dolor sit amet", compareChars);

    return 0;
}
