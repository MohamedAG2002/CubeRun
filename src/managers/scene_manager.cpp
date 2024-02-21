#include "managers/scene_manager.h"
#include "scenes/game_scene.h"
#include "scenes/scene_type.h"

#include "core/defines.h"
#include "core/event.h"

#include "graphics/camera.h"

// Scene manager struct
/////////////////////////////////////////////////
struct scene_manager_t 
{ 
  scene_type_e current_scene;
  camera_t* active_cam = nullptr; 

  game_scene_t* game_scn;
};

static scene_manager_t* s_scn_man;
/////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////
static void change_scene(const scene_type_e type)
{
  s_scn_man->current_scene = type; 
  
  switch(type)
  {
    case SCENE_MENU:
      break;
    case SCENE_GAME:
      game_scene_reset(s_scn_man->game_scn);
      s_scn_man->active_cam = &s_scn_man->game_scn->cam;
      break;
    case SCENE_OVER:
      break;
    default:
      break;
  }
}
/////////////////////////////////////////////////

// Callbacks
/////////////////////////////////////////////////
b8 scene_change_callback(const event_type_e type, const event_desc_t& desc)
{
  // Make sure it's the appropriate event
  if(type != EVENT_SCENE_CHANGED)
    return false;

  // Only change the current scene if its different 
  if(s_scn_man->current_scene == desc.scene)
    return false;

  // Change the current scene
  change_scene(desc.scene);

  return true;
}
/////////////////////////////////////////////////

// Scene manager functions
/////////////////////////////////////////////////
void scene_manager_init()
{
  s_scn_man = new scene_manager_t{};
  event_listen(EVENT_SCENE_CHANGED, scene_change_callback);

  // Scenes init 
  s_scn_man->game_scn = game_scene_create();
  
  // Variables init 
  s_scn_man->current_scene = SCENE_GAME;
  s_scn_man->active_cam    = &s_scn_man->game_scn->cam;
}

void scene_manager_shutdown()
{
  game_scene_shutdown(s_scn_man->game_scn);

  delete s_scn_man;
}

void scene_manager_update(f64 dt)
{
  switch(s_scn_man->current_scene)
  {
    case SCENE_MENU:
      break;
    case SCENE_GAME:
      game_scene_update(s_scn_man->game_scn, dt);
      break;
    case SCENE_OVER:
      break;
    default:
      break;
  }
}

void scene_manager_render()
{
  switch(s_scn_man->current_scene)
  {
    case SCENE_MENU:
      break;
    case SCENE_GAME:
      game_scene_render(s_scn_man->game_scn);
      break;
    case SCENE_OVER:
      break;
    default:
      break;
  }
}

const camera_t& scene_manager_get_active_camera()
{
  return *s_scn_man->active_cam;
}
/////////////////////////////////////////////////
