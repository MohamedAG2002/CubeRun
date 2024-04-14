#include "renderer2d.h"
#include "engine/defines.h"
#include "engine/core/window.h"
#include "engine/graphics/font.h"
#include "engine/graphics/texture.h"
#include "engine/graphics/shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>

// Globals 
/////////////////////////////////////////////////////////////////////////////////
#define MAX_QUADS    5000
#define MAX_VERTICES MAX_QUADS * 4
#define MAX_INDICES  MAX_QUADS * 6
#define MAX_TEXTURES 32
/////////////////////////////////////////////////////////////////////////////////

// Vertex 
/////////////////////////////////////////////////////////////////////////////////
struct Vertex {
  glm::vec2 position; 
  glm::vec4 color; 
  glm::vec2 texture_coords;
  float texture_index;
};
/////////////////////////////////////////////////////////////////////////////////

// Renderer2D 
/////////////////////////////////////////////////////////////////////////////////
struct Renderer2D {
  Shader* font_shader;
  Shader* batch_shader;

  Font* default_font;

  u32 vao, vbo, ebo; 
 
  std::vector<Vertex> vertices;
  glm::vec4 quad_vertices[4];
  Texture* textures[MAX_TEXTURES];

  usizei texture_index = 1; // Starts at one to skip the white texture
  usizei indices       = 0;
};

static Renderer2D* renderer;
/////////////////////////////////////////////////////////////////////////////////

// Priavte functions
/////////////////////////////////////////////////////////////////////////////////
void setup_buffers() {
  glGenVertexArrays(1, &renderer->vao);
  glBindVertexArray(renderer->vao);

  // Setup VBO
  glGenBuffers(1, &renderer->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERTICES, nullptr, GL_DYNAMIC_DRAW);

  // Fill index buffer
  u32 indices[MAX_INDICES];
  u32 offset = 0; 
  for(u32 i = 0; i < MAX_INDICES; i += 6) {
    indices[i + 0] = 0 + offset;
    indices[i + 1] = 1 + offset;
    indices[i + 2] = 2 + offset;
    
    indices[i + 2] = 2 + offset;
    indices[i + 4] = 3 + offset;
    indices[i + 5] = 0 + offset;

    offset += 4;
  }

  // Setup EBO
  glGenBuffers(1, &renderer->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Setup layouts 
  // Position 
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); 

  // Color 
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color)); 
  
  // Texture coords 
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords)); 
  
  // Texture index
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_index)); 

  glBindVertexArray(0);
}

