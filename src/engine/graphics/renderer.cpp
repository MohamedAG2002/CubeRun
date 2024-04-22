#include "renderer.h"
#include "engine/core/window.h"
#include "engine/defines.h"
#include "engine/graphics/camera.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/font.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <string>
#include <cstdio>

// ShaderType
/////////////////////////////////////////////////////////////////////////////////
enum ShaderType {
  SHADER_BASIC = 0, 
  SHADER_CAMERA, 
  SHADER_FONT,
  SHADERS_MAX = 3,
};
/////////////////////////////////////////////////////////////////////////////////

// Renderer
/////////////////////////////////////////////////////////////////////////////////
struct Renderer {
  Shader* shaders[SHADERS_MAX];
  Shader* current_shader;
  Font* font;
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
  renderer.shaders[SHADER_FONT]   = shader_load("assets/shaders/font.glsl");
  renderer.current_shader         = renderer.shaders[SHADER_CAMERA];
 
  renderer.font = font_load("assets/fonts/HeavyDataNerdFont.ttf", 64);

  return true;
}

void renderer_destroy() {
  font_unload(renderer.font);

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

const Font* renderer_default_font() {
  return renderer.font;
}

void render_text(const std::string& text, const f32 size, const glm::vec2& position, const glm::vec4& color) {
  glm::vec2 window_size = window_get_size();
  glm::mat4 ortho = glm::ortho(0.0f, window_size.x, window_size.y, 0.0f);
  glm::vec2 pos = position;
  f32 old_x = pos.x;  

  shader_bind(renderer.shaders[SHADER_FONT]);
  shader_upload_mat4(renderer.shaders[SHADER_FONT], "u_projection", ortho);
  shader_upload_vec4(renderer.shaders[SHADER_FONT], "u_color", color);

  glBindVertexArray(renderer.font->vao);
  glActiveTexture(GL_TEXTURE0);

  std::string::const_iterator it;
  for(it = text.begin(); it != text.end(); it++) {
    Glyph glyph = renderer.font->glyphs[*it];

    if(*it == ' ' || *it == '\t') {
      pos.x += (glyph.advance >> 6) * size;
      continue;
    }

    f32 x_pos = pos.x + glyph.bearing.x * size; 
    f32 y_pos = pos.y - (glyph.size.y - glyph.bearing.y) * size; 
    
    f32 width  = (glyph.size.x * size);
    f32 height = (glyph.size.y * size);

    f32 vertices[6][4] = {
      {x_pos,         y_pos + height, 0.0f, 1.0f},
      {x_pos,         y_pos,          0.0f, 0.0f},
      {x_pos + width, y_pos,          1.0f, 0.0f},
      
      {x_pos,         y_pos + height, 0.0f, 1.0f},
      {x_pos + width, y_pos,          1.0f, 0.0f},
      {x_pos + width, y_pos + height, 1.0f, 1.0f},
    };

    glBindTexture(GL_TEXTURE_2D, glyph.ID);
    glBindBuffer(GL_ARRAY_BUFFER, renderer.font->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    pos.x += (glyph.advance >> 6) * size;
  }
    
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0); 

  // This is cheating but whatever 
  shader_bind(renderer.shaders[SHADER_CAMERA]);
}

void render_mesh(Mesh* mesh, const glm::vec3& pos, const glm::vec3 scale, const glm::vec4& color) {
  glm::mat4 model = glm::mat4(1.0f); 
  model           = glm::translate(model, pos) * 
                    glm::rotate(model, 0.0f, glm::vec3(1.0f)) * 
                    glm::scale(model, scale);

  // Transforming the min/max of the mesh into model space 
  glm::vec4 min = model * glm::vec4(mesh->min, 1.0f);
  glm::vec4 max = model * glm::vec4(mesh->max, 1.0f);
 
  mesh->min = glm::vec3(min);
  mesh->max = glm::vec3(max);

  shader_upload_mat4(renderer.current_shader, "u_model", model);
  shader_upload_vec4(renderer.current_shader, "u_color", color);

  glBindVertexArray(mesh->vao);
  glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
}
/////////////////////////////////////////////////////////////////////////////////
