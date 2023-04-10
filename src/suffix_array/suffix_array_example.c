#include <suffix_array.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int** c;
    char example_string1[] = "banana";
    int* p = suffix_array(example_string1, &c);
    int n = strlen(example_string1);
    printf("Suffix array of \"banana\":\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n\nIntermediate equivalence classes of \"banana\":\n");
    int lg = __builtin_clz(1) - __builtin_clz(n);
    if (__builtin_popcount(n) != 1) lg++;
    for (int i = 0; i <= lg; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    free(c);
    free(p);
    printf("\n\n");

    char example_string2[] = "abaa";
    p = suffix_array(example_string2, &c);
    n = strlen(example_string2);
    printf("Suffix array of \"abaa\":\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n\nIntermediate equivalence classes of \"abaa\":\n");
    lg = __builtin_clz(1) - __builtin_clz(n);
    if (__builtin_popcount(n) != 1) lg++;
    for (int i = 0; i <= lg; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    free(c);
    free(p);
}