#include <suffix_array.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int** c;
    int* p = suffix_array(argv[1], &c);
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", p[i] + 1);
    }
    printf("\n");
    free(c);
    free(p);
}