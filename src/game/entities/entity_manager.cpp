#include "entity_manager.h"
#include "engine/defines.h"
#include "engine/math/rand.h"
#include "game/entities/player.h"
#include "game/entities/obsticle.h"

#include <glm/vec3.hpp>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void spawn_obsticle(EntityManager* entities) {
  for(u32 i = 0; i < OBSTICLES_MAX; i++) {
    if(entities->obsticles[i].is_active) {
      continue;
    }

    entities->obsticles[i].body->position  = glm::vec3(100.0f, 1.0f, random_f32(-9.0f, 0.0f)); 
    entities->obsticles[i].is_active       = true; 
    entities->can_spawn                    = false;

    break;
  }
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
EntityManager* entities_create() {
  EntityManager* entt = new EntityManager{};

  // Player init
  entt->player = player_create(glm::vec3(10.0f, 5.0f, -5.0f));

  // Base platform init 
  entt->base_platform = obsticle_create(glm::vec3(500.0f, -50.0f, -5.0f), glm::vec3(1000.0f, 100.0f, 10.0f), glm::vec4(1.0f));

  // Obsticles init 
  for(u32 i = 0; i < OBSTICLES_MAX; i++) {
    entt->obsticles[i] = obsticle_create(glm::vec3(-1000.0f, -10.0f, -1000.0f), 
                                         random_vec3(glm::vec3(1.0f), glm::vec3(3.0f, 1.0f, 3.0f)), 
                                         glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  }

  entt->spawn_timer     = 0.0f;
  entt->spawn_timer_max = 150.0f;
  entt->can_spawn       = false;

  return entt;
}

void entities_destroy(EntityManager* entities) {
  for(u32 i = 0; i < OBSTICLES_MAX; i++) {
    obsticle_destroy(&entities->obsticles[i]);
  }

  obsticle_destroy(&entities->base_platform);
  player_destory(&entities->player);
  delete entities;
}

void entities_update(EntityManager* entities) {
  entities->spawn_timer++;

  if(entities->spawn_timer > entities->spawn_timer_max) {
    spawn_obsticle(entities);
    entities->spawn_timer = 0.0f;
    entities->can_spawn   = true;

    entities->spawn_timer_max -= entities->spawn_timer_max >= 100.0f ? 0.5f : 0.0f;
  }

  player_update(&entities->player);

  for(u32 i = 0; i < OBSTICLES_MAX; i++) {
    if(!entities->obsticles[i].is_active) {
      continue;
    }

    obsticle_update(&entities->obsticles[i]);
  }
}

void entities_render(EntityManager* entities) {
  player_render(&entities->player);
  obsticle_render(&entities->base_platform);

  for(u32 i = 0; i < OBSTICLES_MAX; i++) {
    if(!entities->obsticles[i].is_active) {
      continue;
    }

    obsticle_render(&entities->obsticles[i]);
  }
}
/////////////////////////////////////////////////////////////////////////////////
