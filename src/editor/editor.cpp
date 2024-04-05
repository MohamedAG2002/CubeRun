#include "editor.h"
#include "engine/core/window.h"

#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>
#include <ImGui/backends/imgui_impl_opengl3_loader.h>

#include <cstdio>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool editor_init() {
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

  return true;
}

void editor_shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void editor_begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::ShowDemoWindow();
}

void editor_end() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
/////////////////////////////////////////////////////////////////////////////////
