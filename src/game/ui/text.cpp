#include "text.h"
#include "engine/core/clock.h"
#include "engine/defines.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/font.h"
#include "game/ui/ui_anchor.h"

#include <glm/glm.hpp>

#include <cmath>
#include <string>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static const glm::vec2 calc_size(UIText& text) {
  glm::vec2 size(1.0f); 

  const Font* font = renderer_default_font();
  for(u32 i = 0; i < text.str.size(); i++) {
    Glyph glyph = font->glyphs[i];  

    size.x += glyph.size.x * text.font_size;
    size.y += (glyph.size.y - glyph.bearing.y) * text.font_size;
  }

  return size;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
UIText ui_text_create(const std::string& text, const f32 size, const UIAnchor anchor, const glm::vec4& color, const glm::vec2& offset) {
  UIText txt; 
  txt.str = text; 
  txt.font_size = size; 
  txt.size = calc_size(txt);
  txt.offset = offset;
  txt.position = ui_anchor_get_position(anchor, txt.size, offset); 
  txt.color = color;
  txt.anchor = anchor;

  return txt;
}

void ui_text_change(UIText& text, const std::string& new_str) {
  text.str = new_str;
  text.size = calc_size(text);
}

void ui_text_render(const UIText& text) {
  render_text(text.str, text.font_size, text.position, text.color); 
}

void ui_text_fade_in(UIText& text) {
  if(text.color.a >= 1.0f) {
    return;
  }

  text.color.a = std::lerp(text.color.a, 1.0f, crclock_delta_time());
}
/////////////////////////////////////////////////////////////////////////////////
