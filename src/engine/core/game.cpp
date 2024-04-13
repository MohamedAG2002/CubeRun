#include "game.h"
#include "engine/core/window.h"
#include "engine/core/clock.h"
#include "engine/core/event.h"
#include "engine/core/input.h"
#include "editor/editor.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/camera.h"
#include "engine/audio/audio_system.h"

#include <cstdio>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void update(Game& game) {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
    window_set_close(true);
  }

  camera_update(&game.cam);
  camera_move(&game.cam);
}

static void render(Game& game) {
  renderer_begin(game.cam); 
  //editor_begin();

  for(int i = 0; i < 10; i++) {
    render_mesh(game.mesh[i], glm::vec3(i * 10.0f, 0.0f, -5.0f), glm::vec4(1.0f, 0, 0, 1));
  }

  glm::vec2 text_pos = glm::vec2(100.0f, 100.0f);
  render_text(renderer_default_font(), "CUBE RUN", 0.0f, text_pos, glm::vec4(1.0f));

  //editor_end();
  renderer_end();
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool game_init(Game& game) {
  // Systems init  
  ///////////////////////////////////////////////// 
  if(!window_create(800, 600, "Cube Run")) {
    printf("[ERROR]: Window failed to be created\n");
    return false;
  }

  input_cursor_show(false);
  input_init();
  editor_init();

  if(!renderer_create()) {
    printf("[ERROR]: Renderer failed to be created\n");
    return false;
  }

  if(!audio_system_init()) {
    printf("[ERROR]: Audio system failed to be initialized\n");
    return false;
  }
  ///////////////////////////////////////////////// 

  for(int i = 0; i < 10; i++) {
    game.mesh[i] = mesh_create();
  }
  game.cam  = camera_create(glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  return true;
}

void game_shutdown(Game& game) {
  audio_system_shutdown();
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
