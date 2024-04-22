#pragma once 

#include "game/physics/collider.h"

#include <glm/vec3.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_world_create();
void physics_world_destroy();
void physics_world_update();

Collider* physics_world_add_collider(const glm::vec3& pos, const glm::vec3& scale);
/////////////////////////////////////////////////////////////////////////////////
