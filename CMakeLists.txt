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
  ${CR_SRC_DIR}/engine/core/game.cpp
)
############################################################

# Libs sources
############################################################
set(LIBS_SOURCE 
  ${CR_LIBS_DIR}/glad/gl.c
)
############################################################

# Linking and compiling
############################################################
add_executable(${PROJECT_NAME} ${CR_SOURCES} ${LIBS_SOURCE})

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)
target_compile_options(${PROJECT_NAME} PRIVATE -lm)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC ${CR_SRC_DIR}/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CR_LIBS_DIR}/)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm)
############################################################
