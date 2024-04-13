#pragma once

#include "engine/graphics/camera.h"
#include "engine/graphics/mesh.h"
#include "engine/graphics/font.h"

#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create();
void renderer_destroy();
void renderer_begin(const Camera& cam = Camera{});
void renderer_end();
const Font* renderer_default_font();
void render_mesh(const Mesh* mesh, const glm::vec3& pos, const glm::vec4& color);
void render_text(const Font* font, const std::string& text, const f32 size, glm::vec2& pos, const glm::vec4& color);
/////////////////////////////////////////////////////////////////////////////////
