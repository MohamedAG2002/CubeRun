#pragma once

#include "engine/defines.h"

#include <string>

#include <glm/glm.hpp>

// Shader
/////////////////////////////////////////////////////////////////////////////////
struct Shader {
  std::string vert_src, frag_src; 

  u32 id, vert_id, frag_id;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Shader* shader_load(const std::string path);
void shader_unload(Shader* shader);
void shader_bind(Shader* shader); 

void shader_upload_int(const Shader* shader, const std::string& name, const i32 value);
void shader_upload_float(Shader* shader, const std::string& name, const f32 value);

void shader_upload_mat4(Shader* shader, const std::string& name, const glm::mat4& value);
void shader_upload_vec4(Shader* shader, const std::string& name, const glm::vec4& value);
void shader_upload_vec3(Shader* shader, const std::string& name, const glm::vec3& value);
/////////////////////////////////////////////////////////////////////////////////
