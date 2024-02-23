cmake_minimum_required(VERSION 3.27)
project(CubeRun)

# CMake variables
############################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
############################################

# Finding libraries
############################################
find_library(glfw glfw REQUIRED)
############################################

# Project variables
############################################
if(WIN32)
  set(PROJ_COMPILER_FLAGS)
endif(WIN32)

if(UNIX)
  set(PROJ_COMPILER_FLAGS -ldl -lpthread -lm -latomic)
endif(UNIX)

set(PROJ_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROJ_LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)
set(PROJ_SOURCES 
  # Core 
  ${PROJ_SRC_DIR}/main.cpp
  ${PROJ_SRC_DIR}/core/game.cpp
  ${PROJ_SRC_DIR}/core/window.cpp
  ${PROJ_SRC_DIR}/core/event.cpp
  ${PROJ_SRC_DIR}/core/input.cpp

  # Graphics
  ${PROJ_SRC_DIR}/graphics/shader.cpp
  ${PROJ_SRC_DIR}/graphics/renderer.cpp
  ${PROJ_SRC_DIR}/graphics/mesh.cpp
  ${PROJ_SRC_DIR}/graphics/camera.cpp
  
  # Managers
  ${PROJ_SRC_DIR}/managers/scene_manager.cpp
  ${PROJ_SRC_DIR}/managers/resource_manager.cpp
  ${PROJ_SRC_DIR}/managers/audio_manager.cpp

  # Scenes
  ${PROJ_SRC_DIR}/scenes/game_scene.cpp
  
  # Entities
  ${PROJ_SRC_DIR}/entities/player.cpp
  ${PROJ_SRC_DIR}/entities/platform.cpp

  # Utils
  ${PROJ_SRC_DIR}/utils/utils.cpp
)

set(LIBS_SOURCES
  ${PROJ_LIBS_DIR}/src/glad/gl.c
  ${PROJ_LIBS_DIR}/src/miniaudio/miniaudio.cpp
)
############################################

# Creating the executable and configuring it
############################################
add_executable(${PROJECT_NAME} ${PROJ_SOURCES} ${LIBS_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(${PROJECT_NAME} PRIVATE ${PROJ_COMPILER_FLAGS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
############################################

# Linking 
############################################
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} BEFORE PUBLIC ${PROJ_SRC_DIR})
target_include_directories(${PROJECT_NAME} BEFORE PUBLIC ${PROJ_LIBS_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${glfw})
############################################
