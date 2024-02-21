#include "camera.h"
#include "core/window.h"
#include "core/input.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

// Private functions
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

// Camera functions
////////////////////////////////////////////////////////
camera_t camera_create(const glm::vec3& pos, glm::vec3* target)
{
  camera_t cam;
  glm::vec3 look_dir = glm::normalize(pos - *target);

  cam.yaw   = 90.0f;
  cam.pitch = 0.0f;

  cam.position = pos;
  
  cam.up_axis    = glm::vec3(0.0f, 1.0f, 0.0f);
  cam.right_axis = glm::normalize(glm::cross(cam.up_axis, look_dir));
  cam.up         = glm::normalize(glm::cross(look_dir, cam.right_axis));

  cam.direction.x = glm::cos(glm::radians(cam.yaw)) * glm::cos(glm::radians(cam.pitch));
  cam.direction.y = glm::sin(glm::radians(cam.pitch));
  cam.direction.z = glm::sin(glm::radians(cam.yaw)) * glm::cos(glm::radians(cam.pitch));
  cam.front       = glm::normalize(cam.direction);

  cam.view_projection = glm::mat4(1.0f);

  return cam;
}

void camera_update(camera_t& cam)
{
  // Getting values from the window
  f32 aspect_ratio    = window_get_aspect_ratio();
  glm::vec2 mouse_pos = input_get_mouse_pos();

  // Updating the projection and view matrices
  cam.view_projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f) * 
                        glm::lookAt(cam.position, cam.position + cam.front, cam.up); 

  cam.yaw   = mouse_pos.x;
  cam.pitch = mouse_pos.y;

  // Updating the front of the camera based on the yaw and pitch values
  cam.direction.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
  cam.direction.y = sin(glm::radians(cam.pitch));
  cam.direction.z = sin(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
  cam.front       = glm::normalize(cam.direction);
}

void camera_move(camera_t& cam, f32 speed, f64 dt)
{ 
  speed *= dt;

  // Move right
  if(input_key_down(KEY_D))
    cam.position += glm::normalize(glm::cross(cam.front, cam.up)) * speed;
  // Move left
  else if(input_key_down(KEY_A))
    cam.position -= glm::normalize(glm::cross(cam.front, cam.up)) * speed;
 
  // Move forwards/up
  if(input_key_down(KEY_W))
    cam.position += cam.front * speed;
  // Move backwards/down
  else if(input_key_down(KEY_S))
    cam.position -= cam.front * speed;
}
////////////////////////////////////////////////////////
