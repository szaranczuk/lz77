#ifndef __LZ77_H
#define __LZ77_H

#include <list.h>

typedef struct lz77_entry
{
	int l;
	int r;
	char c;
} lz77_entry;

lz77_entry compute_entry(int pos);

#endif