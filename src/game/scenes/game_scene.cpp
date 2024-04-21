#include "game_scene.h"
#include "engine/core/event.h"
#include "engine/graphics/camera.h"
#include "engine/core/input.h"
#include "game/ui/text.h"
#include "game/entities/entity_manager.h"

#include <glm/glm.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
GameScene* game_scene_create() {
  GameScene* game = new GameScene{};

  game->entities   = entities_create();

  game->pause_text = ui_text_create("PAUSED", 0.5f, UI_ANC_CENTER, glm::vec4(1.0f));
  game->is_paused  = false; 
  game->is_active  = true; 
  
  game->camera     = camera_create(glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  
  return game;
}

void game_scene_destroy(GameScene* game) {
  entities_destroy(game->entities);
  delete game;
}

void game_scene_update(GameScene* game) {
  if(input_key_pressed(KEY_P)) {
    game->is_paused = !game->is_paused;
  }

  if(game->is_paused) {
    return;
  }

  if(input_key_pressed(KEY_O)) {
    event_dispatch(EVENT_OVERLAY_CHANGE, EventDesc{.overlay_type = OVERLAY_OVER});
  }

  camera_update(&game->camera);
  camera_move(&game->camera);
  
  entities_update(game->entities);
}

void game_scene_render(GameScene* game) {
  entities_render(game->entities);
  
  if(game->is_paused) {
    ui_text_render(game->pause_text);
  }
}
/////////////////////////////////////////////////////////////////////////////////
