#include "game_scene.h"
#include "engine/core/event.h"
#include "engine/graphics/camera.h"
#include "engine/core/input.h"
#include "engine/file/file.h"
#include "game/ui/text.h"
#include "game/entities/entity_manager.h"
#include "game/physics/physics_world.h"

#include <glm/glm.hpp>

#include <string>

// Globals Yuckk!!!!
/////////////////////////////////////////////////////////////////////////////////
static bool s_can_reset = false;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void rewind_game_scene(GameScene* game) {
  game->is_paused = false;

  entities_reset(game->entities);

  game->entities->player.tries--;

  s_can_reset = false;
}

static void reset_game_scene(GameScene* game) {
  if(game->score > game->high_score) {
    game->high_score = game->score;
    file_binary_save_u32(game->high_score, "assets/data/scr.dat");
  }
  
  game->is_paused = false;
  game->score     = 0;
  game->is_paused = false;

  entities_reset(game->entities);
  game->entities->player.tries = 3;
  
  event_dispatch(EVENT_MUSIC_PLAY, EventDesc{.music_type = MUSIC_BACKGROUND});
}

static bool coll_func(const EventType type, const EventDesc& desc) {
  if(type != EVENT_COLLISION) {
    return false;
  }

  bool is_player   = desc.collision.coll1->id == "Player" || desc.collision.coll2->id == "Player";
  bool is_obsticle = desc.collision.coll1->id == "Obsticle" || desc.collision.coll2->id == "Obsticle";
  if(is_player && is_obsticle) {
    s_can_reset = true;
    event_dispatch(EVENT_SOUND_PLAY, EventDesc{.sound_type = SOUND_HIT});
  }

  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
GameScene* game_scene_create() {
  GameScene* game = new GameScene{};

  physics_world_create();

  game->entities = entities_create();

  game->pause_text = ui_text_create("PAUSED", 0.5f, UI_ANC_CENTER, glm::vec4(1.0f));
  game->score_text = ui_text_create("SCORE: 0", 0.3f, UI_ANC_TOP_CENTER, glm::vec4(1.0f));
  game->tries_text = ui_text_create("TRIES: 3", 0.3f, UI_ANC_TOP_LEFT, glm::vec4(1.0f));

  game->is_paused  = false; 
  game->is_active  = true; 
  
  game->camera     = camera_create(glm::vec3(0.0f, 3.0f, -5.0f), glm::vec3(0.0f, 3.0f, -3.0f));

  game->score      = 0;
  game->high_score = file_binary_load_u32("assets/data/scr.dat");

  event_listen(EVENT_COLLISION, coll_func);

  return game;
}

void game_scene_destroy(GameScene* game) {
  entities_destroy(game->entities);
  physics_world_destroy();
  delete game;
}

void game_scene_update(GameScene* game) {
  if(s_can_reset || game->entities->player.has_fell) {
    rewind_game_scene(game);
  }

  if(game->entities->player.tries == 0) {
    reset_game_scene(game);
    
    event_dispatch(EVENT_OVERLAY_CHANGE, EventDesc{.overlay_type = OVERLAY_OVER});
    event_dispatch(EVENT_SOUND_PLAY, EventDesc{.sound_type = SOUND_DEATH});
    event_dispatch(EVENT_MUSIC_STOP, EventDesc{.music_type = MUSIC_BACKGROUND});
  }

  if(input_key_pressed(KEY_P)) {
    game->is_paused = !game->is_paused;
  }

  if(game->is_paused) {
    return;
  }

  game->score++;

  camera_update(&game->camera);
  // camera_move(&game->camera);
    
  physics_world_update();
  entities_update(game->entities);

  ui_text_change(game->score_text, "SCORE: " + std::to_string(game->score));
  ui_text_change(game->tries_text, "TRIES: " + std::to_string(game->entities->player.tries));
}

void game_scene_render(GameScene* game) {
  entities_render(game->entities);
  
  ui_text_render(game->score_text);
  ui_text_render(game->tries_text);
  
  if(game->is_paused) {
    ui_text_render(game->pause_text);
  }
}
/////////////////////////////////////////////////////////////////////////////////