static void flush() {
  // Render all of the compiled textures 
  for(u32 i = 0; i < renderer->texture_index; i++) {
    texture_render(renderer->textures[i]);
  }

  // Draw the compiled vertices 
  glDrawArrays(GL_TRIANGLES, 0, renderer->indices);

  // Reset the variables for the next pass 
  renderer->texture_index = 1;
  renderer->indices       = 0;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void renderer2d_create() {
  renderer = new Renderer2D{};

  setup_buffers();

  // Shaders init 
  renderer->font_shader  = shader_load("assets/shaders/font.glsl");
  renderer->batch_shader = shader_load("assets/shaders/batch.glsl");

  // White texture init 
  u32 texture = 0xffffffff;
  renderer->textures[0] = texture_load(1, 1, GL_RGBA, &texture);

  // Setting up the samplers in the shader 
  shader_bind(renderer->batch_shader);
  i32 texture_slots[MAX_TEXTURES];
  for(u32 i = 0; i < MAX_TEXTURES; i++) {
    texture_slots[i] = i;
  }
  shader_upload_int_arr(renderer->batch_shader, "textures", texture_slots, MAX_TEXTURES);

  // Font init 
  renderer->default_font = font_load("assets/fonts/HeavyDataNerdFont.ttf", 64);

  // Setup the initial quad vertices to use later 
  renderer->quad_vertices[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
  renderer->quad_vertices[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
  renderer->quad_vertices[2] = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
  renderer->quad_vertices[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);
}

void renderer2d_destroy() {
  font_unload(renderer->default_font);
  shader_unload(renderer->batch_shader);
  shader_unload(renderer->font_shader);

  renderer->vertices.clear();

  delete renderer;
}

void renderer2d_begin() {
  shader_bind(renderer->batch_shader); 
  renderer->vertices.clear();
}

void renderer2d_end() {
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * renderer->vertices.size(), renderer->vertices.data());
  flush();
}

void render_text(const Font* font, const std::string& text, const f32 size, glm::vec2& pos, const glm::vec4& color) {
  glm::vec2 window_size = window_get_size();
  glm::mat4 ortho = glm::ortho(0.0f, window_size.x, 0.0f, window_size.y);
  f32 old_x = pos.x;  
 
  shader_bind(renderer->font_shader);
  shader_upload_mat4(renderer->font_shader, "u_projection", ortho);
  shader_upload_vec4(renderer->font_shader, "u_color", color);

  glBindVertexArray(font->vao);
  glActiveTexture(GL_TEXTURE0);

  std::string::const_iterator it;
  for(it = text.begin(); it != text.end(); it++) {
    Glyph glyph = font->glyphs[*it];

    if(*it == ' ' || *it == '\t') {
      pos.x += (glyph.advance >> 6) * size;
      continue;
    }

    f32 x_pos = pos.x + glyph.bearing.x * size; 
    f32 y_pos = pos.y - (glyph.size.y - glyph.bearing.y) * size; 
    
    f32 width  = (glyph.size.x * size);
    f32 height = (glyph.size.y * size);

    f32 vertices[6][4] = {
      {x_pos,         y_pos + height, 0.0f, 0.0f},
      {x_pos,         y_pos,          0.0f, 1.0f},
      {x_pos + width, y_pos,          1.0f, 1.0f},
      
      {x_pos,         y_pos + height, 0.0f, 0.0f},
      {x_pos + width, y_pos,          1.0f, 1.0f},
      {x_pos + width, y_pos + height, 1.0f, 0.0f},
    };

    glBindTexture(GL_TEXTURE_2D, glyph.ID);
    glBindBuffer(GL_ARRAY_BUFFER, font->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    pos.x += (glyph.advance >> 6) * size;
  }
    
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0); 

  // This is cheating but whatever 
  shader_bind(renderer->batch_shader);
}

void render_text(const std::string& text, const f32 size, glm::vec2& pos, const glm::vec4& color) {
  render_text(renderer->default_font, text, size, pos, color);
}

void render_quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) {
  // Reflush the renderer if the number of indices exceded the maximum 
  if(renderer->indices >= MAX_INDICES) {
    renderer2d_end();
    renderer2d_begin();
  }

  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
  model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));

  // Top-left 
  Vertex v; 
  v.position       = renderer->quad_vertices[0] * model; 
  v.color          = color;
  v.texture_coords = glm::vec2(0.0f, 1.0f);
  v.texture_index  = 0.0f;
  renderer->vertices.push_back(v);
  
  // Top-right 
  v.position       = renderer->quad_vertices[1] * model; 
  v.color          = color;
  v.texture_coords = glm::vec2(1.0f, 1.0f);
  v.texture_index  = 0.0f;
  renderer->vertices.push_back(v);
  
  // Bottom-right 
  v.position       = renderer->quad_vertices[2] * model; 
  v.color          = color;
  v.texture_coords = glm::vec2(1.0f, 0.0f);
  v.texture_index  = 0.0f;
  renderer->vertices.push_back(v);
  
  // Bottom-left 
  v.position       = renderer->quad_vertices[3] * model; 
  v.color          = color;
  v.texture_coords = glm::vec2(0.0f, 0.0f);
  v.texture_index  = 0.0f;
  renderer->vertices.push_back(v);

  // Increase the indices therefore add an extra quad
  renderer->indices += 4;
}

void render_quad(const glm::vec2& pos, const glm::vec2& size, const Texture* texture) {
  // Reflush the renderer if the number of indices exceded the maximum 
  // or if the texture limit has been reached
  if(renderer->indices >= MAX_INDICES || renderer->texture_index > MAX_TEXTURES) {
    renderer2d_end();
    renderer2d_begin();
  }
  
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
  model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));
  
  // Top-left 
  Vertex v; 
  v.position       = renderer->quad_vertices[0] * model; 
  v.color          = glm::vec4(1.0f);
  v.texture_coords = glm::vec2(0.0f, 1.0f);
  v.texture_index  = texture->slot;
  renderer->vertices.push_back(v);
  
  // Top-right 
  v.position       = renderer->quad_vertices[1] * model; 
  v.color          = glm::vec4(1.0f);
  v.texture_coords = glm::vec2(1.0f, 1.0f);
  v.texture_index  = texture->slot;
  renderer->vertices.push_back(v);
  
  // Bottom-right 
  v.position       = renderer->quad_vertices[2] * model; 
  v.color          = glm::vec4(1.0f);
  v.texture_coords = glm::vec2(1.0f, 0.0f);
  v.texture_index  = texture->slot;
  renderer->vertices.push_back(v);
  
  // Bottom-left 
  v.position       = renderer->quad_vertices[3] * model; 
  v.color          = glm::vec4(1.0f);
  v.texture_coords = glm::vec2(0.0f, 0.0f);
  v.texture_index  = texture->slot;
  renderer->vertices.push_back(v);
  
  renderer->indices += 4;

  // Only adding the texture if it's unique and has never been added before 
  bool found = false; 
  for(u32 i = 0; i < renderer->texture_index; i++) {
    if(texture->id == renderer->textures[i]->id) {
      found = true;
      break;
    }
  }

  // Don't render the texture if it was already renderer
  if(found) {
    return;
  }
 
  renderer->textures[renderer->texture_index] = (Texture*)texture;
  renderer->texture_index += 1;
}
/////////////////////////////////////////////////////////////////////////////////
