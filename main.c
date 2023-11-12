#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#include "level.h"

#define GRAVITY 0.6

typedef struct window_t {
  int current_width;
  int current_height;
} window_t;

typedef struct player_t
{
  Vector2 position;
  Vector2 velocity;
  int hp;
} player_t;

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------

  window_t window = {
    .current_width = 1440,
    .current_height = 900
  };

  InitWindow(window.current_width, window.current_height, "My Window");

  ToggleFullscreen();
  SetTargetFPS(60);
  //SetExitKey(KEY_X);

  RenderTexture2D canvas = LoadRenderTexture(256, 240);

  Texture2D tileset = LoadTexture("./resources/tileset.png");
  tileset.width = 160;
  tileset.height = 160;

  level_t level = init_level();

  int start = 8;
  float offset = 0.0f;
  float playerSpeed = -1.4f;

  player_t player = {
    .velocity = (Vector2){0, 0},
    .position = (Vector2){start * TILE_SIZE, 240 - 64},
    .hp = 100
  };

  int highest_tile = 3 * CHUNK_COLS;

  bool go_right = false;
  bool go_left = false;

  while(!WindowShouldClose())
  {
    if (IsKeyUp(KEY_D))
    {
      go_right = false;
    }
    if (IsKeyUp(KEY_A))
    {
      go_left = false;
    }

    // Input
    //--------------------------------------------------------------------------------------
    player.velocity.x = 0;
    
    if (IsKeyDown(KEY_D))
    {
      player.velocity.x = 1;
      
      int tile_x = floor(player.position.x / TILE_SIZE);
      if (tile_x > 10)
      {
        start++;
        offset = 0;
        go_right = true;
        player.position.x -= 10;

        if (start + 3 + CHUNK_COLS > highest_tile)
        {
          if (highest_tile % CHUNK_COLS == 0)
          {
            int current_chunk = floor(highest_tile / CHUNK_COLS);
            load_chunk(&level, current_chunk + 1);
          }
          highest_tile = start + 3 + CHUNK_COLS;
        }
      }
    }

    if (IsKeyDown(KEY_A))
    {
      player.velocity.x = -1;

      int tile_x = floor(player.position.x / TILE_SIZE);
      if (tile_x < 4)
      {
        start--;
        offset = 0;
        go_left = true;
        player.position.x += 10;
      }
    }
    
    if (IsKeyPressed(KEY_SPACE) && player.position.y + 32 >= 240 - TILE_SIZE * 2) {
      player.velocity.y = -10;
    }

    // Update
    //--------------------------------------------------------------------------------------

    if (go_right)
    {
      offset += playerSpeed;
    }
    if (go_left)
    {
      offset -= playerSpeed;
    }

    // Apply gravity to vertical velocity
    player.velocity.y += GRAVITY;

    // Update player position
    player.position.x += player.velocity.x;
    player.position.y += player.velocity.y;

    // Ground collision
    if (player.position.y + 32 >= 240 - TILE_SIZE * 2) {
      player.position.y = 240 - 32 - TILE_SIZE * 2;  // Reset to ground level
      player.velocity.y = 0;  // Stop downward movement
    }

    // Draw
    //--------------------------------------------------------------------------------------
    BeginTextureMode(canvas);
      ClearBackground((Color){105, 147, 245, 255});
      
      // Draw the tilemap
      for (int y = 0; y < ROWS; y++) {
        int tile_count = 16;
        int end = start + tile_count;

        int screen_x = 0;

        for (int x = start; x < end + 1; x++) {
          int tile = level.tilemap[y][x];

          float dest_x = screen_x * TILE_SIZE + offset;

          Rectangle dest_rect = {dest_x, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
          Rectangle source_rect = {(tile % (tileset.width / TILE_SIZE)) * TILE_SIZE, (tile / (tileset.width / TILE_SIZE)) * TILE_SIZE, TILE_SIZE, TILE_SIZE };

          DrawTexturePro(tileset, source_rect, dest_rect, Vector2Zero(), 0.0f, WHITE);
          screen_x++;
        }
      }

      DrawRectangle(player.position.x, player.position.y, 16, 32, WHITE);
    EndTextureMode();

    BeginDrawing();
      ClearBackground(BLACK);
      DrawTexturePro(canvas.texture, (Rectangle) {0, 0, 256, -240}, (Rectangle) {0, 0,  window.current_width, window.current_height}, (Vector2) {0.0f, 0.0f}, 0.0f, WHITE);
    EndDrawing();
  }

  return 0;
}
