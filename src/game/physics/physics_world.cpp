#include "physics_world.h"
#include "game/physics/collider.h"
#include "engine/graphics/mesh.h"
#include "engine/core/clock.h"

#include <glm/vec3.hpp>

#include <vector>

// PhysicsWorld
/////////////////////////////////////////////////////////////////////////////////
struct PhysicsWorld {
  std::vector<Collider*> colliders;
  std::vector<ColliderData> collisions;
};

static PhysicsWorld* world;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_world_create() {
  world = new PhysicsWorld{};
}

void physics_world_destroy() {
  for(auto& coll : world->colliders) {
    delete coll;
  } 
  
  world->colliders.clear();
  world->collisions.clear();

  delete world;
}

void physics_world_update() {

}

Collider* physics_world_add_collider(const Mesh* mesh) {
  Collider* coll = new Collider{}; 

  world->colliders.push_back(coll);
  return coll;
}
/////////////////////////////////////////////////////////////////////////////////
