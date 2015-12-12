#include <stdio.h>
#include <stdlib.h>

void process(const char *file_read, const char *file_write)
{
    FILE *f = fopen(file_read, "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    
    string[fsize] = 0;
    
    char *result_string = malloc(fsize + 1);
    
    int i = 0;
    int j = 0;
    for (i = 0; i < fsize + 1; ++i)
    {
        if (!(((string[i] >= '0') && (string[i] <= '9')) || ((string[i] == '-') && ((i + 1) < (fsize + 1)) && (string[i + 1] >= '0') && (string[i + 1] <= '9')) || ((string[i] == '.') && ((i - 1) >= 0) && (string[i - 1] >= '0') && (string[i - 1] <= '9') && ((i + 1) < (fsize + 1)) && (string[i + 1] >= '0') && (string[i + 1] <= '9')) || (string[i] == ' ')))
        {
            result_string[j] = string[i];
            ++j;
        }
    }
    
    result_string[j] = 0;
    
    FILE *f_write = fopen(file_write, "w");
    fputs(result_string, f_write);
    
    free(string);
    free(result_string);
}

int main(int argc, const char * argv[])
{
    process("read.txt", "write.txt");
    
    return 0;
}
