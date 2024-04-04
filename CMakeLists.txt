cmake_minimum_required(VERSION 3.27)
project(CubeRun)

set(PROJ_SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${PROJ_SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE NO_DEFS)
target_compile_options(${PROJECT_NAME} PRIVATE -lm -Wall)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
