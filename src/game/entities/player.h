#pragma once

#include "engine/defines.h"
#include "engine/graphics/mesh.h"
#include "game/physics/body.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Player
/////////////////////////////////////////////////////////////////////////////////
struct Player {
  bool is_active, has_fell;
  u32 tries;

  glm::vec3 position, scale, velocity;
  glm::vec4 color;

  Body* body;
  Mesh* mesh;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Player player_create(const glm::vec3& pos);
void player_destory(Player* player);
void player_update(Player* player);
void player_render(Player* player);
/////////////////////////////////////////////////////////////////////////////////
