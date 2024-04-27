#include "body.h"
#include "engine/math/rand.h"
#include "game/physics/collider.h"

#include <glm/glm.hpp>

#include <string>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void body_add_collider(Body* body, const glm::vec3& scale, const std::string& id) {
  body->collider.scale       = scale;
  body->collider.id          = random_u32();
  body->collider.is_grounded = false;
  body->collider.id          = id;
  body->collider.body        = body;
  
  collider_update_points(&body->collider, body->position);
}
/////////////////////////////////////////////////////////////////////////////////
