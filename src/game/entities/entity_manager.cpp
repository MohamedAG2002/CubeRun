#include "entity_manager.h"
#include "game/entities/player.h"

#include <glm/vec3.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
EntityManager* entities_create() {
  EntityManager* entt = new EntityManager{};
  
  entt->player = player_create(glm::vec3(10.0f, 0.0f, -5.0f));

  return entt;
}

void entities_destroy(EntityManager* entities) {
  player_destory(&entities->player);
  delete entities;
}

void entities_update(EntityManager* entities) {
  //player_update(&entities->player);
}

void entities_render(EntityManager* entities) {
  player_render(&entities->player);
}
/////////////////////////////////////////////////////////////////////////////////
