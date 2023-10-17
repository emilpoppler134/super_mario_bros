#include <stdio.h>

#include "level.h"
#include "raylib.h"

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screen_width = 1200;
  const int screen_height = 800;

  InitWindow(screen_width, screen_height, "Super Mario");

  Texture2D tileset = LoadTexture("./resources/tileset.png");
  tileset.width = 160;
  tileset.height = 160;

  while(!WindowShouldClose())
  {
    // Input
    //--------------------------------------------------------------------------------------

    // Update
    //--------------------------------------------------------------------------------------

    // Draw
    //--------------------------------------------------------------------------------------
    BeginDrawing();
      
    EndDrawing();
  }

  return 0;
}