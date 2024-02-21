#include "core/game.h"
#include "core/event.h"
#include "core/defines.h"
#include "core/window.h"
#include "core/input.h"

#include "graphics/renderer.h"

#include "managers/scene_manager.h"
#include "managers/resource_manager.h"

#include <glad/gl.h>

// Game struct
/////////////////////////////////////////////////////
struct game_t 
{
  f64 last_frame, delta_time;
};

static game_t game;
/////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////
static void update_game()
{
  // Calculating delta time
  game.delta_time = window_get_time() - game.last_frame;
  game.last_frame = window_get_time();
  
  scene_manager_update(game.delta_time);
}

static void render_game()
{
  renderer_clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
  renderer_begin(scene_manager_get_active_camera());

  scene_manager_render();

  renderer_end();
}
/////////////////////////////////////////////////////

// Game functions
/////////////////////////////////////////////////////
b8 game_init(i32 width, i32 height, const char* title)
{
  // Variables init 
  game.last_frame = 0.0f;
  game.delta_time = 0.0f;

  // Window init 
  if(!window_create(width, height, title))
    return false;

  // Systems init 
  input_init();

  // Renderer init 
  renderer_create();
  
  // Managers init
  resource_manager_init();
  scene_manager_init();

  return true;
}

void game_shutdown()
{
  scene_manager_shutdown();
  resource_manager_shutdown();
  
  renderer_destroy();
  event_shutdown();
  window_destroy();
}

void game_run()
{
  while(!window_should_close())
  {
    update_game();
    render_game();

    input_update();
    window_update();
  }
}
/////////////////////////////////////////////////////
