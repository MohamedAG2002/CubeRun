#include "font.h"
#include "engine/defines.h"
#include "freetype/ftmodapi.h"

#include <glad/gl.h>
#include <glm/vec2.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>

#include <cstdio>
#include <string>

// Private functions 
/////////////////////////////////////////////////////////////////////////////////
static void init_font_gl(Font* font) {
  for(u32 i = 0; i < GLYPHS_MAX; i++) {
    if(FT_Load_Char(font->face, i, FT_LOAD_RENDER) != 0) {
      fprintf(stderr, "[ERROR]: Failed to load glyph \'%c\'\n", i);
      continue; 
    }

    u32 texture; 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 
                 0, 
                 GL_R8, 
                 font->face->glyph->bitmap.width, 
                 font->face->glyph->bitmap.rows, 
                 0, 
                 GL_RED, 
                 GL_UNSIGNED_BYTE, 
                 font->face->glyph->bitmap.buffer);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Glyph g = {
      .ID      = texture, 
      .size    = glm::ivec2(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows),
      .bearing = glm::ivec2(font->face->glyph->bitmap_left, font->face->glyph->bitmap_top), 
      .advance = font->face->glyph->advance.x,
    };

    font->glyphs[i] = g;
  }  
}

static void init_font_buffers(Font* font) {
  glGenVertexArrays(1, &font->vao);
  glBindVertexArray(font->vao);
  
  glGenBuffers(1, &font->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, font->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
 
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(f32) * 4, nullptr);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions 
/////////////////////////////////////////////////////////////////////////////////
Font* font_load(const std::string& path, const u32 size) {
  Font* font = new Font{};
  
  if(FT_Init_FreeType(&font->lib) != 0) {
    fprintf(stderr, "[ERROR]: Failed to initialize FreeType");
    return nullptr;
  }

  if(FT_New_Face(font->lib, path.c_str(), 0, &font->face)) {
    fprintf(stderr, "[ERROR]: Failed to load a font at \'%s\'\n", path.c_str());
    return nullptr; 
  }

  FT_Set_Pixel_Sizes(font->face, 0, size);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  init_font_gl(font);
  init_font_buffers(font);

  return font;
}

void font_unload(Font* font) {
  if(!font) {
    return;
  }

  FT_Done_Face(font->face);
  FT_Done_Library(font->lib);

  delete font;
}
/////////////////////////////////////////////////////////////////////////////////
