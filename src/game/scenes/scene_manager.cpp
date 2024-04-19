#include "scene_manager.h"
#include "engine/graphics/renderer.h"
#include "engine/core/event.h"
#include "engine/defines.h"
#include "game/scenes/game_scene.h"
#include "game/scenes/scene_overlay.h"
#include "game/scenes/menu_overlay.h"
#include "game/scenes/over_overlay.h"

// SceneManager
/////////////////////////////////////////////////////////////////////////////////
struct SceneManager {
  GameScene* game_scene;

  SceneOverlay overlays[OVERLAYS_MAX];
  SceneOverlay* current_overlay = nullptr;
};

static SceneManager* scenes;
/////////////////////////////////////////////////////////////////////////////////

// Callbacks
/////////////////////////////////////////////////////////////////////////////////
bool overlay_change_callback(const EventType type, const EventDesc& desc) {
  if(type != EVENT_OVERLAY_CHANGE) {
    return false;
  }

  scenes->current_overlay = &scenes->overlays[desc.overlay_type];
  scenes->current_overlay->is_active = true;

  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void scenes_create() {
  scenes = new SceneManager{};

  // Scenes init 
  scenes->game_scene = game_scene_create();

  // Overlays init 
  menu_overlay_create(&scenes->overlays[OVERLAY_MENU]);
  over_overlay_create(&scenes->overlays[OVERLAY_OVER]);

  // Setting the current overlay
  scenes->current_overlay = &scenes->overlays[OVERLAY_MENU];

  event_listen(EVENT_OVERLAY_CHANGE, overlay_change_callback);
}

void scenes_destroy() {
  for(u32 i = 0; i < OVERLAYS_MAX; i++) {
    scenes->overlays[i].destroy(&scenes->overlays[i]);
  }

  game_scene_destroy(scenes->game_scene);

  delete scenes;
}

void scenes_update() {
  // Do not render the game scene when an overlay is active
  if(scenes->current_overlay->is_active) {
    scenes->current_overlay->update(scenes->current_overlay);
    return;
  }

  game_scene_update(scenes->game_scene);
}

void scenes_render() {
  renderer_clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
  renderer_begin(scenes->game_scene->camera);

  if(scenes->current_overlay->is_active) {
    scenes->current_overlay->render(scenes->current_overlay);
  }
  else {
    game_scene_render(scenes->game_scene);
  }
  
  renderer_end();
  renderer_present();
}
/////////////////////////////////////////////////////////////////////////////////
