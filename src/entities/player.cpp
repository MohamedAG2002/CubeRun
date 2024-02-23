#include "entities/player.h"
#include "core/defines.h"
#include "core/input.h"

#include "graphics/mesh.h"
#include "graphics/renderer.h"

#include "managers/resource_manager.h"

#include <glm/vec3.hpp>

// Consts
////////////////////////////////////////////////////
#define JUMP_SPEED      8.0f
#define MOVE_SPEED      8.0f
#define GRAVITY         0.3f
#define FALL_DEATH_DIST 100.0f 
////////////////////////////////////////////////////

// Private functions
////////////////////////////////////////////////////
static void move_player(player_t& player, f64 dt)
{
  if(input_key_down(KEY_LEFT))
    player.velocity.x = -MOVE_SPEED; 
  else if(input_key_down(KEY_RIGHT))
    player.velocity.x = MOVE_SPEED; 
  else 
    player.velocity.x = 0.0f;

  if(input_key_pressed(KEY_SPACE))
    player.velocity.y = JUMP_SPEED;
  else 
    player.velocity.y -= GRAVITY;
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
    .mesh      = resource_get_mesh("Cube_Mesh"),
  };
}

void player_update(player_t& player, f64 dt)
{
  // Checking if the player fell too far
  if(player.position.y > FALL_DEATH_DIST)
  {
    player.is_alive = false;
    return;
  }
 
  // Movements 
  player.position += player.velocity * (f32)dt;
  move_player(player, dt);

  // @NOTE: VERY temporary. Like, as soon as collisions are implemented, remove this.
  if(player.position.y < 0.5f)
    player.position.y = 0.5f;
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
