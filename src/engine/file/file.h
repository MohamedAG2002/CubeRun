#pragma once

#include "engine/defines.h"

#include <fstream>
#include <string>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool file_is_empty(std::fstream& file);
void file_binary_save_u32(const u32 data, const std::string& file_name);
const u32 file_binary_load_u32(const std::string& file_name);
/////////////////////////////////////////////////////////////////////////////////
