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

#include <cstdio>

// Renderer
/////////////////////////////////////////////////////////////////////////////////
struct Renderer {
  Shader* basic_shader;
  Shader* camera_shader;
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

  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create() {
  if(!gl_init()) {
    return false;
  }

  renderer.basic_shader   = shader_load("assets/shaders/basic.glsl");
  renderer.camera_shader  = shader_load("assets/shaders/camera.glsl");
  renderer.current_shader = renderer.camera_shader;
  return true;
}

void renderer_destroy() {
}

void renderer_begin(const Camera& cam) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  shader_bind(renderer.current_shader);
  shader_upload_mat4(renderer.current_shader, "u_view_projection", cam.view_projection);
}

void renderer_end() {
  window_swap_buffers();
}

void render_mesh(const Mesh* mesh, const glm::vec3& pos, const glm::vec4& color) {
  glm::mat4 model = glm::mat4(1.0f); 
  model           = glm::translate(model, pos) * 
                    glm::rotate(model, 45.0f, glm::vec3(1.0f)) * 
                    glm::scale(model, glm::vec3(1.0f));
  shader_upload_mat4(renderer.current_shader, "u_model", model);

  glBindVertexArray(mesh->vao);
  glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
}
/////////////////////////////////////////////////////////////////////////////////
