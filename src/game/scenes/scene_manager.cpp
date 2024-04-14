#include "scene_manager.h"
#include "game/scenes/overlay_type.h"

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static Scene* game_scene_create() {
  return nullptr;
}

static void build_overlays(SceneManager* scenes) {

  // Finally, point the current overlay to the 
  // first desired overlay to be displayed.
  scenes->current_overlay = scenes->overlays[OVERLAY_INTRO];
}

static void overlay_update(SceneManager* scenes) {
  // When an overlay transitiones into the game scene, 
  // make the current_overlay pointer invalid to tell 
  // the manager to ignore it and give attention to the game scene.
}

static void overlay_render(SceneManager* scenes) {

}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
SceneManager* scenes_create() {
  SceneManager* scns = new SceneManager{}; 
  scns->game_scene   = game_scene_create();
  build_overlays(scns);
  
  return scns;
}

void scenes_destroy(SceneManager* scenes) {
  
}

void scenes_update(SceneManager* scenes) {
  // If an overlay is currently active, update it and ignore the game scene for now.
  if(!scenes->current_overlay) {
    overlay_update(scenes);  
    return;
  }
  
  // Update the game scene
}

void scenes_render(SceneManager* scenes) {
  // Same story...
  if(!scenes->current_overlay) {
    overlay_render(scenes);  
    return;
  }

  // Render the game scene
}
/////////////////////////////////////////////////////////////////////////////////
