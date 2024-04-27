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
    platform.position = platform.body->position;
  }
}

Platform& entities_platform_add(EntityManager* entities, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color) {
  Platform plat; 
  plat.position = pos; 
  plat.scale    = scale;
  plat.color    = color;
  plat.mesh     = mesh_create(); 
  plat.body     = physics_world_create_body(plat.position, plat.scale, false, "Platform");

  entities->platforms.push_back(plat);
  return entities->platforms.back();
}
/////////////////////////////////////////////////////////////////////////////////
