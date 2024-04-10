#pragma once

#include "engine/graphics/mesh.h"
#include "engine/graphics/camera.h"

// Game
/////////////////////////////////////////////////////////////////////////////////
struct Game {
  Camera cam;
  Mesh* mesh[10];  
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool game_init(Game& game);
void game_shutdown(Game& game);
void game_run(Game& game);
/////////////////////////////////////////////////////////////////////////////////
