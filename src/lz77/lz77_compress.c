#include <lz77.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#define BLOCK_SIZE  (1 << 20)
#define FILE_TERMINATOR 1000075u
#define BLOCK_TERMINATOR 1000099u
#define START_OF_FILE 7999999u
#define ENTRY_SIZE 7
char buff[BLOCK_SIZE];
int entry_counter = 0;

void writeInt(const unsigned int x, FILE* pf)
{
	const char *xp = &x;
	for (int i = 0; i < 3; i++)
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
		entry_counter++;
		writeInt((unsigned int) lz77[i].l, out);
		writeInt((unsigned int) lz77[i].r, out);
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
	clock_t start_time = clock();
	writeInt(START_OF_FILE, output_pf);
	writeInt(BLOCK_TERMINATOR, output_pf);
	writeInt(FILE_TERMINATOR, output_pf);
	writeInt(BLOCK_SIZE, output_pf);
	int bytes_readed;
	int no_blocks = 0;
	while ((bytes_readed = fread(buff, sizeof(char), BLOCK_SIZE, input_pf)) == BLOCK_SIZE)
	{
		read_block(output_pf);
		writeInt(BLOCK_TERMINATOR, output_pf);
		no_blocks++;
	}
	if (bytes_readed != 0)
	{
		read_block(output_pf);
		writeInt(BLOCK_TERMINATOR, output_pf);
		no_blocks++;
	}
	writeInt(FILE_TERMINATOR, output_pf);
	fclose(input_pf);
	fclose(output_pf);
	clock_t end_time = clock();
    printf("Successfully compressed %d block(s) of data from %s\n", no_blocks, argv[1]);
	float size_before = (no_blocks - 1) * BLOCK_SIZE;
	if (bytes_readed == 0) size_before += BLOCK_SIZE;
	else size_before += bytes_readed;
	size_before /= 1024.0;
	float size_after = entry_counter * ENTRY_SIZE;
	size_after /= 1024.0;
	float time_elapsed = (end_time - start_time)/((float) CLOCKS_PER_SEC);
	printf("Size before compression: %0.2f [KiB]\nSize after compression: %.2f [KiB]\nTime elapsed: %.3f [s]\n", size_before, size_after, time_elapsed);
	exit(EXIT_SUCCESS);
}