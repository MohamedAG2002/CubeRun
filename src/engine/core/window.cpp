#include "window.h"
#include "engine/defines.h"
#include "engine/core/event.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <cstdio>

// Window
/////////////////////////////////////////////////////////////////////////////////
struct Window {
  GLFWwindow* handle = nullptr;

  glm::vec2 size;
  glm::vec2 mouse_pos, last_mouse_pos;

  bool is_focused;
}; 

static Window window;

#define SENS 0.1f
/////////////////////////////////////////////////////////////////////////////////

// Callbacks
/////////////////////////////////////////////////////////////////////////////////
void mouse_callback(GLFWwindow* win, f64 x_pos, f64 y_pos) {
  // Will happen once when the window is initially focused to prevent sudden 
  // large mouse movements.
  if(!window.is_focused) {
    window.is_focused = true; 
    window.last_mouse_pos = glm::vec2(x_pos, y_pos);
  }

  glm::vec2 offset(x_pos - window.last_mouse_pos.x, window.last_mouse_pos.y - y_pos);
  window.last_mouse_pos = glm::vec2(x_pos, y_pos);

  offset *= SENS; 
  window.mouse_pos += offset;

  EventDesc desc = {
    .mouse_pos = window.mouse_pos,
  };
  event_dispatch(EVENT_MOUSE_MOVED, desc);
}

void frame_buffer_resize_callback(GLFWwindow* win, i32 width, i32 height) {
  window.size = glm::vec2(width, height);
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* win, i32 key, i32 scancode, i32 action, i32 mods) {
  EventType type;
  EventDesc desc;

  if(action == GLFW_PRESS) {
    desc = {
      .key_pressed = key, 
    };
    type = EVENT_KEY_PRESSED;
  }
  else if(action == GLFW_RELEASE) {
    desc = {
      .key_released = key, 
    };
    type = EVENT_KEY_RELEASED;
  }
  
  event_dispatch(type, desc);
}

void mouse_button_callback(GLFWwindow* win, i32 button, i32 action, i32 mods) {
  EventType type;
  EventDesc desc;

  if(action == GLFW_PRESS) {
    desc = {
      .button_pressed = button, 
    };
    type = EVENT_MOUSE_BUTTON_PRESSED;
  }
  else if(action == GLFW_RELEASE) {
    desc = {
      .button_released = button, 
    };
    type = EVENT_MOUSE_BUTTON_RELEASED;
  }
  
  event_dispatch(type, desc);
}

void error_callback(i32 err_code, const char* desc) {
  printf("[ERROR, CODE: %i]: %s\n", err_code, desc);
}

bool cursor_mode_change_callback(const EventType type, const EventDesc& desc) {
  if(type != EVENT_CURSOR_CHANGED) {
    return false;
  }
  
  if(desc.cursor_shown) {
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
  else {
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }

  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Priavte functions
/////////////////////////////////////////////////////////////////////////////////
static void glfw_init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  glfwSetErrorCallback(error_callback);
}

static bool create_handle(i32 width, i32 height, const char* title) {
  window.handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if(!window.handle) {
    printf("[ERROR]: Failed to create GLFW window\n");
    return false; 
  } 
  // Everything's good. Set the context
  else {
    glfwMakeContextCurrent(window.handle);
  }

  // Disable VSYNC
  glfwSwapInterval(0);
  glfwSetInputMode(window.handle, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE); 

  return true;
}

static void set_callbacks() {
  glfwSetCursorPosCallback(window.handle, mouse_callback);
  glfwSetFramebufferSizeCallback(window.handle, frame_buffer_resize_callback);
  glfwSetKeyCallback(window.handle, key_callback);
  glfwSetMouseButtonCallback(window.handle, mouse_button_callback); 
}

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool window_create(const i32 width, const i32 height, const char* title) {
  // GLFW init 
  ////////////////////////////////////////// 
  glfw_init();
  if(!create_handle(width, height, title)) {
    return false;
  }
  set_callbacks();
  ////////////////////////////////////////// 

  // Window init
  ////////////////////////////////////////// 
  window.size = glm::vec2(width, height);
  window.last_mouse_pos = glm::vec2(0.0f);
  window.mouse_pos = window.last_mouse_pos; 
  window.is_focused = false;
  event_listen(EVENT_CURSOR_CHANGED, cursor_mode_change_callback);
  ////////////////////////////////////////// 

  return true;
}

void window_destroy() {
  glfwDestroyWindow(window.handle);
  glfwTerminate();
}

void window_poll_events() {
  glfwPollEvents();
}

void window_swap_buffers() {
  glfwSwapBuffers(window.handle);
}

const bool window_should_close() {
  return glfwWindowShouldClose(window.handle);
}

const glm::vec2 window_get_size() {
  return window.size; 
}

const f64 window_get_time() {
  return glfwGetTime();
}

const f32 window_get_aspect_ratio() {
  return window.size.x / window.size.y;
}

GLFWwindow* window_get_handle() {
  return window.handle;
}

void window_set_current_context() {
  glfwMakeContextCurrent(window.handle);
}

void window_set_close(const bool close) {
  glfwSetWindowShouldClose(window.handle, close);
}
/////////////////////////////////////////////////////////////////////////////////

