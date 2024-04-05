#include "game.h"
#include "engine/core/window.h"
#include "engine/core/clock.h"
#include "engine/core/event.h"
#include "engine/core/input.h"

#include <glad/gl.h>

#include <cstdio>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void update(Game& game) {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
    window_set_close(true);
  }

  static bool show = true;
  if(input_key_pressed(KEY_F5)) {
    input_cursor_show(!show);
  }
  
  glm::vec2 mouse_pos = input_mouse_pos();
  printf("%.03f, %.03f\n", mouse_pos.x, mouse_pos.y);
}

static void render(Game& game) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

  window_swap_buffers(); 
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
  ///////////////////////////////////////////////// 
  
  return true;
}

void game_shutdown(Game& game) {
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
