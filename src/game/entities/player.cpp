#include "player.h"
#include "engine/core/clock.h"
#include "engine/defines.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/renderer.h"
#include "engine/core/input.h"
#include "game/physics/collider.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// DEFS
/////////////////////////////////////////////////////////////////////////////////
#define PLAYER_SPEED   10.0f 
#define PLAYER_GRAVITY 0.081f
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void move_player(Player* player) {
  if(input_key_pressed(KEY_SPACE)) {
    player->velocity.y = PLAYER_SPEED;     
  }
  else {
    player->velocity.y -= PLAYER_GRAVITY;
  }
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Player player_create(const glm::vec3& pos) {
  Player p{};
  p.is_active = true; 
  p.tries     = 3; 
  p.position  = pos;
  p.velocity  = glm::vec3(0.0f);
  p.color     = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
  p.mesh      = mesh_create();

  return p;
}

void player_destory(Player* player) {
  mesh_destroy(player->mesh);
}

void player_update(Player* player) {
  if(!player->is_active) {
    return;
  }

  if(player->tries == 0) {
    player->is_active = false; 
    return;
  }

  move_player(player);
  player->position += player->velocity * (f32)crclock_delta_time();
}

void player_render(Player* player) {
  if(!player->is_active) {
    return;
  }
  
  render_mesh(player->mesh, player->position, player->color); 
}
/////////////////////////////////////////////////////////////////////////////////
