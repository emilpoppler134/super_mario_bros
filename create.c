#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 16
#define COLS 8
#define LEVEL_FILE_PATH "./resources/terrain/plattform3"

typedef struct chunk_t
{
  int tiles[ROWS][COLS];
} chunk_t;

void SerializeLevel(const char *path, chunk_t *chunk)
{
	FILE *file = fopen(path, "wb");
	if (!file)
	{
		perror("Failed to open level file");
		exit(1);
	}

	if (fwrite(chunk, sizeof(chunk_t), 1, file) != 1)
	{
		perror("Failed to write level data");
		fclose(file);
		exit(1);
	}

	fclose(file);
}

void InitializeLevel(chunk_t *chunk)
{
	int tiles[ROWS][COLS] = {
    {0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  12,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  11,  11,  11,  11,  11,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {11,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0},
    {1,  1,  1,  1,  1,  1,  1,  1},
    {1,  1,  1,  1,  1,  1,  1,  1}
  };

	memcpy(chunk->tiles, tiles, sizeof(int) * ROWS * COLS);
}

int main()
{
	chunk_t chunk;
	InitializeLevel(&chunk);
	SerializeLevel(LEVEL_FILE_PATH, &chunk);

	return 0;
}
