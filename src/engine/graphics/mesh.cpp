#include "mesh.h"
#include "engine/defines.h"

#include <glad/gl.h>

#include <vector>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void setup_buffers(Mesh* mesh) {
  mesh->vertices = {
    // Back-face
    -0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
   
    // Front-face
    -0.5f, -0.5f, 0.5f,
     0.5f, -0.5f, 0.5f,
     0.5f,  0.5f, 0.5f,
    -0.5f,  0.5f, 0.5f,
  
    // Left-face
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
  
    // Right-face
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
  
    // Top-face
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
  
    // Bottom-face
    -0.5f, 0.5f, -0.5f,
     0.5f, 0.5f, -0.5f,
     0.5f, 0.5f,  0.5f,
    -0.5f, 0.5f,  0.5f,
  };

  mesh->indices = {
    // Back-face 
    0, 1, 2, 
    2, 3, 0, 

    // Front-face 
    4, 5, 6, 
    6, 7, 4, 

    // Left-face 
    10, 9, 8, 
    8, 11, 10, 
    
    // Right-face 
    14, 13, 12, 
    12, 15, 14,

    // Top-face 
    16, 17, 18, 
    18, 19, 16, 

    // Bottom-face 
    20, 21, 22, 
    22, 23, 20, 
  };

  glGenVertexArrays(1, &mesh->vao);
  glBindVertexArray(mesh->vao);

  glGenBuffers(1, &mesh->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);
  
  glGenBuffers(1, &mesh->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);

  glBindVertexArray(0);
}
/////////////////////////////////////////////////////////////////////////////////

// Public functions
/////////////////////////////////////////////////////////////////////////////////
Mesh* mesh_create() {
  Mesh* mesh = new Mesh{};
  setup_buffers(mesh);

  return mesh;
}

void mesh_destroy(Mesh* mesh) {
  mesh->vertices.clear();
  mesh->indices.clear();

  delete mesh;
}
/////////////////////////////////////////////////////////////////////////////////
