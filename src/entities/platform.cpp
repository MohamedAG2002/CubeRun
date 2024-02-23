#include "platform.h"
#include "core/defines.h"
#include "core/input.h"
#include "graphics/renderer.h"
#include "managers/resource_manager.h"

#include <glm/vec3.hpp>

// Platform consts
//////////////////////////////////////////////
#define PLATFORM_SPEED 20
#define MAX_SPAWN_TIME 30.0f
//////////////////////////////////////////////

// Private functions
//////////////////////////////////////////////
static void spawn_platform(platform_t* plat)
{
  for(u32 i = 0; i < MAX_PLATFORMS; i++)
  {
    // We only care about the deactivated platforms
    if(plat->active_flags[i])
      continue;

    // Spawn the platform 
    plat->positions[i] = plat->start_pos;
    plat->velocities[i] = glm::vec3(0.0f, 0.0f, PLATFORM_SPEED);
    plat->active_flags[i] = true; 
    break;
  }
}
//////////////////////////////////////////////

// Platform functions
//////////////////////////////////////////////
platform_t* platforms_create(const glm::vec3& pos)
{
  platform_t* plat = new platform_t;
  plat->start_pos = pos; 
  plat->scale = glm::vec3(2.7f, 0.1f, 5.8f);
  plat->spawn_timer = 0.0f;

  for(u32 i = 0; i < MAX_PLATFORMS; i++)
  {
    plat->positions[i] = glm::vec3(-1000.0f);
    plat->velocities[i] = glm::vec3(0.0f, 0.0f, PLATFORM_SPEED);
    plat->active_flags[i] = false;
    
    plat->meshes[i] = resource_get_mesh("Platform_Mesh");
  }

  return plat;
}

void platforms_destroy(platform_t* plat)
{
  delete plat;
}

void platforms_update(platform_t* plat, f64 dt)
{
  // Spawn a platform every once in a while
  plat->spawn_timer++; 
  if(plat->spawn_timer >= MAX_SPAWN_TIME)
  {
    plat->spawn_timer = 0.0f;
    spawn_platform(plat);
  }

  // Updating each platform
  for(u32 i = 0; i < MAX_PLATFORMS; i++)
  {
    // We don't care about the deactivated platforms
    if(!plat->active_flags[i])
      continue;

    // Deactivate the platform if it goes out of screen
    if(plat->positions[i].z > 15.0f)
    {
      plat->active_flags[i] = false;
      plat->positions[i] = glm::vec3(-1000.0f);
      continue;
    }

    plat->positions[i] += plat->velocities[i] * (f32)dt;
  }
}

void platforms_render(platform_t* plat)
{
  for(u32 i = 0; i < MAX_PLATFORMS; i++)
  {
    if(!plat->active_flags[i])
      continue;

    render_mesh(plat->meshes[i], plat->positions[i], plat->scale, glm::vec4(0.9f));    
  }
}

void platforms_reset(platform_t* plat)
{
  plat->spawn_timer = 0.0f;

  for(u32 i = 0; i < MAX_PLATFORMS; i++)
  {
    plat->active_flags[i] = false; 
    plat->positions[i] = plat->start_pos;
    plat->velocities[i] = glm::vec3(0.0f);
  }
}
//////////////////////////////////////////////
