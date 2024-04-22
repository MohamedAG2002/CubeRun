#include "entity_manager.h"
#include "engine/graphics/mesh.h"
#include "game/entities/player.h"
#include "engine/graphics/renderer.h"
#include "game/physics/physics_world.h"

#include <glm/vec3.hpp>

#include <vector>

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
  player_update(&entities->player);
}

void entities_render(EntityManager* entities) {
  player_render(&entities->player);

  for(auto& platform : entities->platforms) {
    render_mesh(platform.mesh, platform.position, platform.scale, platform.color);
  }
}

void entities_platform_add(EntityManager* entities, const glm::vec3& pos) {
  Platform plat; 
  plat.position = pos; 
  plat.scale    = glm::vec3(1.0f);
  plat.color    = glm::vec4(1.0f);
  plat.mesh     = mesh_create(); 
  plat.collider = physics_world_add_collider(plat.mesh);

  entities->platforms.push_back(plat);
}
/////////////////////////////////////////////////////////////////////////////////
