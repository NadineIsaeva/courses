#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "nlp.h"

const char *fileName = "text.txt";
const char *fileNameOut = "text.csv";

int main()
{
    FILE *file = fopen(fileName, "r");
    fseek(file, 0, SEEK_END);
    size_t fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *fileStr = malloc((fileLength + 1) * sizeof(char));
    fread(fileStr, 1, fileLength, file);
    fileStr[fileLength] = '\0';
    fclose(file);
    text_t *text = text_create_str(fileStr, strlen(fileStr));
    free(fileStr);
    text_print(text, stdout);
    printf("\n\n");
    text_sort(text);
    text_print(text, stdout);

    FILE *fileOut = fopen(fileNameOut, "w");
    text_print(text, fileOut);
    fclose(fileOut);

    text_delete(text);

    return 0;
}
