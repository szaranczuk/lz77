#ifndef _SUFFIX_ARRAY
#define _SUFFIX_ARRAY

#define ALPHABET 256

#ifndef __EXTERN
int* suffix_array(const char* input_string, int*** c);
int* lcp_array(int** c, int* p,int n);
int lcp(int** c, int a, int b, int n);
#endif

#endif