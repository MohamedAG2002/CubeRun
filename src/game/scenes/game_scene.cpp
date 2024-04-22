#include "game_scene.h"
#include "engine/core/event.h"
#include "engine/graphics/camera.h"
#include "engine/core/input.h"
#include "game/ui/text.h"
#include "game/entities/entity_manager.h"
#include "game/physics/physics_world.h"
#include "editor/editor.h"

#include <glm/glm.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
GameScene* game_scene_create() {
  GameScene* game = new GameScene{};

  physics_world_create();
  game->entities   = entities_create();

  game->pause_text = ui_text_create("PAUSED", 0.5f, UI_ANC_CENTER, glm::vec4(1.0f));
  game->is_paused  = false; 
  game->is_active  = true; 
  game->is_editing = false;
  
  game->camera     = camera_create(glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  return game;
}

void game_scene_destroy(GameScene* game) {
  entities_destroy(game->entities);
  physics_world_destroy();
  delete game;
}

void game_scene_update(GameScene* game) {
  if(input_key_pressed(KEY_P)) {
    game->is_paused = !game->is_paused;
  }

  if(game->is_paused) {
    return;
  }

  if(input_key_pressed(KEY_F1)) {
    game->is_editing = !game->is_editing;
    input_cursor_show(game->is_editing);
  }

  if(game->is_editing) {
    return;
  }

  camera_update(&game->camera);
  camera_move(&game->camera);
  
  physics_world_update();
  entities_update(game->entities);
}

void game_scene_render(GameScene* game) {
  entities_render(game->entities);

  if(game->is_editing) {
    editor_entities(game->entities);  
  }
  
  if(game->is_paused) {
    ui_text_render(game->pause_text);
  }
}
/////////////////////////////////////////////////////////////////////////////////
