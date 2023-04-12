#include <lz77.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#define START_OF_FILE 424910213
//#define __DEBUG

int block_terminator, file_terminator, block_size;
char* buff;

int readInt(FILE* fp)
{
    int x;
    char* xp = (char* )&x;
    for (int i = 0; i < sizeof(int); i++)
    {
        xp[i] = fgetc(fp);
    }
    return x;
}

int main(int argc, char** argv)
{
    FILE* input_pf = fopen(argv[1], "r");
    FILE* output_pf = fopen(argv[2], "w");
    if (input_pf == NULL || output_pf == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int greeting_message = readInt(input_pf);
    if (greeting_message != START_OF_FILE)
    {
        fprintf(stderr, "%s is not a valid lz77 file\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    block_terminator = readInt(input_pf);
    file_terminator = readInt(input_pf);
    block_size = readInt(input_pf);
    buff = malloc(sizeof(char) * (block_size + 1));
    buff[block_size] = '\0';
    #ifdef __DEBUG
    fprintf(output_pf, "%d\n%d\n%d\n", greeting_message, block_terminator, file_terminator);
    #endif
    int l, r;
    char c;
    int no_blocks = 0;
    int pos = 0;
    while ((l = readInt(input_pf)) != file_terminator)
    {
        if (l == block_terminator)
        {
            no_blocks++;
            pos = 0;
            #ifdef __DEBUG
            fprintf(output_pf, "%d\n", block_terminator);
            #else
            fprintf(output_pf, "%s", buff);
            #endif
            continue;
        }
        r = readInt(input_pf);
        c = fgetc(input_pf);
        #ifdef __DEBUG
        fprintf(output_pf, "%d %d %c\n", l, r, c);
        #endif
        if (l != -1)
        {
            for (int i = l; i < r; i++)
            {
                buff[pos++] = buff[i];
            }
        }
        buff[pos++] = c;
    }
    #ifdef __DEBUG
    fprintf(output_pf, "%d\n", file_terminator);
    #endif
    printf("Successfully decomposed %d block(s) of data from %s\n", no_blocks, argv[1]);
}