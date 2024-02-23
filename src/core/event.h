#pragma once

#include "defines.h"
#include "scenes/scene_type.h"

#include <glm/vec2.hpp>

#include <string>

// Event type enum
////////////////////////////////////////////////
enum event_type_e 
{
  EVENT_KEY_PRESSED  = 0x01, 
  EVENT_KEY_RELEASED = 0x02, 
  
  EVENT_BUTTON_PRESSED  = 0x03, 
  EVENT_BUTTON_RELEASED = 0x04,

  EVENT_MOUSE_MOVED    = 0x05, 
  EVENT_WINDOW_RESIZED = 0x06,

  EVENT_GAME_CLOSED = 0x07,

  EVENT_SCENE_CHANGED = 0x08,

  EVENT_AUDIO_PLAYED  = 0x09,
  EVENT_AUDIO_STOPPED = 0x10,
  EVENT_AUDIO_PAUSED  = 0x11,
};
////////////////////////////////////////////////

// Event desc struct 
////////////////////////////////////////////////
struct event_desc_t 
{
  scene_type_e scene;

  u32 key_pressed, key_released;
  u32 button_pressed, button_released;
  
  glm::vec2 mouse_pos, window_size; 

  std::string sound_id;
};
////////////////////////////////////////////////

// Event function pointer
////////////////////////////////////////////////
typedef b8(*pfn_event_callback)(const event_type_e, const event_desc_t&);
////////////////////////////////////////////////

// Event functions
////////////////////////////////////////////////
void event_shutdown();
void event_listen(const event_type_e type, pfn_event_callback callback);
void event_dispatch(const event_type_e& type, const event_desc_t& event);
////////////////////////////////////////////////
