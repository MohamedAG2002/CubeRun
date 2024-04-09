#include "renderer.h"
#include "engine/core/window.h"
#include "engine/defines.h"
#include "engine/graphics/camera.h"
#include "engine/graphics/shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <cstdio>

// Renderer
/////////////////////////////////////////////////////////////////////////////////
struct Renderer {
  Shader* basic_shader; 

  u32 vao, vbo, ebo;
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

static void setup_buffers() {
  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 
     0.5f, -0.5f, 0.0f, 
     0.5f,  0.5f, 0.0f, 
    -0.5f,  0.5f, 0.0f, 
  };

  u32 indices[] = {
    0, 1, 2, 
    2, 3, 0,
  };

  glGenVertexArrays(1, &renderer.vao);
  glBindVertexArray(renderer.vao);

  glGenBuffers(1, &renderer.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glGenBuffers(1, &renderer.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);

  glBindVertexArray(0);
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create() {
  if(!gl_init()) {
    return false;
  }

  setup_buffers();
  renderer.basic_shader = shader_load("assets/shaders/basic.glsl");
  return true;
}

void renderer_destroy() {
  shader_unload(renderer.basic_shader);
}

void renderer_begin(const Camera& cam) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  shader_bind(renderer.basic_shader);
}

void renderer_end() {
  window_swap_buffers();
}

void render_mesh(const Mesh* mesh, const glm::vec3& pos, const glm::vec4& color) {
  glBindVertexArray(mesh->vao);
  glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
}
/////////////////////////////////////////////////////////////////////////////////
