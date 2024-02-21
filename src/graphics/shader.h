#pragma once

#include "core/defines.h"

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

// Shader struct
///////////////////////////////////////////////////////
struct shader_t 
{
  u32 program, vert, frag;
};
///////////////////////////////////////////////////////

// Shader functions
///////////////////////////////////////////////////////
shader_t shader_load(const char* path);
void shader_unload(shader_t& shader);
void shader_bind(const shader_t& shader);

void shader_upload_vec4(const shader_t& shader, const char* name, const glm::vec4& value);
void shader_upload_mat4(const shader_t& shader, const char* name, const glm::mat4& value);
///////////////////////////////////////////////////////
