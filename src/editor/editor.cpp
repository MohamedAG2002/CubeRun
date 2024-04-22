#include "editor.h"
#include "engine/core/window.h"
#include "game/entities/entity_manager.h"

#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>
#include <ImGui/backends/imgui_impl_opengl3_loader.h>

#include <cstdio>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool editor_init() {
#ifdef EDITOR_ACTIVE
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  
  ImGuiIO io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
 
  if(!ImGui_ImplGlfw_InitForOpenGL(window_get_handle(), true)) {
    printf("[ERROR]: ImGui-GLFW failed to init\n");
    return false;
  }
  
  if(!ImGui_ImplOpenGL3_Init("#version 460 core")) {
    printf("[ERROR]: ImGui-GL failed to init\n");
    return false;
  }
#endif

  return true;
}

void editor_shutdown() {
#ifdef EDITOR_ACTIVE
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
#endif
}

void editor_begin() {
#ifdef EDITOR_ACTIVE
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
#endif
}

void editor_end() {
#ifdef EDITOR_ACTIVE
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void editor_entities(EntityManager* entities) {
#ifdef EDITOR_ACTIVE
  ImGui::Begin("Entities");

  // Player settings 
  ImGui::SeparatorText("Player");
  ImGui::SliderFloat3("Position", &entities->player.position.x, -100.0f, 100.0f);
  ImGui::SliderFloat3("Scale", &entities->player.scale.x, -10.0f, 10.0f);
  ImGui::SliderFloat3("Velocity", &entities->player.velocity.x, -100.0f, 100.0f);
  ImGui::ColorEdit4("Color", &entities->player.color.r);

  // Platform settings 
  ImGui::SeparatorText("Platforms");
  ImGui::SliderFloat3("Position", &entities->player.position.x, -100.0f, 100.0f);
  ImGui::SliderFloat3("Scale", &entities->player.scale.x, -10.0f, 10.0f);
  ImGui::SliderFloat3("Velocity", &entities->player.velocity.x, -100.0f, 100.0f);
  ImGui::ColorEdit4("Color", &entities->player.color.r);
  
  ImGui::End();
#endif
}
/////////////////////////////////////////////////////////////////////////////////
