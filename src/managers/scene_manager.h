#pragma once

#include "core/defines.h"
#include "graphics/camera.h"

// Scene manager functions
/////////////////////////////////////////////////
void scene_manager_init();
void scene_manager_shutdown();
void scene_manager_update(f64 dt);
void scene_manager_render();
const camera_t& scene_manager_get_active_camera();
/////////////////////////////////////////////////
