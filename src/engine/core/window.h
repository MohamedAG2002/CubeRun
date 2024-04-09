#pragma once

#include "engine/defines.h"

#include <glm/vec2.hpp>

struct GLFWwindow;

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool window_create(const i32 width, const i32 height, const char* title); 
void window_destroy();
void window_poll_events();
void window_swap_buffers();

const bool window_should_close();
const glm::vec2 window_get_size();
const f64 window_get_time();
GLFWwindow* window_get_handle(); 

void window_set_current_context();
void window_set_close(const bool close);
/////////////////////////////////////////////////////////////////////////////////
