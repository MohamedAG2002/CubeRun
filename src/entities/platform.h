#pragma once

#include "core/defines.h"
#include "graphics/mesh.h"

#include <glm/vec3.hpp>

// Platform consts
//////////////////////////////////////////////
#define MAX_PLATFORMS 100
//////////////////////////////////////////////

// Platform struct
//////////////////////////////////////////////
struct platform_t 
{
  glm::vec3 start_pos, scale;
  glm::vec3 random_pos[3];
  glm::vec3 positions[MAX_PLATFORMS];
  glm::vec3 velocities[MAX_PLATFORMS];
  
  b8 active_flags[MAX_PLATFORMS];

  mesh_t* meshes[MAX_PLATFORMS];

  f32 spawn_timer;
};
//////////////////////////////////////////////

// Platform functions
//////////////////////////////////////////////
platform_t* platforms_create(const glm::vec3& pos);
void platforms_destroy(platform_t* plat);
void platforms_update(platform_t* plat, f64 dt);
void platforms_render(platform_t* plat);
void platforms_reset(platform_t* plat);
//////////////////////////////////////////////
