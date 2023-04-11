#include <stdlib.h>
#include <lz77.h>
#include <list.h>
#include <suffix_array.h>

int min(int a, int b)
{
    if (a < b) return a;
    return b;
}

int *sa, *reverse_sa, *lcparr;
array_list lcp_list;
char* text;
int pos;
int n;

void initialize_block(const char* _text)
{
    n = strlen(_text);
    strcpy(text, _text);
    int** c;
    sa = suffix_array(text, &c);
    lcparr = lcp_array(c, sa, n);
    free(c);
    reverse_sa = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        reverse_sa[sa[i]] = i;
    }
    lcp_list = initialize_array_list(n);
    for (int i = 0; i < n - 1; i++)
    {
        array_list_push_back(&lcp_list, lcparr[i]);
    }
    pos = n - 1;
}

void cleanup_block()
{
    free(sa);
    free(reverse_sa);
    free(lcparr);
    free(text);
}

lz77_entry compute_next_entry()
{
}
