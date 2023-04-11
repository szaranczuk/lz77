#define __EXTERN
#include <suffix_array.h>
#include <list.h>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <set>
#include <deque>
#include <cassert>

extern "C" int* suffix_array(const char* input_string, int*** c);
extern "C" int* lcp_array(int** c, int* p,int n);
extern "C" void compute_lpf_array(array_list *lcp_list, int* sa, int *reverse_sa, const char *text, int **lpf_out, int **lpf_come_from_out);
extern "C" array_list initialize_array_list(size_t max_size);
extern "C" int array_list_push_back(array_list* list, int val);
extern "C" int array_list_push_front(array_list* list, int val);
extern "C" void array_list_erase(array_list* list, int idx);
extern "C" void cleanup_array_list(array_list* list);

std::mt19937 gen;

int getrandom(int lo, int hi)
{
	std::uniform_int_distribution<int> dist(lo, hi);
	return dist(gen);
}

std::vector<int> brute_lpf(const std::string& text)
{
	int n = text.size();
	std::vector<int> lpf(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int ans = 0;
			while (i + ans < n && text[i + ans] == text[j + ans]) ans++;
			lpf[i] = std::max(lpf[i], ans);
		}
	}
	return lpf;
}

int main(int argc, char** argv)
{
	gen.seed(atoi(argv[1]));
	int n = atoi(argv[2]);
	std::string random_text;
	for (int i = 0; i < n; i++)
	{
		random_text.push_back(getrandom(1, 127));
	}
	int** c;
	int* sa = suffix_array(random_text.c_str(), &c);
	int* reverse_sa = (int*) malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) reverse_sa[sa[i]] = i;
	int* lcp = lcp_array(c, sa, n);
	array_list lcp_list = initialize_array_list(n);
	for (int i = 0; i < n-1; i++) array_list_push_back(&lcp_list, lcp[i]);
	int* result;
	int* dummy;
	compute_lpf_array(&lcp_list, sa, reverse_sa, random_text.c_str(), &result, &dummy);
	cleanup_array_list(&lcp_list);
	std::vector<int> answer = brute_lpf(random_text);
	for (int i = 0; i < n; i++)
	{
		assert(result[i] == answer[i]);
	}
	free(c);
	free(sa);
	free(reverse_sa);
	free(result);
	free(dummy);
	free(lcp);
}