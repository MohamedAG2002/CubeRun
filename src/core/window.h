#pragma once

#include "defines.h"

#include <glm/vec2.hpp>

struct GLFWwindow;

// Window functions
///////////////////////////////////////////////////////
b8 window_create(i32 width, i32 height, const char* title);
void window_destroy();
void window_update();
void window_swap_buffers();
b8 window_should_close();
glm::vec2 window_get_size();
f64 window_get_time();
f32 window_get_aspect_ratio();
///////////////////////////////////////////////////////
