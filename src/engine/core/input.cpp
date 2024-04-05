#include "input.h"
#include "engine/defines.h"
#include "engine/core/event.h"

#include <glm/vec2.hpp>

#include <string.h>

// InputState
/////////////////////////////////////////////////////////////////////////////////
struct InputState {
  bool key_prev_state[KEYS_MAX];
  bool key_curr_state[KEYS_MAX];
  
  bool mouse_prev_state[BUTTONS_MAX];
  bool mouse_curr_state[BUTTONS_MAX];

  glm::vec2 mouse_pos;
};

static InputState state;
/////////////////////////////////////////////////////////////////////////////////

// Callbacks
/////////////////////////////////////////////////////////////////////////////////
bool mouse_move_callback(const EventType type, const EventDesc& desc) {
  if(type != EVENT_MOUSE_MOVED) {
    return false;
  } 

  state.mouse_pos = desc.mouse_pos;
  return true;
}

bool key_input_callback(const EventType type, const EventDesc& desc) {
  if(type == EVENT_KEY_PRESSED)
  {
    state.key_curr_state[desc.key_pressed] = true;
    return true;
  }
  else if(type == EVENT_KEY_RELEASED)
  {
    state.key_curr_state[desc.key_released] = false;
    return true;
  }

  return false;
}

bool mouse_input_callback(const EventType type, const EventDesc& desc) {
  if(type == EVENT_MOUSE_BUTTON_PRESSED)
  {
    state.mouse_curr_state[desc.button_pressed] = true;
    return true;
  }
  else if(type == EVENT_MOUSE_BUTTON_RELEASED)
  {
    state.mouse_curr_state[desc.button_released] = false;
    return true;
  }

  return false;
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void input_init() {
  event_listen(EVENT_KEY_PRESSED, key_input_callback);
  event_listen(EVENT_KEY_RELEASED, key_input_callback);
  event_listen(EVENT_MOUSE_BUTTON_PRESSED, mouse_input_callback);
  event_listen(EVENT_MOUSE_BUTTON_RELEASED, mouse_input_callback);
  event_listen(EVENT_MOUSE_MOVED, mouse_move_callback);
}

void input_update() {
  memcpy(state.key_prev_state, state.key_curr_state, sizeof(state.key_prev_state));
  memcpy(state.mouse_prev_state, state.mouse_curr_state, sizeof(state.mouse_prev_state));
}

bool input_key_down(const KeyCode key) {
  return state.key_curr_state[key];
}

bool input_key_up(const KeyCode key) {
  return !state.key_curr_state[key];
}

bool input_key_pressed(const KeyCode key) {
  return !state.key_prev_state[key] && state.key_curr_state[key];  
}

bool input_key_released(const KeyCode key) {
  return state.key_prev_state[key] && !state.key_curr_state[key];  
}

bool input_button_down(const ButtonCode key) {
  return state.mouse_curr_state[key];
}

bool input_button_up(const ButtonCode key) {
  return state.mouse_curr_state[key];
}

bool input_button_pressed(const ButtonCode key) {
  return !state.mouse_prev_state[key] && state.mouse_curr_state[key];  
}

bool input_button_released(const ButtonCode key) {
  return state.mouse_prev_state[key] && !state.mouse_curr_state[key];  
}

const glm::vec2& input_mouse_pos() {
  return state.mouse_pos;
}

void input_cursor_show(const bool show) {
  event_dispatch(EVENT_CURSOR_CHANGED, EventDesc{.cursor_shown = show});
}
/////////////////////////////////////////////////////////////////////////////////
