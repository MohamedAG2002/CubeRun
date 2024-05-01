#include "over_overlay.h"
#include "engine/core/event.h"
#include "game/scenes/scene_overlay.h"
#include "game/ui/text.h"
#include "engine/core/input.h"

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void over_overlay_create(SceneOverlay* overlay) {
  overlay->type = OVERLAY_OVER;
  overlay->is_active = true;

  overlay->texts.push_back(ui_text_create("The run has ended...", 0.7f, UI_ANC_TOP_CENTER, glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
  overlay->texts.push_back(ui_text_create("Press [SPACE] to start a new run", 0.5f, UI_ANC_CENTER, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));
  overlay->texts.push_back(ui_text_create("[M] MENU", 0.5f, UI_ANC_BOTTOM_LEFT, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));

  overlay->create  = over_overlay_create;
  overlay->destroy = over_overlay_destroy;
  overlay->update  = over_overlay_update;
  overlay->render  = over_overlay_render;
}

void over_overlay_destroy(SceneOverlay* overlay) {
  overlay->texts.clear();
}

void over_overlay_update(SceneOverlay* overlay) {
  if(input_key_pressed(KEY_SPACE)) {
    overlay->is_active = false;
    return;
  }
  else if(input_key_pressed(KEY_M)) {
    event_dispatch(EVENT_OVERLAY_CHANGE, EventDesc{.overlay_type = OVERLAY_MENU});
    return;
  }

  for(auto& text : overlay->texts) {
    ui_text_fade_in(text);
  }
}

void over_overlay_render(SceneOverlay* overlay) {
  for(auto& text : overlay->texts) {
    ui_text_render(text);
  }
}
/////////////////////////////////////////////////////////////////////////////////
