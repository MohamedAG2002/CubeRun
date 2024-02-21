#pragma once

#include "core/defines.h"

// Game scene type
/////////////////////////////////////////////////
struct game_scene_t
{

};
/////////////////////////////////////////////////

// Game scene functions
/////////////////////////////////////////////////
game_scene_t* game_scene_create();
void game_scene_shutdown(game_scene_t* game);
void game_scene_update(game_scene_t* game, f64 dt);
void game_scene_render(game_scene_t* game);
void game_scene_reset(game_scene_t* game);
/////////////////////////////////////////////////
