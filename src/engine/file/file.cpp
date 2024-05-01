#include "file.h"
#include "engine/defines.h"

#include <fstream>
#include <string>
#include <cstdio>

// Public functions
/////////////////////////////////////////////////////////////////////////////////
bool file_is_empty(std::fstream& file) {
  return file.peek() == std::fstream::traits_type::eof();
}

void file_binary_save_u32(const u32 data, const std::string& file_name) {
  std::fstream file(file_name, std::ios::out | std::ios::binary);
  if(!file.is_open()) {
    printf("[FILE-ERROR]: Failed to open file at \'%s\'\n", file_name.c_str());
    return;
  }

  file.write((char*)&data, sizeof(data));
  file.close();
}

const u32 file_binary_load_u32(const std::string& file_name) {
  u32 data = 0; 
  
  std::fstream file(file_name, std::ios::in | std::ios::binary);
  if(!file.is_open()) {
    printf("[FILE-ERROR]: Failed to open file at \'%s\'\n", file_name.c_str());
    return data;
  }

  if(file_is_empty(file)) {
    return data;
  }

  file.read((char*)&data, sizeof(data));
  while(!file.eof()) {
    file.read((char*)&data, sizeof(data));
  }

  file.close();
  return data;
}
/////////////////////////////////////////////////////////////////////////////////
