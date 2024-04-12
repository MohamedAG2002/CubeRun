#include "shader.h"
#include "engine/defines.h"

#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glad/gl.h>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void read_shader(const std::string& path, Shader* shader) {
  std::ifstream file(path);
  std::stringstream ss;

  if(!file.is_open()) {
    printf("[ERROR]: Failed to open a shader at \'%s\'\n", path.c_str());
    return;
  }

  // Get the name of the shader from the path 
  shader->name = path.substr(path.find_last_of('/') + 1);

  ss << file.rdbuf();
  file.close();

  std::string str = ss.str();
  usizei vert_iden_pos = str.find("@type vertex"); 
  usizei frag_iden_pos = str.find("@type fragment");

  if(vert_iden_pos == str.npos) {
    printf("[ERROR]: No vertex identifier found in shader \'%s\'\n", path.c_str());
    shader->vert_src = "";
  }
  if(frag_iden_pos == str.npos) {
    printf("[ERROR]: No fragment identifier found in shader \'%s\'\n", path.c_str());
    shader->frag_src = "";
  }

  usizei vert_iden_size = strlen("@type vertex");
  usizei frag_iden_size = strlen("@type fragment");
  shader->vert_src = str.substr(vert_iden_pos + vert_iden_size, frag_iden_pos - vert_iden_size);
  shader->frag_src = str.substr(frag_iden_pos + frag_iden_size);
}

static void check_compile_error(const u32 shader_id) {
  int success;
  char log_info[512];

  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success); 

  if(!success) {
    glGetShaderInfoLog(shader_id, 512, nullptr, log_info);
    printf("[SHADER-ERROR]: %s\n", log_info);
  }
}

static void check_linker_error(const Shader* shader) {
  int success;
  char log_info[512];

  glGetProgramiv(shader->id, GL_COMPILE_STATUS, &success); 

  if(!success) {
    glGetProgramInfoLog(shader->id, 512, nullptr, log_info);
    printf("[SHADER-ERROR]: %s\n", log_info);
  }
}

static unsigned int get_uniform_location(const Shader* shader, const std::string& name) {
  u32 uni_loc = 0;

  uni_loc = glGetUniformLocation(shader->id, name.c_str());
  if(uni_loc == -1) {
    printf("[SHADER-ERROR]: Could not find variable \'%s\' in shader \'%s\'\n", name.c_str(), shader->name.c_str());
  }

  return uni_loc;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Shader* shader_load(const std::string path) {
  Shader* shader = new Shader{};
  read_shader(path, shader);
 
  // Vertex shader
  const char* vert_src = shader->vert_src.c_str(); 
  shader->vert_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader->vert_id, 1, &vert_src, 0);
  glCompileShader(shader->vert_id);
  check_compile_error(shader->vert_id);
  
  // Fragment shader
  const char* frag_src = shader->frag_src.c_str();
  shader->frag_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader->frag_id, 1, &frag_src, 0);
  glCompileShader(shader->frag_id);
  check_compile_error(shader->frag_id);

  // Linking 
  shader->id = glCreateProgram();
  glAttachShader(shader->id, shader->vert_id);
  glAttachShader(shader->id, shader->frag_id);
  glLinkProgram(shader->id);
  check_linker_error(shader);

  // Detaching 
  glDetachShader(shader->id, shader->vert_id);
  glDetachShader(shader->id, shader->frag_id);
  glDeleteShader(shader->vert_id);
  glDeleteShader(shader->frag_id);

  return shader;
}

void shader_unload(Shader* shader) {
  glDeleteProgram(shader->id);

  delete shader;
}

void shader_bind(Shader* shader) {
  glUseProgram(shader->id);
}

void shader_upload_int(Shader* shader, const std::string& name, const i32 value) {
  glUniform1i(get_uniform_location(shader, name), value);
}

void shader_upload_float(Shader* shader, const std::string& name, const f32 value) {
  glUniform1f(get_uniform_location(shader, name), value);
}

void shader_upload_mat4(Shader* shader, const std::string& name, const glm::mat4& value) {
  glUniformMatrix4fv(get_uniform_location(shader, name), 1, GL_FALSE, glm::value_ptr(value));
}

void shader_upload_vec4(Shader* shader, const std::string& name, const glm::vec4& value) {
  glUniform4f(get_uniform_location(shader, name), value.x, value.y, value.z, value.w);
}

void shader_upload_vec3(Shader* shader, const std::string& name, const glm::vec3& value) {
  glUniform3f(get_uniform_location(shader, name), value.x, value.y, value.z);
}
/////////////////////////////////////////////////////////////////////////////////
