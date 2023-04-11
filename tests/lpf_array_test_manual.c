#include <suffix_array.h>
#include <stdlib.h>
#include <string.h>
#include <list.h>
#include <assert.h>

int* brute_lpf(const char* text)
{
	int n = strlen(text);
	int* lpf = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int ans = 0;
			while (i + ans < n && text[i + ans] == text[j + ans]) ans++;
			lpf[i] = max(lpf[i], ans);
		}
	}
	return lpf;
}

int main(int argc, char** argv)
{
	int n = strlen(argv[1]);
	int** c;
	int* sa = suffix_array(argv[1], &c);
	int* reverse_sa = (int*) malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) reverse_sa[sa[i]] = i;
	int* lcp = lcp_array(c, sa, n);
	array_list lcp_list = initialize_array_list(n);
	for (int i = 0; i < n; i++) array_list_push_back(&lcp_list, lcp[i]);
	int* result;
	int* dummy;
	compute_lpf_array(&lcp_list, sa, reverse_sa, argv[1], &result, &dummy);
	int* answer = brute_lpf(argv[1]);
	for (int i = 0; i < n; i++)
	{
		assert(result[i] == answer[i]);
	}
	free(c);
	free(sa);
	free(reverse_sa);
	free(lcp);
	free(result);
	free(answer);
	free(dummy);
	cleanup_array_list(&lcp_list);
}