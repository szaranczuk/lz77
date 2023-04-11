/**********************************************************************************
 *         Description: Algorithm for computing LCP array of Suffix Array         *
 *                            Time complexity: O(nlogn)                           *
 *                           Memory complexity: O(nlogn)                          *
 *                             Author: Igor Hanczaruk                             *
 *                               Date: 10.04.2023                                 *
 **********************************************************************************/

#include <stdlib.h>
#include <list.h>
#include <suffix_array.h>

int* lcp_array(int** c, int* p, int n)
{
	int lg = __builtin_clz(1) - __builtin_clz(n);
	if (__builtin_popcount(n) != 1) lg++;
	int* ret = malloc((n - 1) * sizeof(int));
	for (int i = 1; i < n; i++)
	{
		ret[i-1] = lcp(c, p[i-1], p[i], lg);
	}
	return ret;
}

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
