#pragma once 

#include "game/physics/body.h"

#include <glm/vec3.hpp>

#include <string>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void physics_world_create();
void physics_world_destroy();
void physics_world_update();

Body* physics_world_create_body(const glm::vec3& pos, const glm::vec3& scale, const bool dynamic, const std::string& id);
/////////////////////////////////////////////////////////////////////////////////
