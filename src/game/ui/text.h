#pragma once

#include "engine/defines.h"
#include "game/ui/ui_anchor.h"

#include <glm/glm.hpp>

#include <string>

// UIText
/////////////////////////////////////////////////////////////////////////////////
struct UIText {
  std::string str;
  f32 font_size;
  glm::vec2 position, size, offset;
  glm::vec4 color;
  UIAnchor anchor;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
UIText ui_text_create(const std::string& text, const f32 size, const UIAnchor anchor, const glm::vec4& color, const glm::vec2& offset = glm::vec2(0.0f));
void ui_text_change(UIText& text, const std::string& new_str);
void ui_text_render(const UIText& text);
void ui_text_fade_in(UIText& text);
/////////////////////////////////////////////////////////////////////////////////
