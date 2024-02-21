#include "graphics/shader.h"
#include "core/defines.h"

#include <glad/gl.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>

// Shader source type
///////////////////////////////////////////////////////
struct shader_src_t 
{
  std::string vert_src, frag_src;
};
///////////////////////////////////////////////////////

// Private functions
///////////////////////////////////////////////////////
static shader_src_t read_shader(const char* path)
{
  std::string str;
  std::fstream file(path, std::ios::in);
  shader_src_t src{};

  if(!file.is_open())
  {
    printf("ERROR: Failed to read shader at \'%s\'\n", path);
    return shader_src_t{};
  }

  // Get the size of the file and resize the result string accordingly
  file.seekg(0, std::ios::end);
  str.resize(file.tellg());

  // Start from the beginning again
  file.seekg(std::ios::beg);

  // Read the contents of the file into the string and close the file afterwards
  file.read(&str[0], str.size());
  file.close();

  usizei vert_iden_size = strlen("@type vertex");
  usizei frag_iden_size = strlen("@type fragment");
  usizei vert_pos = str.find("@type vertex");
  usizei frag_pos = str.find("@type fragment");

  // No vertex identifier found
  if(vert_pos == std::string::npos)
    printf("ERROR: No vertex identifier found in shader \'%s\'", path);

  // No fragment identifier found
  if(frag_pos == std::string::npos)
    printf("ERROR: No fragment identifier found in shader \'%s\'", path);

  src.vert_src = str.substr(vert_pos + vert_iden_size, frag_pos - vert_iden_size);
  src.frag_src = str.substr(frag_pos + frag_iden_size);

  return src;
}

static void check_compile_error(const u32 shader_id)
{
  int success;
  char log_info[512];

  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success); 

  if(!success) 
  {
    glGetShaderInfoLog(shader_id, 512, nullptr, log_info);
    printf("[SHADER-ERROR]: %s\n", log_info);
  }
}

static void check_linker_error(const shader_t& shader)
{
  int success;
  char log_info[512];

  glGetProgramiv(shader.program, GL_COMPILE_STATUS, &success); 

  if(!success) 
  {
    glGetProgramInfoLog(shader.program, 512, nullptr, log_info);
    printf("[SHADER-ERROR]: %s\n", log_info);
  }
}

static unsigned int get_uniform_location(const shader_t& shader, const char* name)
{
  u32 uni_loc = 0;

  uni_loc = glGetUniformLocation(shader.program, name);
  if(uni_loc == -1)
    printf("ERROR: Could not find variable \'%s\' in the shader\n", name);

  return uni_loc;
}
///////////////////////////////////////////////////////

// Shader functions
///////////////////////////////////////////////////////
shader_t shader_load(const char* path)
{
  shader_t shdr{};
  shader_src_t sources = read_shader(path);

  // Vertex shader
  const char* vert_src = sources.vert_src.c_str(); 
  shdr.vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shdr.vert, 1, &vert_src, 0);
  glCompileShader(shdr.vert);
  check_compile_error(shdr.vert);

  // Fragment shader
  const char* frag_src = sources.frag_src.c_str(); 
  shdr.frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shdr.frag, 1, &frag_src, 0);
  glCompileShader(shdr.frag);
  check_compile_error(shdr.frag);

  // Program linking
  shdr.program = glCreateProgram();
  glAttachShader(shdr.program, shdr.vert);
  glAttachShader(shdr.program, shdr.frag);
  glLinkProgram(shdr.program);
  check_linker_error(shdr);

  // Deleting the vertex and fragment shaders since we already used its data
  glDetachShader(shdr.program, shdr.vert);
  glDetachShader(shdr.program, shdr.frag);
  glDeleteShader(shdr.vert);
  glDeleteShader(shdr.frag);

  return shdr;
}

void shader_unload(shader_t& shader)
{
  glDeleteProgram(shader.program);
}

void shader_bind(const shader_t& shader)
{
  glUseProgram(shader.program);  
}

void shader_upload_vec4(const shader_t& shader, const char* name, const glm::vec4& value)
{
  glUniform4f(get_uniform_location(shader, name), value.x, value.y, value.z, value.w);
}

void shader_upload_mat4(const shader_t& shader, const char* name, const glm::mat4& value)
{
  glUniformMatrix4fv(get_uniform_location(shader, name), 1, GL_FALSE, glm::value_ptr(value));
}
///////////////////////////////////////////////////////
