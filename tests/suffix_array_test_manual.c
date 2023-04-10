#include <stdlib.h> 
#include <assert.h>
#include <string.h>
#include <suffix_array.h>

int main(int argc, char** argv)
{
    int** c;
    int* p = suffix_array(argv[1], &c);
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        assert(p[i] == atoi(argv[i + 2]));
    }
}