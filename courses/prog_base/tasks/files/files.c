#include <stdio.h>
#include <stdlib.h>

#define VARIANT 4

void fprocess(const char *pread, const char *pwrite);

int main(int argc, const char * argv[])
{
    fprocess("read.txt", "write.txt");

    return 0;
}

void fprocess(const char *pread, const char *pwrite)
{
    FILE *file_read = fopen(pread, "r");
    FILE *file_write = fopen(pwrite, "w");
    int line = 1;
    char ch = 0;
    int max = 0;
    int length = 0;

    while (line < VARIANT)
    {
        ch = fgetc(file_read);
        if (ch == '\n')
            ++line;
    }

    while (1)
    {
        ch = fgetc(file_read);

        if ((ch == ' ') || (ch == '\n'))
        {
            if (length > max)
                max = length;

            if (ch == '\n')
                break;

            length = 0;
        }
        else
        {
            ++length;
        }
    }

    fprintf(file_write, "%i", max);
}
