#include "scenes/game_scene.h"
#include "core/defines.h"

// Game scene functions
/////////////////////////////////////////////////
game_scene_t* game_scene_create()
{
  game_scene_t* game = new game_scene_t;

  return game;
}

void game_scene_shutdown(game_scene_t* game)
{
  delete game;
}

void game_scene_update(game_scene_t* game, f64 dt)
{

}

void game_scene_render(game_scene_t* game)
{

}

void game_scene_reset(game_scene_t* game)
{

}
/////////////////////////////////////////////////
