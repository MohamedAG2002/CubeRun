#include "core/game.h"
#include "core/event.h"
#include "core/defines.h"
#include "core/window.h"
#include "core/input.h"

#include "graphics/renderer.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"

#include <glad/gl.h>

// Game struct
/////////////////////////////////////////////////////
struct game_t 
{
  f64 last_frame, delta_time;
  mesh_t* cube_mesh;
  
  glm::vec3 target;
  camera cam;
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

  camera_move(game.cam, 5.0f, game.delta_time);
  camera_update(game.cam);
}

static void render_game()
{
  renderer_clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
  renderer_begin(game.cam);

  render_mesh(game.cube_mesh, {1.0f, 0.0f, 0.0f}, {0.3f, 2.0f, 1.0f}, {1.0f, 0.0f, 0.1f, 1.0f});

  renderer_end();
}
/////////////////////////////////////////////////////

// Game functions
/////////////////////////////////////////////////////
b8 game_init(i32 width, i32 height, const char* title)
{
  // Window init 
  if(!window_create(width, height, title))
    return false;

  // Systems init 
  input_init();

  // Renderer init 
  renderer_create();

  // Variables init 
  game.last_frame = 0.0f;
  game.delta_time = 0.0f;
  game.cube_mesh  = mesh_load();
  game.target     = glm::vec3(0.0f, 0.0f, -0.3f);
  game.cam        = camera_create(glm::vec3{0.0f, 0.0f, -3.0f}, &game.target);

  return true;
}

void game_shutdown()
{
  mesh_destroy(game.cube_mesh);

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
