cmake_minimum_required(VERSION 3.27)
project(CubeRun)

# Setting variables
############################################################
set(CR_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CR_LIBS_DIR ${CMAKE_SOURCE_DIR}/libs/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
############################################################

# Sub-dirs
############################################################
add_subdirectory(libs/GLFW)
add_subdirectory(libs/glm)
add_subdirectory(libs/freetype)
add_subdirectory(libs/yaml-cpp)
############################################################

# Source
############################################################
set(CR_SOURCES 
  # engine/core
  ${CR_SRC_DIR}/main.cpp
  ${CR_SRC_DIR}/engine/core/window.cpp
  ${CR_SRC_DIR}/engine/core/clock.cpp
  ${CR_SRC_DIR}/engine/core/event.cpp
  ${CR_SRC_DIR}/engine/core/input.cpp

  # engine/editor
  ${CR_SRC_DIR}/editor/editor.cpp
  
  # engine/graphics
  ${CR_SRC_DIR}/engine/graphics/renderer.cpp
  ${CR_SRC_DIR}/engine/graphics/shader.cpp
  ${CR_SRC_DIR}/engine/graphics/mesh.cpp
  ${CR_SRC_DIR}/engine/graphics/camera.cpp
  ${CR_SRC_DIR}/engine/graphics/font.cpp
  ${CR_SRC_DIR}/engine/graphics/texture.cpp
  
  # engine/audio
  ${CR_SRC_DIR}/engine/audio/audio_system.cpp
  
  # game/
  ${CR_SRC_DIR}/game/game.cpp
  
  # game/ui
  ${CR_SRC_DIR}/game/ui/text.cpp
  
  # game/scenes
  ${CR_SRC_DIR}/game/scenes/scene_manager.cpp
  ${CR_SRC_DIR}/game/scenes/menu_overlay.cpp
  ${CR_SRC_DIR}/game/scenes/over_overlay.cpp
  ${CR_SRC_DIR}/game/scenes/game_scene.cpp
  ${CR_SRC_DIR}/game/scenes/serializer.cpp
  
  # game/entities
  ${CR_SRC_DIR}/game/entities/entity_manager.cpp
  ${CR_SRC_DIR}/game/entities/player.cpp
  
  # game/physics
  ${CR_SRC_DIR}/game/physics/collider.cpp
  ${CR_SRC_DIR}/game/physics/physics_world.cpp
)
############################################################

# Libs sources
############################################################
set(LIBS_SOURCE 
  ${CR_LIBS_DIR}/glad/gl.c

  ${CR_LIBS_DIR}/ImGui/imgui.cpp
  ${CR_LIBS_DIR}/ImGui/imgui_demo.cpp
  ${CR_LIBS_DIR}/ImGui/imgui_draw.cpp
  ${CR_LIBS_DIR}/ImGui/imgui_tables.cpp
  ${CR_LIBS_DIR}/ImGui/imgui_widgets.cpp
  
  ${CR_LIBS_DIR}/ImGui/backends/imgui_impl_opengl3.cpp
  ${CR_LIBS_DIR}/ImGui/backends/imgui_impl_glfw.cpp
  
  ${CR_LIBS_DIR}/miniaudio/miniaudio.cpp
  ${CR_LIBS_DIR}/stb_image/stb_image.cpp
)
############################################################

# Linking and compiling
############################################################
add_executable(${PROJECT_NAME} ${CR_SOURCES} ${LIBS_SOURCE})

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE EDITOR_ACTIVE)
target_compile_options(${PROJECT_NAME} PRIVATE -lm -O1)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC ${CR_SRC_DIR}/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CR_LIBS_DIR}/)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm freetype yaml-cpp)
############################################################
