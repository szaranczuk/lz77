#ifndef __LZ77_H
#define __LZ77_H
#define NOT_FOUND 3700009
#include <list.h>

typedef struct lz77_entry
{
	int l;
	int r;
	char c;
} lz77_entry;

void initialize_block(const unsigned char* _text);
lz77_entry* compute_block(const unsigned char* _text, int* no_entries);
void cleanup_block();

#endif
