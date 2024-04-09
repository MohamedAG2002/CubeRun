#pragma once

#include "engine/graphics/camera.h"

// TEMP
struct Mesh;

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create();
void renderer_destroy();
void renderer_begin(const Camera& cam = Camera{});
void renderer_end();
void render_mesh(const Mesh* mesh);
/////////////////////////////////////////////////////////////////////////////////
