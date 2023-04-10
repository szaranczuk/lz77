#define __EXTERN
#include <lcp_array.h>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <deque>
#include <cassert>

extern "C" int* suffix_array(const char*, int***);
extern "C" int* lcp_array(int** c, int* p,int n);

std::mt19937 gen;


int getrand(int lo, int hi)
{
    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(gen);
}


std::vector<int> lcp_array_brute(const std::string& input_string)
{
    int** c;
    int* sa = suffix_array(input_string.c_str(), &c);
    int n = input_string.size();
    std::vector<int> ret(n-1);
    for (int i = 1; i < n; i++)
    {
        int a = sa[i-1];
        int b = sa[i];
        while (a < n && b < n && input_string[a] == input_string[b])
        {
            a++;
            b++;
            ret[i-1]++;
        }
    }
    return ret;
}


int main(int argc, char** argv)
{
    gen.seed(atoi(argv[1]));
    int n = atoi(argv[2]);
    std::string random_string;
    for (int i = 0; i < n; i++)
    {
        random_string.push_back(getrand(1, 127));
    }
    int** c;
    int* sa = suffix_array(random_string.c_str(), &c);
    int* result = lcp_array(c, sa, n);
    std::vector<int> answer = lcp_array_brute(random_string);
    for (int i = 0; i < n-1; i++)
    {
        assert(result[i] == answer[i]);
    }
}