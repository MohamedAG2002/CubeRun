#include "physics_world.h"
#include "engine/core/clock.h"
#include "game/physics/collider.h"
#include "game/physics/body.h"

#include <cstdio>
#include <glm/vec3.hpp>

#include <vector>
#include <string>

// PhysicsWorld
/////////////////////////////////////////////////////////////////////////////////
struct PhysicsWorld {
  std::vector<Body*> bodies;
  std::vector<ColliderData> collisions;

  glm::vec3 gravity;
};

static PhysicsWorld* world;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void check_collisions() {
  for(auto& body1 : world->bodies) {
    if(!body1->is_active) {
      continue;
    }

    for(auto& body2 : world->bodies) {
      if(!body2->is_active) {
        continue;
      }

      // Make sure to not check collisions with the same body
      if(body1->collider.id == body2->collider.id) {
        continue;
      }      

      const ColliderData collision = collider_colliding(&body1->collider, &body2->collider);
      if(collision.is_colliding) {
        world->collisions.push_back(collision);
      }
    }
  }
}

static void resolve_collisions() {
  for(auto& coll : world->collisions) {
    if(coll.coll1->body->is_dynamic) {
      coll.coll1->body->position -= (-coll.normal * coll.depth); 
      coll.coll1->body->velocity = glm::vec3(0.0f); 
    }
    
    if(coll.coll2->body->is_dynamic) {
      coll.coll2->body->position -= (-coll.normal * coll.depth); 
      coll.coll2->body->velocity = glm::vec3(0.0f); 
    }
  }

  world->collisions.clear();
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_world_create() {
  world          = new PhysicsWorld{};
  world->gravity = glm::vec3(0.0f, -0.081f, 0.0f);
}

void physics_world_destroy() {
  for(auto& body : world->bodies) {
    delete body;
  }

  delete world;
}

void physics_world_update() {
  for(auto& body : world->bodies) {
    body->velocity += body->is_dynamic ? world->gravity : glm::vec3(0.0f); 
    body->position += body->velocity * (f32)crclock_delta_time();

    // body->velocity = glm::vec3(0.0f);
    collider_update_points(&body->collider, body->position);
  }

  check_collisions();
  resolve_collisions();
}

Body* physics_world_create_body(const glm::vec3& pos, const glm::vec3& scale, const bool dynamic, const std::string& id) {
  Body* body       = new Body{};
  body->position   = pos;
  body->velocity   = glm::vec3(0.0f);
  body->is_active  = true; 
  body->is_dynamic = dynamic;
  body_add_collider(body, scale, id);

  world->bodies.push_back(body);
  return body;
}
/////////////////////////////////////////////////////////////////////////////////
