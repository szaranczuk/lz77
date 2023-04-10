#define __EXTERN

#include <list.h>
#include <random>
#include <algorithm>
#include <cassert>
#include <deque>


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

int main(int argc, char** argv)
{
	gen.seed(atoi(argv[1]));
	int q = atoi(argv[2]);
	int max_size = atoi(argv[3]);
	array_list list = initialize_array_list(max_size);
	std::vector<int> list_to_idx(max_size);
	std::deque<std::pair<int, int>> cpp_deque;
	while (q--)
	{
		if (list.freeidx < max_size && list.freeidx > 0)
		{
			if (getrandom(0, 1))
			{
				int val = getrandom(1, 1e6);
				if (getrandom(0, 1))
				{
					int idx = array_list_push_front(&list, val);
					cpp_deque.push_front({val, idx});
				}
				else
				{
					int idx = array_list_push_back(&list, val);
					cpp_deque.push_back({val, idx});
				}
			}
			else
			{
				int idx = getrandom(0, list.freeidx - 1);
				array_list_erase(&list, idx);
				for (auto it = cpp_deque.begin(); it != cpp_deque.end(); ++it)
				{
					if (it->second == idx)
					{
						cpp_deque.erase(it);
						break;
					}
				}
			}
		}
		else if (list.freeidx == max_size)
		{
			int idx = getrandom(0, list.freeidx - 1);
			array_list_erase(&list, idx);
			for (auto it = cpp_deque.begin(); it != cpp_deque.end(); ++it)
			{
				if (it->second == idx)
				{
					cpp_deque.erase(it);
					break;
				}
			}
		}
		else
		{
			int val = getrandom(1, 1e6);
			if (getrandom(0, 1))
			{
				int idx = array_list_push_front(&list, val);
				cpp_deque.push_front({val, idx});
			}
			else
			{
				int idx = array_list_push_back(&list, val);
				cpp_deque.push_back({val, idx});
			}
		}
	}
	int list_item = list.head;
	for (auto p : cpp_deque)
	{
		assert(p.first == list.list[list_item].val);
		list_item = list.list[list_item].next;
	}
	cleanup_array_list(&list);
}