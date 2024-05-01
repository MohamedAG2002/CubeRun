#include "obsticle.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/renderer.h"
#include "game/physics/body.h"
#include "game/physics/physics_world.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Obsticle obsticle_create(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color) {
  Obsticle o; 
  o.position  = pos;
  o.scale     = scale;
  o.color     = color;
  o.is_active = false;
  o.mesh      = mesh_create();
  o.body      = physics_world_create_body(pos, scale, false, color == glm::vec4(1.0f) ? "Platform" : "Obsticle");

  return o;
}

void obsticle_destroy(Obsticle* obsticle) {
  mesh_destroy(obsticle->mesh);
}

void obsticle_update(Obsticle* obsticle) {
  obsticle->body->velocity.x = -20.0f; 
  obsticle->position = obsticle->body->position;

  if(obsticle->body->position.x <= -50.0f) {
    obsticle->is_active      = false;
    obsticle->body->position = glm::vec3(-1000.0f, -1000.0f, -1000.0f);
  }
}

void obsticle_render(Obsticle* obsticle) {
  render_mesh(obsticle->mesh, obsticle->position, obsticle->scale, obsticle->color);
}
/////////////////////////////////////////////////////////////////////////////////
