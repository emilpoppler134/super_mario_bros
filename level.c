#include "level.h"

dynamic_chunk_array init_chunk_array()
{
  dynamic_chunk_array arr;
  arr.data = (chunk_t*)malloc(sizeof(chunk_t));
  arr.count = 0;
  arr.capacity = 1;
  return arr;
}

void push(dynamic_chunk_array *arr, chunk_t item)
{
  if (arr->count == arr->capacity)
  {
    arr->capacity++;
    arr->data = (chunk_t*)realloc(arr->data, arr->capacity * sizeof(chunk_t));
  }
  arr->data[arr->count] = item;
  arr->count++;
}

dynamic_chunk_array deserialize_terrain()
{
  dynamic_chunk_array terrain = init_chunk_array();

  DIR *directory;
  struct dirent *entry;

  // Open the directory
  directory = opendir("./resources/terrain");

  if (directory == NULL) {
    perror("Error opening directory");
    exit(1);
  }

  // Read each entry in the directory
  while ((entry = readdir(directory)) != NULL)
  {
    if (entry->d_type == DT_REG) // Check if it's a regular file
    {
      chunk_t chunk;

      FILE *file = fopen(TextFormat("./resources/terrain/%s", entry->d_name), "rb");
      if (!file)
      {
        perror("Failed to open level file");
        exit(1);
      }

      if (fread(&chunk, sizeof(chunk_t), 1, file) != 1)
      {
        perror("Failed to read level data");
        fclose(file);
        exit(1);
      }

      push(&terrain, chunk);

      fclose(file);
    }
  }

  // Close the directory
  closedir(directory);

  return terrain;
}

level_t init_level()
{
  level_t level;

  for(int i = 1; i <= 3; i++)
  {
    int start = i * CHUNK_COLS;
    int end = start + CHUNK_COLS;
    
    for(int y = start; y < end; y++)
    {
      for(int x = 0; x < ROWS; x++)
      {
        level.tilemap[x][y] = x > 12 ? TILE_GROUND : TILE_SKY; 
      }
    }
  }

  terrain = deserialize_terrain();
  srand(time(NULL));

  return level;
}

void load_chunk(level_t *level, int current_chunk)
{ 
  int random_index = rand() % terrain.count;

  int start = current_chunk * CHUNK_COLS;
  int end = start + CHUNK_COLS;
    
  for(int x = start; x < end; x++)
  {
    for(int y = 0; y < ROWS; y++)
    {
      level->tilemap[y][x] = terrain.data[random_index].tiles[y][x % CHUNK_COLS];
    } 
  }
}

