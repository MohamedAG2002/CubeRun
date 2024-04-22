#include "camera.h"
#include "engine/core/clock.h"
#include "engine/defines.h"
#include "engine/core/input.h"
#include "engine/core/window.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

// Globals
/////////////////////////////////////////////////////////////////////////////////
const f32 CAM_MAX_DEG  = 89.0f;
const f32 CAM_MAX_ZOOM = 180.0f;
const f32 CAM_SPEED    = 10.0f;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Camera camera_create(const glm::vec3& position, const glm::vec3& target) {
  Camera  cam; 
 
  cam.yaw   = -90.0f;
  cam.pitch = 0.0f;
  cam.zoom  = 45.0f;
  cam.type  = CAMERA_FREE;

  glm::vec3 look_dir   = glm::vec3(position - target); 
  glm::vec3 up_axis    = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 right_axis = glm::normalize(glm::cross(up_axis, look_dir));
  
  cam.position    = position; 
  cam.up          = glm::normalize(glm::cross(look_dir, right_axis));
  cam.direction.x = glm::cos(glm::radians(cam.yaw)) * glm::cos(glm::radians(cam.pitch));
  cam.direction.y = glm::sin(glm::radians(cam.pitch));
  cam.direction.z = glm::sin(glm::radians(cam.yaw)) * glm::cos(glm::radians(cam.pitch));
  cam.front       = glm::normalize(cam.direction);
 
  cam.view_projection = glm::mat4(1.0f);

  return cam;
}

void camera_update(Camera* camera) {
  glm::vec2 mouse_pos = input_mouse_pos();  
  f32 aspect_ratio    = window_get_aspect_ratio();

  camera->view_projection = glm::perspective(glm::radians(camera->zoom), aspect_ratio, 0.1f, 100.0f) * 
                            glm::lookAt(camera->position, camera->position + camera->front, camera->up);

  camera->yaw   = mouse_pos.x;
  camera->pitch = mouse_pos.y;

  camera->pitch = glm::clamp(camera->pitch, -CAM_MAX_DEG, CAM_MAX_DEG);
  camera->zoom  = glm::clamp(camera->zoom, 1.0f, CAM_MAX_ZOOM);

  camera->direction.x = glm::cos(glm::radians(camera->yaw)) * glm::cos(glm::radians(camera->pitch));
  camera->direction.y = glm::sin(glm::radians(camera->pitch));
  camera->direction.z = glm::sin(glm::radians(camera->yaw)) * glm::cos(glm::radians(camera->pitch));
  camera->front       = glm::normalize(camera->direction);
}

void camera_move(Camera* camera) {
  f32 speed = CAM_SPEED * crclock_delta_time();

  // Move forward
  if(input_key_down(KEY_W)) {
    camera->position += camera->front * speed;
  }
  // Move backwards
  else if(input_key_down(KEY_S)) {
    camera->position -= camera->front * speed;
  }
 
  // Move right
  if(input_key_down(KEY_D)) {
    camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * speed;
  }
  // Move left
  else if(input_key_down(KEY_A)) {
    camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * speed;
  }

  // Don't move on the Y-axis if the camera fixed 
  if(camera->type == CAMERA_FIXED) {
    camera->position.y = 0.0f;
  }
}
/////////////////////////////////////////////////////////////////////////////////
