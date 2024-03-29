#pragma once

#include "core/defines.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

// Camera type
////////////////////////////////////////////////////////
struct camera_t
{
  f32 yaw, pitch;

  glm::vec3 position;
  glm::vec3 up_axis, right_axis, up;
  glm::vec3 direction, front;

  glm::mat4 view_projection;
};
////////////////////////////////////////////////////////

// Camera 3D functions
////////////////////////////////////////////////////////
camera_t camera_create(const glm::vec3& pos, glm::vec3* target);
void camera_update(camera_t& cam);
void camera_move(camera_t& cam, f32 speed, f64 dt);
////////////////////////////////////////////////////////
