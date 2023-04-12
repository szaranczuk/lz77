#include <lz77.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BLOCK_SIZE  (1 << 20)
#define FILE_TERMINATOR 1467298742
char buff[BLOCK_SIZE];

void writeInt(const int x, FILE* pf)
{
	const char *xp = &x;
	for (int i = 0; i < sizeof(int); i++)
	{
		fprintf(pf, "%c", xp[i]);
	}
}

void read_block(FILE* out)
{
	int n;
	lz77_entry* lz77 = compute_block(buff, &n);
	for (int i = 0; i < n; i++)
	{
		writeInt(lz77[i].l, out);
		writeInt(lz77[i].r, out);
		fprintf(out, "%c", lz77[i].c);
	}
}

int main(int argc, char** argv)
{
	FILE* input_pf = fopen(argv[1], "r");
	FILE* output_pf = fopen(argv[2], "w");
	if (input_pf == NULL || output_pf == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	int bytes_readed;
	while ((bytes_readed = fread(buff, sizeof(char), BLOCK_SIZE, input_pf)) == BLOCK_SIZE)
	{
		read_block(output_pf);
	}
	if (bytes_readed != 0)
	{
		read_block(output_pf);
	}
	writeInt(FILE_TERMINATOR, output_pf);
	fclose(input_pf);
	fclose(output_pf);
	exit(EXIT_SUCCESS);
}