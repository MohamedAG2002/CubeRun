#include "game/game.h"
#include "engine/core/window.h"
#include "engine/core/clock.h"
#include "engine/core/event.h"
#include "engine/core/input.h"
#include "engine/graphics/renderer.h"
#include "engine/audio/audio_system.h"
#include "game/scenes/scene_manager.h"

#include <cstdio>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void update() {
  if(input_key_pressed(KEY_ESCAPE)) {
    event_dispatch(EVENT_GAME_QUIT, EventDesc{});
  }

  scenes_update();
}

static void render() {
  scenes_render();
}

static bool quit_game_callback(const EventType type, const EventDesc& desc) {
  if(type != EVENT_GAME_QUIT) {
    return false;
  }

  window_set_close(true);
  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool game_init() {
  // Systems/managers init  
  ///////////////////////////////////////////////// 
  if(!window_create(1280, 720, "Cube Run")) {
    printf("[ERROR]: Window failed to be created\n");
    return false;
  }

  input_cursor_show(false);
  input_init();

  if(!renderer_create()) {
    printf("[ERROR]: Renderer failed to be created\n");
    return false;
  }

  if(!audio_system_init()) {
    printf("[ERROR]: Audio system failed to be initialized\n");
    return false;
  }

  scenes_create();
  ///////////////////////////////////////////////// 
 
  // Listen to events
  ///////////////////////////////////////////////// 
  event_listen(EVENT_GAME_QUIT, quit_game_callback);
  ///////////////////////////////////////////////// 

  return true;
}

void game_shutdown() {
  scenes_destroy();

  audio_system_shutdown();

  renderer_destroy();
  window_destroy();
}

void game_run() {
  while(!window_should_close()) {
    crclock_update();
    update();
    input_update();
    
    render();
  
    window_poll_events();
  }
}
/////////////////////////////////////////////////////////////////////////////////
