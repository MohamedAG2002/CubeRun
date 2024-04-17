#pragma once

#include "game/ui/ui_anchor.h"
#include "game/ui/text.h"

#include <glm/glm.hpp>

#include <string>

// UIButton
/////////////////////////////////////////////////////////////////////////////////
struct UIButton {
  UIText text;
  glm::vec2 position, size, offset;
  glm::vec4 color;
  UIAnchor anchor;
  bool is_active;
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
UIButton ui_button_create(const std::string& text, const UIAnchor anchor, const glm::vec2& offset = glm::vec2(0.0f));
const bool ui_button_clicked(UIButton& button);
void ui_button_render(UIButton& button);
/////////////////////////////////////////////////////////////////////////////////
