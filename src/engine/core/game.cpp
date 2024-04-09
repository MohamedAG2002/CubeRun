#include "game.h"
#include "engine/core/window.h"
#include "engine/core/clock.h"
#include "engine/core/event.h"
#include "engine/core/input.h"
#include "editor/editor.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/renderer.h"

#include <cstdio>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void update(Game& game) {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
    window_set_close(true);
  }
}

static void render(Game& game) {
  renderer_begin(); 
  editor_begin();

  render_mesh(game.mesh, glm::vec3(0.0f), glm::vec4(1.0f));

  editor_end();
  renderer_end();
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool game_init(Game& game) {
  // Systems init  
  ///////////////////////////////////////////////// 
  if(!window_create(1280, 720, "Cube Run")) {
    printf("[ERROR]: Window failed to be created\n");
    return false;
  }

  input_init();
  editor_init();

  if(!renderer_create()) {
    printf("[ERROR]: Renderer failed to be created\n");
    return false;
  }
  ///////////////////////////////////////////////// 
 
  game.mesh = mesh_create();

  return true;
}

void game_shutdown(Game& game) {
  renderer_destroy();
  editor_shutdown();
  window_destroy();
}

void game_run(Game& game) {
  while(!window_should_close()) {
    crclock_update();
    
    update(game);
    input_update();
    
    render(game);
  
    window_poll_events();
  }
}
/////////////////////////////////////////////////////////////////////////////////
