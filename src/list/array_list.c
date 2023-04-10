#include <list.h>
#include <stdlib.h>
#include <stddef.h>

array_list initialize_array_list(size_t max_size)
{
	array_list ret;
	ret.max_size = max_size;
	ret.list = malloc(max_size * sizeof(array_list_node*));
	ret.head = -1;
	ret.tail = -1;
	ret.freeidx = 0;
	return ret;
}

int array_list_push_back(array_list* list, int val)
{
	list->list[list->freeidx].next = -1;
	list->list[list->freeidx].prev = list->tail;
	list->list[list->freeidx].val = val;
	if (list->tail != -1)
	{
		list->list[list->tail].next = list->freeidx;
	}
	else
	{
		list->head = list->freeidx;
	}
	list->tail = list->freeidx++;
	return list->tail;
}

int array_list_push_front(array_list* list, int val)
{
	list->list[list->freeidx].prev = -1;
	list->list[list->freeidx].next = list->head;
	list->list[list->freeidx].val = val;
	if (list->head != -1)
	{
		list->list[list->head].prev = list->freeidx;
	}
	else
	{
		list->tail = list->freeidx;
	}
	list->head = list->freeidx++;
	return list->head;
}

void array_list_erase(array_list* list, int idx)
{
	int next_idx = list->list[idx].next;
	int prev_idx = list->list[idx].prev;
	if (next_idx != -1)
	{
		list->list[next_idx].prev = prev_idx;
	}
	if (prev_idx != -1)
	{
		list->list[prev_idx].next = next_idx;
	}
	if (idx == list->head)
	{
		list->head = next_idx;
	}
	if (idx == list->tail)
	{
		list->tail = prev_idx;
	}
	list->list[idx].next = -1;
	list->list[idx].prev = -1;
}

void cleanup_array_list(array_list* list)
{
	free(list->list);
	list->head = -1;
	list->tail = -1;
	list->max_size = 0;
	list->freeidx = 0;
}