/*********************************************************************************************************
 *  Description: Algorithm for computing LPF array of ASCII string using Suffix Array and its LCP Aray   *
 *                                      Time complexity: O(n)                                            *
 *                                     Memory complexity: O(n)                                           *
 *                                     Author: Igor Hanczaruk                                            *
 *                                        Date: 10.04.2023                                               *
 *********************************************************************************************************/

#include <suffix_array.h>
#include <stdlib.h>
#include <list.h>
#include <string.h>
#include <utils.h>

void compute_lpf_array(array_list *lcp_list, int* sa, int *reverse_sa, const char *text, int **lpf_out, int **lpf_come_from_out)
{
	int n = strlen(text);
	(*lpf_out) = (int *)malloc(n * sizeof(int));
	(*lpf_come_from_out) = (int *)malloc(n * sizeof(int));
	int* lpf = *lpf_out;
	int* lpf_come_from = *lpf_come_from_out;
	for (int i = n - 1; i >= 0; i--)
	{
		int sa_idx = reverse_sa[i];
		if (sa_idx == 0)
		{
			int match_idx = lcp_list->head;
			array_list_node match = lcp_list->list[match_idx];
			lpf[i] = match.val;
			lpf_come_from[i] = reverse_sa[match_idx+1];
			lcp_list->list[match_idx].val = 0;
		}
		else
		{
			int next = lcp_list->list[sa_idx - 1].next;
			int next_val = next == -1 ? -1 : lcp_list->list[next].val;
			int prev = lcp_list->list[sa_idx - 1].prev;
			int prev_val = lcp_list->list[sa_idx-1].val;
			if (next_val > prev_val)
			{
				lpf[i] = next_val;
				lpf_come_from[i] = reverse_sa[next+1];
			}
			else
			{
				lpf[i] = prev_val;
				lpf_come_from[i] = reverse_sa[prev+1];
			}
			if (next != -1)
			{
				lcp_list->list[next].val = min(lcp_list->list[next].val, lcp_list->list[sa_idx - 1].val);
			}
			array_list_erase(lcp_list, sa_idx - 1);
		}
	}
}
