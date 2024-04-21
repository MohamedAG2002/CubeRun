#include "mesh.h"
#include "engine/defines.h"

#include <glad/gl.h>

// Private functions
/////////////////////////////////////////////////////////////////////////////////
static void setup_buffers(Mesh* mesh) {
  mesh->vertex_count = 24; 
  mesh->vertices     = new glm::vec3[mesh->vertex_count];
 
  // Back-face
  mesh->vertices[0] = glm::vec3(-0.5f, -0.5f, -0.5f);
  mesh->vertices[1] = glm::vec3( 0.5f, -0.5f, -0.5f);
  mesh->vertices[2] = glm::vec3( 0.5f,  0.5f, -0.5f);
  mesh->vertices[3] = glm::vec3(-0.5f,  0.5f, -0.5f);
    
  // Front-face
  mesh->vertices[4] = glm::vec3(-0.5f, -0.5f, 0.5f);
  mesh->vertices[5] = glm::vec3( 0.5f, -0.5f, 0.5f);
  mesh->vertices[6] = glm::vec3( 0.5f,  0.5f, 0.5f);
  mesh->vertices[7] = glm::vec3(-0.5f,  0.5f, 0.5f);
    
  // Left-face
  mesh->vertices[8]  = glm::vec3(-0.5f,  0.5f,  0.5f);
  mesh->vertices[9]  = glm::vec3(-0.5f,  0.5f, -0.5f);
  mesh->vertices[10] = glm::vec3(-0.5f, -0.5f, -0.5f);
  mesh->vertices[11] = glm::vec3(-0.5f, -0.5f,  0.5f);
  
  // Right-face
  mesh->vertices[12] = glm::vec3(0.5f,  0.5f,  0.5f);
  mesh->vertices[13] = glm::vec3(0.5f,  0.5f, -0.5f);
  mesh->vertices[14] = glm::vec3(0.5f, -0.5f, -0.5f);
  mesh->vertices[15] = glm::vec3(0.5f, -0.5f,  0.5f);
    
  // Top-face
  mesh->vertices[16] = glm::vec3(-0.5f, -0.5f, -0.5f);
  mesh->vertices[17] = glm::vec3( 0.5f, -0.5f, -0.5f);
  mesh->vertices[18] = glm::vec3( 0.5f, -0.5f,  0.5f);
  mesh->vertices[19] = glm::vec3(-0.5f, -0.5f,  0.5f);
    
  // Bottom-face
  mesh->vertices[20] = glm::vec3(-0.5f, 0.5f, -0.5f);
  mesh->vertices[21] = glm::vec3( 0.5f, 0.5f, -0.5f);
  mesh->vertices[22] = glm::vec3( 0.5f, 0.5f,  0.5f);
  mesh->vertices[23] = glm::vec3(-0.5f, 0.5f,  0.5f);

  mesh->index_count = 36; 
  mesh->indices     = new u32[mesh->index_count];

  // Back-face 
  mesh->indices[0] = 0;
  mesh->indices[1] = 1;
  mesh->indices[2] = 2;
  mesh->indices[3] = 2;
  mesh->indices[4] = 3;
  mesh->indices[5] = 0;
 
  // Front-face
  mesh->indices[6]  = 4;
  mesh->indices[7]  = 5;
  mesh->indices[8]  = 6;
  mesh->indices[9]  = 6;
  mesh->indices[10] = 7;
  mesh->indices[11] = 4;
  
  // Left-face 
  mesh->indices[12] = 10;
  mesh->indices[13] = 9;
  mesh->indices[14] = 8;
  mesh->indices[15] = 8;
  mesh->indices[16] = 11;
  mesh->indices[17] = 10;
  
  // Right-face 
  mesh->indices[18] = 14;
  mesh->indices[19] = 13;
  mesh->indices[20] = 12;
  mesh->indices[21] = 12;
  mesh->indices[22] = 15;
  mesh->indices[23] = 14;
  
  // Top-face 
  mesh->indices[24] = 16;
  mesh->indices[25] = 17;
  mesh->indices[26] = 18;
  mesh->indices[27] = 18;
  mesh->indices[28] = 19;
  mesh->indices[29] = 16;
  
  // Bottom-face 
  mesh->indices[30] = 20;
  mesh->indices[31] = 21;
  mesh->indices[32] = 22;
  mesh->indices[33] = 22;
  mesh->indices[34] = 23;
  mesh->indices[35] = 20;

  glGenVertexArrays(1, &mesh->vao);
  glBindVertexArray(mesh->vao);

  glGenBuffers(1, &mesh->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh->index_count, &mesh->indices[0], GL_STATIC_DRAW);
  
  glGenBuffers(1, &mesh->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->vertex_count, &mesh->vertices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(glm::vec3), 0);

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
  delete[] mesh->vertices;
  delete[] mesh->indices;

  delete mesh;
}
/////////////////////////////////////////////////////////////////////////////////
