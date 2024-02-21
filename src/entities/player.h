#pragma once

#include "core/defines.h"

#include "graphics/mesh.h"

#include <glm/vec3.hpp>

// Player struct
////////////////////////////////////////////////////
struct player_t
{
  b8 is_alive;
 
  glm::vec3 start_pos, position, velocity;
  mesh_t* mesh;
};
////////////////////////////////////////////////////

// Player functions
////////////////////////////////////////////////////
player_t player_create(const glm::vec3& pos);
void player_destroy(player_t& player);
void player_update(player_t& player, f64 dt);
void player_render(const player_t& player);
void player_reset(player_t& player);
////////////////////////////////////////////////////
