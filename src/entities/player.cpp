#include "entities/player.h"
#include "core/defines.h"
#include "core/input.h"

#include "graphics/mesh.h"
#include "graphics/renderer.h"

#include <glm/vec3.hpp>

// Consts
////////////////////////////////////////////////////
const f32 JUMP_SPEED      = 50.0f;
const f32 GRAVITY         = 98.1f;
const f32 FALL_DEATH_DIST = 100.0f; 
////////////////////////////////////////////////////

// Private functions
////////////////////////////////////////////////////
static void move_player(player_t& player)
{
  if(input_key_down(KEY_LEFT))
    player.velocity.z = -JUMP_SPEED; 
  else if(input_key_down(KEY_RIGHT))
    player.velocity.z = JUMP_SPEED; 
  else 
    player.velocity.z = 0.0f; 
}
////////////////////////////////////////////////////

// Player functions
////////////////////////////////////////////////////
player_t player_create(const glm::vec3& pos)
{
  return player_t{
    .is_alive  = true,
    .start_pos = pos, 
    .position  = pos, 
    .velocity  = glm::vec3(0.0f),
    .mesh      = mesh_load(),
  };
}

void player_destroy(player_t& player)
{
  mesh_destroy(player.mesh);
}

void player_update(player_t& player, f64 dt)
{
  // Checking if the player fell too far
  if(player.position.y > FALL_DEATH_DIST)
  {
    player.is_alive = false;
    return;
  }
  
  move_player(player);
  player.position += player.velocity * (f32)dt;
}

void player_render(const player_t& player)
{
  render_mesh(player.mesh, player.position, glm::vec3(1.0f), glm::vec4(1.0f)); 
}

void player_reset(player_t& player)
{
  player.position = player.start_pos;
  player.is_alive = true; 
  player.velocity = glm::vec3(0.0f);
}
////////////////////////////////////////////////////
