#include "window.h"
#include "defines.h"
#include "event.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

// Window struct 
///////////////////////////////////////////////////////
struct window_t 
{
  bool fullscreen;

  glm::vec2 size, mouse_pos;
  GLFWwindow* handle;
};
///////////////////////////////////////////////////////

// Globals
///////////////////////////////////////////////////////
static window_t window;
static glm::vec2 last_mouse_pos(1.0f);
const float SENSITIVITY = 0.1f;
///////////////////////////////////////////////////////

// Callbacks
/////////////////////////////////////////////////////
void mouse_callback(GLFWwindow* win, f64 x_pos, f64 y_pos)
{
  glm::vec2 offset(x_pos - last_mouse_pos.x, last_mouse_pos.y - y_pos);
  last_mouse_pos = glm::vec2(x_pos, y_pos);

  // Adding the sensitivity 
  offset *= SENSITIVITY;

  // Adding the offset to the current mouse position to get the current position
  window.mouse_pos += offset;

  event_desc_t desc = {
    .mouse_pos = window.mouse_pos
  };
  event_dispatch(EVENT_MOUSE_MOVED, desc);
}

void key_callback(GLFWwindow* win, i32 key, i32 scancode, i32 action, i32 mods)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window.handle, true);
  
  event_desc_t desc; 
  event_type_e type;
  
  if(action == GLFW_PRESS)
  {
    desc = {
      .key_pressed = (u32)key
    };
    type = EVENT_KEY_PRESSED;
  }
  else if(action == GLFW_RELEASE)
  {
    desc = {
      .key_released = (u32)key
    };
    type = EVENT_KEY_RELEASED;
  }

  event_dispatch(type, desc);
}

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
  event_desc_t desc; 
  event_type_e type;
  
  if(action == GLFW_PRESS)
  {
    desc = {
      .button_pressed = (u32)button
    };
    type = EVENT_BUTTON_PRESSED;
  }
  else if(action == GLFW_RELEASE)
  {
    desc = {
      .button_released = (u32)button
    };
    type = EVENT_BUTTON_RELEASED;
  }

  event_dispatch(type, desc);
}

void error_callback(i32 err_code, const char* desc)
{
  printf("GLFW-ERROR: %d - %s\n", err_code, desc);
}
/////////////////////////////////////////////////////

// Window functions
///////////////////////////////////////////////////////
b8 window_create(i32 width, i32 height, const char* title)
{
  // Init GLFW 
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwSetErrorCallback(error_callback);

  window.handle = glfwCreateWindow(width, height, title, 0, 0);
  if(!window.handle)
  {
    printf("ERROR: Could not create window\n");
    return false;
  }
  glfwMakeContextCurrent(window.handle);

  // Setting callbacks
  glfwSetCursorPosCallback(window.handle, mouse_callback);
  glfwSetKeyCallback(window.handle, key_callback);
  glfwSetMouseButtonCallback(window.handle, mouse_button_callback);

  // Window variables init 
  window.fullscreen = false; 
  window.size       = glm::vec2(width, height);
  window.mouse_pos  = last_mouse_pos; 

  // Init GLAD 
  if(!gladLoadGL(glfwGetProcAddress))
  {
    printf("ERROR: Could not load GLAD\n");
    return false;
  }
  glViewport(0, 0, width, height);
  glfwMakeContextCurrent(window.handle);

  // Disable the cursor 
  glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  return true;
}

void window_destroy()
{
  glfwDestroyWindow(window.handle);
  glfwTerminate();
}

void window_update()
{
  glfwPollEvents();
}

void window_swap_buffers()
{
  glfwSwapBuffers(window.handle);
}

b8 window_should_close()
{
  return glfwWindowShouldClose(window.handle);
}

glm::vec2 window_get_size()
{
  return window.size;
}

f64 window_get_time()
{
  return glfwGetTime();
}

f32 window_get_aspect_ratio()
{
  return window.size.x / window.size.y;
}
///////////////////////////////////////////////////////
