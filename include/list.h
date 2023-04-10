#ifndef __LIST_H
#define __LIST_H

#include <stdlib.h>

typedef struct array_list_node
{
	int next;
	int prev;
	int val;
} array_list_node;

typedef struct array_list
{
	array_list_node* list;
	int head;
	int tail;
	int freeidx;
	int max_size;
} array_list;

#ifndef __EXTERN

array_list initialize_array_list(size_t max_size);
int array_list_push_back(array_list* list, int val);
int array_list_push_front(array_list* list, int val);
void array_list_erase(array_list* list, int idx);
void cleanup_array_list(array_list* list);

#endif
#endif