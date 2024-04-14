#include "renderer.h"
#include "engine/core/window.h"
#include "engine/defines.h"
#include "engine/graphics/camera.h"
#include "engine/graphics/shader.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <string>
#include <cstdio>

// Defines
/////////////////////////////////////////////////////////////////////////////////
#define MODELS_MAX 400
/////////////////////////////////////////////////////////////////////////////////

// ShaderType
/////////////////////////////////////////////////////////////////////////////////
enum ShaderType {
  SHADER_BASIC = 0, 
  SHADER_CAMERA, 
  SHADERS_MAX = 2,
};
/////////////////////////////////////////////////////////////////////////////////

// Renderer
/////////////////////////////////////////////////////////////////////////////////
struct Renderer {
  Shader* shaders[SHADERS_MAX];
  Shader* current_shader;
};

static Renderer renderer;
/////////////////////////////////////////////////////////////////////////////////

// Private functions
/////////////////////////////////////////////////////////////////////////////////
bool gl_init() {
  // Loading GLAD
  if(!gladLoadGL(glfwGetProcAddress)) {
    printf("[ERROR]: Failed to initialize GLAD\n");
    return false;
  }
  else {
    window_set_current_context();
  }

  // Setting the GL viewport size
  glm::vec2 win_size = window_get_size();
  glViewport(0, 0, win_size.x, win_size.y);
 
  // Setting options
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create() {
  if(!gl_init()) {
    return false;
  }

  renderer.shaders[SHADER_BASIC]  = shader_load("assets/shaders/basic.glsl");
  renderer.shaders[SHADER_CAMERA] = shader_load("assets/shaders/camera.glsl");
  renderer.current_shader         = renderer.shaders[SHADER_CAMERA];
  
  return true;
}

void renderer_destroy() {
  for(u32 i = 0; i < SHADERS_MAX; i++) {
    shader_unload(renderer.shaders[i]);
  }
}

void renderer_clear(const glm::vec4& color) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(color.r, color.g, color.b, color.a);
}

void renderer_begin(const Camera& cam) {
  shader_bind(renderer.current_shader);
  shader_upload_mat4(renderer.current_shader, "u_view_projection", cam.view_projection);
}

void renderer_end() {
  // @TODO: Add behaviour later for instances
}

void renderer_present() {
  window_swap_buffers();
}

void render_mesh(const Mesh* mesh, const glm::vec3& pos, const glm::vec4& color) {
  glm::mat4 model = glm::mat4(1.0f); 
  model           = glm::translate(model, pos) * 
                    glm::rotate(model, 0.0f, glm::vec3(1.0f)) * 
                    glm::scale(model, glm::vec3(1.0f));
  
  shader_upload_mat4(renderer.current_shader, "u_model", model);
  shader_upload_vec4(renderer.current_shader, "u_color", color);

  glBindVertexArray(mesh->vao);
  glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
}
/////////////////////////////////////////////////////////////////////////////////
