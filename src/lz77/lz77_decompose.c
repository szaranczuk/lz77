#include <lz77.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define FILE_TERMINATOR 1467298742
#define BLOCK_SIZE  (1 << 20)
char buff[BLOCK_SIZE];

int main(int argc, char** argv)
{
    argv[1] = "/home/szaranczuk/lz77-c/build/src/compressed";
    argv[2] = "/home/szaranczuk/lz77-c/build/src/output";
    FILE* input_pf = fopen(argv[1], "r");
    FILE* output_pf = fopen(argv[2], "w");
    if (input_pf == NULL || output_pf == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int l, r;
    l = 0;
    r = 0;
    char *lp = &l;
    char *rp = &r;
    char c;
    while (1)
    {
        for (int i = 0; i < sizeof(int); i++)
        {
            lp[i] = fgetc(input_pf);
        }
        if (l == FILE_TERMINATOR)
        {
            break;
        }
        for (int i = 0; i < sizeof(int); i++)
        {
            rp[i] = fgetc(input_pf);
        }
        c = fgetc(input_pf);
        if (l == 1002 && r == 1004)
        {
            int dupa = 5+5;
        }
        fprintf(output_pf, "%d %d %c\n", l, r, c);
    }
}