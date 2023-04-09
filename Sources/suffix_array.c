/**********************************************************************************
 *       Description: Algorithm for computing suffix array of ASCII string        *
 *                            Time complexity: O(nlogn)                           *
 *      Memory complexity: O(n) + O(nlogn) for saving intermediate eq. classes    *
 *                             Author: Igor Hanczaruk                             *
 *                               Date: 08.04.2023                                 *
 **********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <suffix_array.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a > b) return a;
    return b;
}

//Technically, this algorithm sorts cyclic shifts of a string, but it can be easily used to compute suffix array, just by appending a terminator character,
//which is less than any other character in string, to the end of string 

int* suffix_array(char* input_string, int*** c)
{
    int n = strlen(input_string);
    n++; // I will use \0 as string terminator 
    int lg = __builtin_clz(1) - __builtin_clz(n);
    if (__builtin_popcount(n) != 1) lg++; //lg should be equal ceil(log2(n))
    *c = (int**) malloc((lg + 1) * sizeof(int*));
    for (int i = 0; i <= lg; i++)
    {
        (*c)[i] = (int *) malloc(n * sizeof(int));
    }
    int classes = 1;
    int* p = (int *) malloc(n * sizeof(int));
    int* pn = (int *) malloc(n * sizeof(int));
    int* cn = (int *) malloc(n * sizeof(int));
    int cnt_size = max(n, ALPHABET);
    int* cnt = (int *) calloc(cnt_size, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        cnt[input_string[i]]++;
    }
    for (int i = 1; i < ALPHABET; i++)
    {
        cnt[i] += cnt[i-1];
    }
    for (int i = 0; i < n; i++)
    {
        p[--cnt[input_string[i]]] = i;
    }
    (*c)[0][p[0]] = 0;
    for (int i = 1; i < n; i++)
    {
        if (input_string[p[i]] != input_string[p[i-1]])
        {
            classes++;
        }
        (*c)[0][p[i]] = classes - 1;
    }
    for (int h = 0; h < lg; h++)
    {
        for (int i = 0; i < cnt_size; i++)
        {
            cnt[i] = 0;
        }
        for (int i = 0; i < n; i++) 
        {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        for (int i = 0; i < n; i++)
        {
            cnt[(*c)[h][pn[i]]]++;
        }
        for (int i = 1; i < cnt_size; i++)
        {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n-1; i >= 0; i--)
        {
            p[--cnt[(*c)[h][pn[i]]]] = pn[i];
        }
        classes = 1;
        cn[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            int idx1 = p[i] + (1 << h);
            if (idx1 >= n) idx1 -= n;
            int idx2 = p[i] + (1 << h) - 1;
            if (idx2 >= n) idx2 -= n;
            if ((*c)[h][p[i]] != (*c)[h][p[i-1]] || (*c)[h][idx1] != (*c)[h][idx2])
            {
                classes++;
            }
            cn[p[i]] = classes - 1;
        }
        int* tmp = cn;
        cn = (*c)[h+1];
        (*c)[h+1] = tmp;
    }
    int* ret = malloc((n-1) * sizeof(int));
    for (int i = 1; i < n; i++)
    {
        ret[i-1] = p[i];
    }
    free(cnt);
    free(p);
    return ret;
}