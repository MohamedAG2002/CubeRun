#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"

#include "core/window.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

// Renderer struct 
/////////////////////////////////////////////////////////////
struct renderer_t 
{
  shader_t shader;
};

static renderer_t ren{};
/////////////////////////////////////////////////////////////

// Renderer functions
/////////////////////////////////////////////////////////////
void renderer_create()
{ 
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  // Shaders init 
  ren.shader = shader_load("assets/shaders/shader.glsl");  
}

void renderer_destroy()
{
  shader_unload(ren.shader);
}

void renderer_clear(const glm::vec4& color)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(color.r, color.g, color.b, color.a);
}

void renderer_begin(const camera_t& cam)
{
  shader_bind(ren.shader);
  shader_upload_mat4(ren.shader, "u_view_proj", cam.view_projection);
}

void renderer_end()
{
  window_swap_buffers(); 
}

void render_mesh(const mesh_t* mesh, const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
{
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::scale(model, scale);

  shader_bind(ren.shader);
  shader_upload_vec4(ren.shader, "u_color", color);
  shader_upload_mat4(ren.shader, "u_model", model);

  glBindVertexArray(mesh->vao_id);
  glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
}
/////////////////////////////////////////////////////////////
