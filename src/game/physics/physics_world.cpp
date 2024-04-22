#include "physics_world.h"
#include "engine/math/rand.h"
#include "game/physics/collider.h"

#include <glm/vec3.hpp>

#include <cstdio>
#include <vector>

// PhysicsWorld
/////////////////////////////////////////////////////////////////////////////////
struct PhysicsWorld {
  std::vector<Collider*> colliders;
  std::vector<ColliderData> collisions;
};

static PhysicsWorld* world;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void check_collisions() {
  for(auto& coll1 : world->colliders) {
    collider_update_points(coll1);
    
    for(auto& coll2 : world->colliders) {
      // Don't collision with itself
      if(coll1->id == coll2->id) {
        continue;
      }

      collider_update_points(coll2);
      ColliderData data = collider_colliding(coll1, coll2);

      if(data.is_colliding) {
        printf("COLLISION!!!!!!!!!!\n");
      }
    }
  }
}

static void resolve_collisions() {

}
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
  check_collisions();
  resolve_collisions();
}

Collider* physics_world_add_collider(const glm::vec3& pos, const glm::vec3& scale) {
  Collider* coll  = new Collider{}; 
  coll->position  = pos; 
  coll->scale     = scale;
  coll->id        = random_u32();
  coll->is_active = true;

  // MIN = Left most side 
  // MAX = Right most side
  //
  // \5------------------------6\
  //  \                        | \
  //  |\1----------------------|--\2                      
  //  | |                      |   |
  //  | |                      |   | 
  //  | |                      |   | 
  //  | |                      |   | 
  //  | |                      |   | 
  //  | |                      |   | 
  //  8-|----------------------7\  |
  //  \ |                        \ |
  //   \4-------------------------\3

  glm::vec3 min = coll->position - (coll->scale / 2.0f);
  glm::vec3 max = coll->position + (coll->scale / 2.0f);

  coll->points[0] = min;                            // Point 1 
  coll->points[1] = glm::vec3(max.x, min.y, min.z); // Point 2
  coll->points[2] = glm::vec3(max.x, max.y, min.z); // Point 3
  coll->points[3] = glm::vec3(min.x, max.y, min.z); // Point 4
  
  coll->points[4] = glm::vec3(min.x, min.y, max.z); // Point 5
  coll->points[5] = glm::vec3(max.x, min.y, max.z); // Point 6
  coll->points[6] = max;                            // Point 7
  coll->points[7] = glm::vec3(min.x, max.y, max.z); // Point 8

  world->colliders.push_back(coll);
  return coll;
}
/////////////////////////////////////////////////////////////////////////////////
