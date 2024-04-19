#include "menu_overlay.h"
#include "game/scenes/scene_overlay.h"
#include "game/ui/text.h"
#include "engine/core/input.h"

#include <vector>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
void menu_overlay_create(SceneOverlay* overlay) {
  overlay->type = OVERLAY_MENU;
  overlay->is_active = true;

  overlay->texts.push_back(ui_text_create("CUBE RUN", 0.7f, UI_ANC_TOP_CENTER, glm::vec4(1.0f)));
  overlay->texts.push_back(ui_text_create("Press SPACE to play", 0.5f, UI_ANC_CENTER, glm::vec4(1.0f)));
  overlay->texts.push_back(ui_text_create("PB: ", 0.5f, UI_ANC_BOTTOM_LEFT, glm::vec4(1.0f)));

  overlay->create  = menu_overlay_create;
  overlay->destroy = menu_overlay_destroy;
  overlay->update  = menu_overlay_update;
  overlay->render  = menu_overlay_render;
}

void menu_overlay_destroy(SceneOverlay* overlay) {
  overlay->texts.clear();
}

void menu_overlay_update(SceneOverlay* overlay) {
  if(input_key_pressed(KEY_SPACE)) {
    overlay->is_active = false;
    return;
  }
}

void menu_overlay_render(SceneOverlay* overlay) {
  for(auto& text : overlay->texts) {
    ui_text_render(text);
  }
}
/////////////////////////////////////////////////////////////////////////////////
