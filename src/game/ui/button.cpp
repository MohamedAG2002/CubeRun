#include "button.h"
#include "engine/graphics/renderer2d.h"
#include "engine/core/input.h"
#include "game/ui/ui_anchor.h"
#include "game/ui/text.h"

#include <glm/glm.hpp>

#include <string>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
const bool check_mouse_button_collision(const UIButton& button) {
  glm::vec2 mouse_pos = input_mouse_pos();

  return true;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
UIButton ui_button_create(const std::string& text, const UIAnchor anchor, const glm::vec2& offset) {
  UIButton button; 
  button.text = ui_text_create(text, 0.5f, anchor, glm::vec4(0, 0, 0, 1), offset);
  button.size = glm::vec2(button.text.size.x + 20.0f, 40.0f);
  button.offset = offset;
  button.position = button.text.position;
  button.color = glm::vec4(1.0f);
  button.is_active = true;
  button.anchor = anchor;

  button.position.x += (button.text.size.x + 5.0f) / 2.0f;
  button.position.y += 10.0f; 

  return button;
}

const bool ui_button_clicked(UIButton& button) {

  return true;
}

void ui_button_render(UIButton& button) {
  render_quad(button.position, button.size, button.color);
  ui_text_render(button.text);
}
/////////////////////////////////////////////////////////////////////////////////
