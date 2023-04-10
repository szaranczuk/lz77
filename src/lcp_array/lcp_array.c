#include <stdlib.h>
#include <list.h>
#include <lcp_array.h>

int* lcp_array(int** c, int* p,int n);

int lcp(int** c, int a, int b, int lg)
{
	int ret = 0;
	for (int h = lg; h >= 0; h--)
	{
		if (c[h][a] == c[h][b])
		{
			ret |= (1 << h);
			a += (1 << h);
			b += (1 << h);
		}
	}
	return ret;
}
