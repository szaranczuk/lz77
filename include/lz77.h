#ifndef __LZ77_H
#define __LZ77_H

#include <list.h>

typedef struct lz77_entry
{
	int l;
	int r;
	char c;
} lz77_entry;

void initialize_block(const char* _text);
lz77_entry* compute_block(const char* _text, int* no_entries);
void cleanup_block();

#endif
