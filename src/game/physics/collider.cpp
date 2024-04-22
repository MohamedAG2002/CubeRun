#include "collider.h"

#include <glm/vec3.hpp>

#include <cstdio>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const ColliderData collider_colliding(const Collider* coll1, const Collider* coll2) {
  ColliderData data; 
  glm::vec3 min1 = coll1->position - (coll1->scale / 2.0f);
  glm::vec3 max1 = coll1->position + (coll1->scale / 2.0f);
  
  glm::vec3 min2 = coll2->position - (coll2->scale / 2.0f);
  glm::vec3 max2 = coll2->position + (coll2->scale / 2.0f);

  printf("MIN = A: {%f, %f, %f}, B: {%f, %f, %f}\n", min1.x, min1.y, min1.z, min2.x, min2.y, min2.z);
  printf("MAX = A: {%f, %f, %f}, B: {%f, %f, %f}\n", max1.x, max1.y, max1.z, max2.x, max2.y, max2.z);
  data.is_colliding = ((max1.x >= min2.x) && (min1.x <= max2.x)) && 
                      ((max1.y >= min2.y) && (min1.y <= max2.y)) && 
                      ((max1.z >= min2.z) && (min1.z <= max2.z));

  return data;
}

void collider_update_points(Collider* collider) {
  glm::vec3 min = collider->position;
  glm::vec3 max = collider->position + collider->scale;

  collider->points[0] = min;                            // Point 1 
  collider->points[1] = glm::vec3(max.x, min.y, min.z); // Point 2
  collider->points[2] = glm::vec3(max.x, max.y, min.z); // Point 3
  collider->points[3] = glm::vec3(min.x, max.y, min.z); // Point 4 

  collider->points[4] = glm::vec3(min.x, min.y, max.z); // Point 5
  collider->points[5] = glm::vec3(max.x, min.y, max.z); // Point 6
  collider->points[6] = max;                            // Point 7
  collider->points[7] = glm::vec3(min.x, max.y, max.z); // Point 8
}
/////////////////////////////////////////////////////////////////////////////////
