#include "player.h"
#include "engine/defines.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/renderer.h"
#include "engine/core/input.h"
#include "game/physics/physics_world.h"
#include "game/physics/body.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// DEFS
/////////////////////////////////////////////////////////////////////////////////
#define PLAYER_SPEED   10.0f 
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void move_player(Player* player) {
  if(input_key_down(KEY_S)) {
    player->body->velocity.x = -PLAYER_SPEED;
  }
  else if(input_key_down(KEY_W)) {
    player->body->velocity.x = PLAYER_SPEED;
  }
  
  if(input_key_down(KEY_A)) {
    player->body->velocity.z = -PLAYER_SPEED;
  }
  else if(input_key_down(KEY_D)) {
    player->body->velocity.z = PLAYER_SPEED;
  }

  if(input_key_pressed(KEY_SPACE)) {
    player->body->velocity.y = PLAYER_SPEED;
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
  p.scale     = glm::vec3(1.0f);
  p.velocity  = glm::vec3(0.0f);
  p.color     = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
  p.mesh      = mesh_create();
  p.body      = physics_world_create_body(p.position, p.scale, true, "Player");

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
    player->is_active       = false; 
    player->body->is_active = false; 
    return;
  }

  move_player(player);
  player->position = player->body->position;
}

void player_render(Player* player) {
  if(!player->is_active) {
    return;
  }
  
  render_mesh(player->mesh, player->position, player->scale, player->color); 
}
/////////////////////////////////////////////////////////////////////////////////
