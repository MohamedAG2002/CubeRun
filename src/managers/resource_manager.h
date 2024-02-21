#pragma once

#include "graphics/mesh.h"

#include <string>

// Resource manager functions
/////////////////////////////////////////////////
void resource_manager_init();
void resource_manager_shutdown();

const mesh_t* resource_get_mesh(const std::string& id);
// const font_t* resource_get_font();
// const audio_t* resource_get_audio(const char* id);
/////////////////////////////////////////////////
