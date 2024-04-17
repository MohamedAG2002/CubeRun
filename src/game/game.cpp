#include "game/game.h"
#include "engine/core/window.h"
#include "engine/core/clock.h"
#include "engine/core/event.h"
#include "engine/core/input.h"
#include "editor/editor.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/renderer2d.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/camera.h"
#include "engine/audio/audio_system.h"
#include "game/ui/button.h"
#include "game/ui/text.h"
#include "game/ui/ui_anchor.h"

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
  renderer_clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  //editor_begin();
  
  // Render 3D stuff
  /////////////////////////////////////////////////////////////////////////////////////////
  renderer_begin(game.cam); 

  for(int i = 0; i < 10; i++) {
    render_mesh(game.mesh[i], glm::vec3(i * 10.0f, 0.0f, -5.0f), glm::vec4(1.0f, 0, 0, 1));
  }

  renderer_end();
  /////////////////////////////////////////////////////////////////////////////////////////

  // Render 2D stuff
  /////////////////////////////////////////////////////////////////////////////////////////
  renderer2d_begin();
  
  for(auto& text : game.texts) {
    ui_text_render(text);
  }
  
  for(auto& button : game.buttons) {
    ui_button_render(button);
  }

  renderer2d_end();
  /////////////////////////////////////////////////////////////////////////////////////////
  
  //editor_end();
  renderer_present();
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

  input_cursor_show(true);
  input_init();
  editor_init();

  if(!renderer_create()) {
    printf("[ERROR]: Renderer failed to be created\n");
    return false;
  }
  renderer2d_create();

  if(!audio_system_init()) {
    printf("[ERROR]: Audio system failed to be initialized\n");
    return false;
  }
  ///////////////////////////////////////////////// 

  for(int i = 0; i < 10; i++) {
    game.mesh[i] = mesh_create();
  }

  game.cam  = camera_create(glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  
  // game.texts.push_back(ui_text_create("UI_ANC_TOP_LEFT", 0.5f, UI_ANC_TOP_LEFT)); 
  game.texts.push_back(ui_text_create("UI_ANC_TOP_CENTER", 0.5f, UI_ANC_TOP_CENTER, glm::vec4(1.0f))); 
  // game.texts.push_back(ui_text_create("UI_ANC_TOP_RIGHT", 0.5f, UI_ANC_TOP_RIGHT)); 
  // game.texts.push_back(ui_text_create("UI_ANC_CENTER_LEFT", 0.5f, UI_ANC_CENTER_LEFT)); 
  // game.texts.push_back(ui_text_create("UI_ANC_CENTER", 0.5f, UI_ANC_CENTER)); 
  // game.texts.push_back(ui_text_create("UI_ANC_CENTER_RIGHT", 0.5f, UI_ANC_CENTER_RIGHT)); 
  // game.texts.push_back(ui_text_create("UI_ANC_BOTTOM_LEFT", 0.5f, UI_ANC_BOTTOM_LEFT)); 
  // game.texts.push_back(ui_text_create("UI_ANC_BOTTOM_CENTER", 0.5f, UI_ANC_BOTTOM_CENTER)); 
  // game.texts.push_back(ui_text_create("UI_ANC_BOTTOM_RIGHT", 0.5f, UI_ANC_BOTTOM_RIGHT)); 

  game.buttons.push_back(ui_button_create("PLAY", UI_ANC_CENTER));
  game.buttons.push_back(ui_button_create("SETTINGS", UI_ANC_CENTER_LEFT));

  return true;
}

void game_shutdown(Game& game) {
  audio_system_shutdown();

  renderer2d_destroy();
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
