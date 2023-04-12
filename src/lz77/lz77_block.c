#include <stdlib.h>
#include <lz77.h>
#include <list.h>
#include <suffix_array.h>
#include <utils.h>
#include <string.h>


int *sa, *reverse_sa, *lcparr, *lpf, *lpf_come_from;
array_list lcp_list;
unsigned char* text;
int pos;
int n;

void initialize_block(const unsigned char* _text)
{
    n = strlen(_text);
    text = malloc(sizeof(unsigned char) * (n + 1));
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
    compute_lpf_array(&lcp_list, sa, reverse_sa, text, &lpf, &lpf_come_from);
}

lz77_entry* compute_block(const unsigned char* _text, int* no_entries)
{
    initialize_block(_text);
    *no_entries = 0;
    int it = 0;
    while (it < n)
    {
        (*no_entries)++;
        it += lpf[it] + 1;
    }
    lz77_entry* ret = (lz77_entry*) malloc((*no_entries) * sizeof(lz77_entry));
    it = 0;
    int idx = 0;
    while (it < n)
    {
        if (lpf[it] == 0)
        {
            ret[idx].l = NOT_FOUND;
            ret[idx].r = NOT_FOUND;
            ret[idx].c = text[it];
        }
        else
        {
            ret[idx].l = lpf_come_from[it];
            ret[idx].r = lpf_come_from[it] + lpf[it];
            it += lpf[it];
            if (it < n)
            {
                ret[idx].c = text[it];
            }
            else
            {
                ret[idx].c = -1;
            }
        }
        it++;
        idx++;
    }
    cleanup_block();
    return ret;
}

void cleanup_block()
{
    free(sa);
    free(reverse_sa);
    free(lcparr);
    free(text);
    free(lpf);
    free(lpf_come_from);
    cleanup_array_list(&lcp_list);
}