#pragma once

#include "engine/graphics/mesh.h"
#include "game/physics/body.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Obsticle
/////////////////////////////////////////////////////////////////////////////////
struct Obsticle {
  glm::vec3 position, scale; 
  glm::vec4 color;
  bool is_active;

  Mesh* mesh;
  Body* body;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Obsticle obsticle_create(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color);
void obsticle_destroy(Obsticle* obsticle);
void obsticle_update(Obsticle* obsticle);
void obsticle_render(Obsticle* obsticle);
/////////////////////////////////////////////////////////////////////////////////
