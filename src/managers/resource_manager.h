#pragma once

#include "graphics/mesh.h"

#include <miniaudio/miniaudio.h>

#include <string>

// Resource manager functions
/////////////////////////////////////////////////
void resource_manager_init();
void resource_manager_shutdown();

const mesh_t* resource_get_mesh(const std::string& id);
// const font_t* resource_get_font();
ma_sound& resource_get_audio(const std::string id);
/////////////////////////////////////////////////
