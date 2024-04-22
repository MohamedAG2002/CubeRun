#pragma once

#include "engine/graphics/camera.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/font.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create();
void renderer_destroy();
void renderer_clear(const glm::vec4& color);
void renderer_begin(const Camera& cam = Camera{});
void renderer_end();
void renderer_present();

const Font* renderer_default_font();

void render_text(const std::string& text, const f32 size, const glm::vec2& position, const glm::vec4& color);
void render_mesh(Mesh* mesh, const glm::vec3& pos, const glm::vec3 scale, const glm::vec4& color);
/////////////////////////////////////////////////////////////////////////////////
