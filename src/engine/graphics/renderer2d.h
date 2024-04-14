#pragma once

#include "engine/defines.h"
#include "engine/graphics/font.h"
#include "engine/graphics/texture.h"

#include <glm/glm.hpp>

#include <string>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void renderer2d_create();
void renderer2d_destroy();
void renderer2d_begin();
void renderer2d_end();

void render_text(const std::string& text, const f32 size, glm::vec2& pos, const glm::vec4& color);
void render_text(const Font* font, const std::string& text, const f32 size, glm::vec2& pos, const glm::vec4& color);
void render_quad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
void render_quad(const glm::vec2& pos, const glm::vec2& size, const Texture* texture);
/////////////////////////////////////////////////////////////////////////////////
