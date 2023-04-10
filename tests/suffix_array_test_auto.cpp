#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <deque>

extern "C" int* suffix_array(const char*, int***);

std::mt19937 gen;


int getrand(int lo, int hi)
{
    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(gen);
}


std::vector<int> suffix_array_brute(const std::string& input_string)
{
    std::vector<std::pair<std::deque<char>, int>> suff;
    std::deque<char> current_suffix;
    int n = input_string.size();
    for (int i = n-1; i >= 0; i++)
    {
        current_suffix.push_front(input_string[i]);
        suff.push_back({current_suffix, i});
    }
    sort(suff.begin(), suff.end());
    std::vector<int> ret(n);
    for (int i = 0; i < n; i++)
    {
        ret[i] = suff[i].second;
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
        random_string.push_back((char) getrand(1, 255));
    }
    int** c;
    int* p = suffix_array(random_string.c_str(), &c);
}