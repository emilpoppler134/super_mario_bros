#ifndef __TILES_H__
#define __TILES_H__

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <time.h>

#include "raylib.h"

#define ROWS 15
#define TILE_SIZE 16
#define LEVEL_COLS 1600
#define CHUNK_COLS 8

typedef enum tile_type_e
{
  // Row 1
  TILE_SKY,
  TILE_GROUND,
  TILE_GRASS_LEFT,
  TILE_GRASS_MIDDLE,
  TILE_GRASS_RIGHT,
  TILE_HILL_LEFT,
  TILE_HILL_MIDDLE_LEFT,
  TILE_HILL_MIDDLE,
  TILE_HILL_MIDDLE_RIGHT,
  TILE_HILL_RIGHT,
  TILE_HILL_TOP,
  // Row 2
  TILE_BRICK,
  TILE_QUE_BLOCK,
  TILE_WARP_PIPE_TOP_LEFT,
  TILE_WARP_PIPE_TOP_RIGHT,
  TILE_WARP_PIPE_BOTTOM_LEFT,
  TILE_WARP_PIPE_BOTTOM_RIGHT,
  TILE_BRICK_NICE,
  TILE_CLOUD_BOTTOM_LEFT,
  TILE_CLOUD_BOTTOM_MIDDLE,
  TILE_CLOUD_BOTTOM_RIGHT,
  // Row 3
  TILE_CLOUD_TOP_LEFT,
  TILE_CLOUD_TOP_MIDDLE,
  TILE_CLOUD_TOP_RIGHT,
  TILE_DOOR_TOP,
  TILE_DOOR_BOTTOM,
  TILE_HOUSE_TOP,
  TILE_HOUSE_MIDDLE,
  TILE_WINDOW_RIGHT,
  TILE_WINDOW_LEFT,
  TILE_FLAG_POLE,
  // Row 4
  TILE_FLAG_LEFT,
  TILE_FLAG_MIDDLE,
  TILE_FLAG_TOP,

  TILE_NUM_TYPES
} tile_type_e;

typedef struct level_t
{
  tile_type_e tilemap[ROWS][LEVEL_COLS];
} level_t;

typedef struct chunk_t
{
  int tiles[ROWS][CHUNK_COLS];
} chunk_t;

typedef struct dynamic_chunk_array
{
  chunk_t* data;
  int count;
  int capacity;
} dynamic_chunk_array;

level_t init_level();
void load_chunk(level_t *level, int highest_tile);
dynamic_chunk_array deserialize_terrain();

dynamic_chunk_array terrain;

#endif
