#pragma once

#include "engine/core/window.h"

#include <glm/vec2.hpp>

// UIAnchor
/////////////////////////////////////////////////////////////////////////////////
enum UIAnchor {
  UI_ANC_TOP_LEFT, 
  UI_ANC_TOP_CENTER,
  UI_ANC_TOP_RIGHT, 
  
  UI_ANC_CENTER_LEFT, 
  UI_ANC_CENTER,
  UI_ANC_CENTER_RIGHT, 
  
  UI_ANC_BOTTOM_LEFT, 
  UI_ANC_BOTTOM_CENTER,
  UI_ANC_BOTTOM_RIGHT, 
};
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
inline const glm::vec2 ui_anchor_get_position(UIAnchor anchor, const glm::vec2& element_size, const glm::vec2& offset) {
  glm::vec2 window_size = window_get_size();  
  glm::vec2 pos(1.0f);

  // The space between the ui elements and the edges of the screen
  glm::vec2 margin(30.0f, 10.0f);

  // COLOMN
  //////////////////////////////////////////////////////////////////////
  switch(anchor) {
    case UI_ANC_TOP_LEFT:
    case UI_ANC_CENTER_LEFT:
    case UI_ANC_BOTTOM_LEFT:
      pos.x = margin.x + offset.x;
      break;
    case UI_ANC_TOP_CENTER:
    case UI_ANC_CENTER:
    case UI_ANC_BOTTOM_CENTER: 
      pos.x = ((window_size.x - element_size.x) / 2.0f) + offset.x;
      break;
    case UI_ANC_TOP_RIGHT:
    case UI_ANC_CENTER_RIGHT:
    case UI_ANC_BOTTOM_RIGHT: 
      pos.x = (window_size.x - element_size.x - 30.0f) + offset.x;
      break;
  }
  //////////////////////////////////////////////////////////////////////
 
  // ROW
  //////////////////////////////////////////////////////////////////////
  switch(anchor) {
    case UI_ANC_TOP_LEFT:
    case UI_ANC_TOP_CENTER:
    case UI_ANC_TOP_RIGHT:
      pos.y = margin.y + offset.y;
      break;
    case UI_ANC_CENTER_LEFT:
    case UI_ANC_CENTER:
    case UI_ANC_CENTER_RIGHT: 
      pos.y = ((window_size.y - element_size.y) / 2.0f) + offset.y;
      break;
    case UI_ANC_BOTTOM_LEFT:
    case UI_ANC_BOTTOM_CENTER:
    case UI_ANC_BOTTOM_RIGHT: 
      pos.y = (window_size.y - 30.0f) + offset.y;
      break;
  }
  //////////////////////////////////////////////////////////////////////

  return pos;
}
/////////////////////////////////////////////////////////////////////////////////
