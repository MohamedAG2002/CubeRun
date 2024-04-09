#pragma once

#include "engine/graphics/camera.h"
#include "engine/graphics/mesh.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
const bool renderer_create();
void renderer_destroy();
void renderer_begin(const Camera& cam = Camera{});
void renderer_end();
void render_mesh(const Mesh* mesh, const glm::vec3& pos, const glm::vec4& color);
/////////////////////////////////////////////////////////////////////////////////
