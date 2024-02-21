#include "input.h"
#include "defines.h"
#include "event.h"

#include <glm/vec2.hpp>

#include <cstring>

// Key input state
////////////////////////////////////////////////
struct key_state_t
{
  b8 current_state[MAX_KEYS];
  b8 previous_state[MAX_KEYS];
};

struct mouse_state_t 
{
  b8 current_state[MAX_BUTTONS];
  b8 previous_state[MAX_BUTTONS];

  glm::vec2 mouse_pos;
};

static key_state_t s_key = {};
static mouse_state_t s_mouse = {};
////////////////////////////////////////////////

// Callbacks
////////////////////////////////////////////////
b8 key_input_callback(const event_type_e type, const event_desc_t& desc)
{
  if(type == EVENT_KEY_PRESSED)
  {
    s_key.current_state[desc.key_pressed] = true;
    return true;
  }
  else if(type == EVENT_KEY_RELEASED)
  {
    s_key.current_state[desc.key_released] = false;
    return true;
  }

  return false;
}

b8 mouse_input_callback(const event_type_e type, const event_desc_t& desc)
{
  if(type == EVENT_BUTTON_PRESSED)
  {
    s_mouse.current_state[desc.button_pressed] = true;
    return true;
  }
  else if(type == EVENT_BUTTON_RELEASED)
  {
    s_mouse.current_state[desc.button_released] = false;
    return true;
  }

  return false;
}

b8 mouse_move_callback(const event_type_e type, const event_desc_t& desc)
{
  if(type == EVENT_MOUSE_MOVED)
  {
    s_mouse.mouse_pos = desc.mouse_pos;
    return true;
  }

  return false;
}
////////////////////////////////////////////////

// Input functions 
////////////////////////////////////////////////
void input_init()
{
  // Listening  to events 
  event_listen(EVENT_KEY_PRESSED, key_input_callback);
  event_listen(EVENT_KEY_RELEASED, key_input_callback);
  event_listen(EVENT_BUTTON_PRESSED, mouse_input_callback);
  event_listen(EVENT_BUTTON_RELEASED, mouse_input_callback);
  event_listen(EVENT_MOUSE_MOVED, mouse_move_callback);
}

void input_update()
{
  // Update the input states by changing the previous states to the current states
  memcpy(s_key.previous_state, s_key.current_state, sizeof(s_key.current_state));
  memcpy(s_mouse.previous_state, s_mouse.current_state, sizeof(s_mouse.current_state));
}

b8 input_key_down(key_code_e code)
{
  return s_key.current_state[code];
}

b8 input_key_up(key_code_e code)
{
  return !s_key.current_state[code];
}

b8 input_key_pressed(key_code_e code)
{
  return !s_key.previous_state[code] && s_key.current_state[code];
}

b8 input_key_released(key_code_e code)
{
  return s_key.previous_state[code] && !s_key.current_state[code];
}

glm::vec2 input_get_mouse_pos()
{
  return s_mouse.mouse_pos;  
}

b8 input_mouse_down(button_code_e code)    
{
  return s_mouse.current_state[code];
}

b8 input_mouse_up(button_code_e code)      
{
  return !s_mouse.current_state[code];
}

b8 input_mouse_pressed(button_code_e code)
{
  return !s_mouse.previous_state[code] && s_mouse.current_state[code];
}

b8 input_mouse_released(button_code_e code)
{
  return s_mouse.previous_state[code] && !s_mouse.current_state[code];
}
////////////////////////////////////////////////
