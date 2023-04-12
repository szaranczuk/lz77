#ifndef _SUFFIX_ARRAY
#define _SUFFIX_ARRAY

#include <list.h>

#define ALPHABET 256

#ifndef __EXTERN
int* suffix_array(const unsigned char* input_string, int*** c);
int* lcp_array(int** c, int* p,int n);
void compute_lpf_array(array_list *lcp_list, int* sa, int *reverse_sa, const unsigned char *text, int **lpf_out, int **lpf_come_from_out);
#endif

#endif