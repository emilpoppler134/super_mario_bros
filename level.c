#include "level.h"

level_t init_level()
{
  level_t level = {.tilemap = 0};

  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < LEVEL_COLS; j++) {
      if (i > 12) {
        level.tilemap[i][j] = TILE_GROUND;
        if (j % 16 == 0)
        {
          level.tilemap[i][j] = TILE_BRICK;
        }
      } else {
        level.tilemap[i][j] = TILE_SKY;
      }
    }
  }

  return level;
}