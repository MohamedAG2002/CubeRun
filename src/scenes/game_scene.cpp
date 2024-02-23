#include "scenes/game_scene.h"
#include "core/defines.h"
#include "core/event.h"
#include "core/input.h"
#include "graphics/camera.h"
#include "entities/player.h"
#include "entities/platform.h"

#include <glm/vec3.hpp>

// Game scene functions
/////////////////////////////////////////////////
game_scene_t* game_scene_create()
{
  game_scene_t* game = new game_scene_t;

  // Camer init 
  glm::vec3 target(0.0f, 0.0f, -0.3f);
  game->cam = camera_create(glm::vec3{1.0f, 0.0f, 3.0f}, &target);
  
  // Entities init 
  game->player = player_create(glm::vec3{1.0f, 0.5f, 1.0f});
  game->platforms = platforms_create(glm::vec3(1.0f, 0.0f, -100.0f));

  return game;
}

void game_scene_shutdown(game_scene_t* game)
{
  platforms_destroy(game->platforms);

  delete game;
}

void game_scene_update(game_scene_t* game, f64 dt)
{
  camera_move(game->cam, 5.0f, dt);
  camera_update(game->cam);

  player_update(game->player, dt);
  platforms_update(game->platforms, dt);

  if(input_key_pressed(KEY_SPACE))
    event_dispatch(EVENT_AUDIO_PLAYED, event_desc_t{.sound_id = "Player_Death"});
}

void game_scene_render(game_scene_t* game)
{
  player_render(game->player); 
  platforms_render(game->platforms);
}

void game_scene_reset(game_scene_t* game)
{
  player_reset(game->player); 
  platforms_reset(game->platforms);
}
/////////////////////////////////////////////////
