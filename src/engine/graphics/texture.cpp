#include "texture.h"
#include "engine/defines.h"

#include <stb_image/stb_image.h>
#include <glad/gl.h>

#include <string>
#include <cstdio>

// Globals
/////////////////////////////////////////////////////////////////////////////////
static i32 texture_slots = 0;
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Texture* texture_load(const std::string& path) {
  Texture* texture = new Texture{};
  texture->id    = 0; 
  texture->depth = 0;
  texture->slot  = texture_slots++;

  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  stbi_set_flip_vertically_on_load(true);
  u8* data = stbi_load(path.c_str(), &texture->width, &texture->height, &texture->channels, 0);
  if(data) {
    // Deduce the correct format based on the channels
    switch(texture->channels) {
      case 1:
        texture->format = GL_RED;
        break;
      case 2:
        texture->format = GL_RG;
        break;
      case 3:
        texture->format = GL_RGB;
        break;
      case 4:
        texture->format = GL_RGBA;
        break;
    } 

    // Send the pixel data to the GPU and generate a mipmap
    glTexImage2D(GL_TEXTURE_2D, texture->depth, texture->format, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  // Couldn't load the texture
  else {
    fprintf(stderr, "[ERROR]: Failed to load texture at \'%s\'\n", path.c_str());
  }
 
  // Setting texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Don't need the pixel data anymore, so free it. 
  stbi_image_free(data);

  return texture;
}

Texture* texture_load(i32 width, i32 height, u32 format, void* pixels) {
  Texture* texture  = new Texture{};
  texture->id       = 0; 
  texture->width    = width;
  texture->height   = height;
  texture->depth    = 0;
  texture->slot     = texture_slots++;
  texture->channels = 4;
  texture->format   = GL_RGBA;

  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  if(pixels) {
    // Send the pixel data to the GPU and generate a mipmap
    glTexImage2D(GL_TEXTURE_2D, texture->depth, texture->format, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  // Couldn't load the texture
  else {
    fprintf(stderr, "[ERROR]: Given pixels not valid\n");
  }
 
  // Setting texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return texture;
}

void texture_unload(Texture* texture) {
  glDeleteTextures(1, &texture->id);
  delete texture;
}

void texture_render(Texture* texture) {
  glActiveTexture(GL_TEXTURE0 + texture->slot);
  glBindTexture(GL_TEXTURE_2D, texture->id);
}
/////////////////////////////////////////////////////////////////////////////////
