#pragma once

#include "graphics/mesh.h"
#include "graphics/camera.h"

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

// Renderer functions
/////////////////////////////////////////////////////////////
void renderer_create();
void renderer_destroy();
void renderer_clear(const glm::vec4& color);
void renderer_begin(const camera& cam);
void renderer_end();

void render_mesh(const mesh_t* mesh, const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);
/////////////////////////////////////////////////////////////
