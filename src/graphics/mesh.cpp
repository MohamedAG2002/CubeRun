#include "graphics/mesh.h"
#include "core/defines.h"

#include <glad/gl.h>
#include <glm/vec3.hpp>

#include <cstring>

// Private functions
////////////////////////////////////////////////////////
static void setup_buffers(mesh_t* mesh)
{
  // Vertices init 
  //////////////////////////////////////////
  mesh->vertex_count = CUBE_VERTICES;
  
  // Back-face
  mesh->vertices[0] = {-0.5f, -0.5f, -0.5f};  
  mesh->vertices[1] = { 0.5f, -0.5f, -0.5f}; 
  mesh->vertices[2] = { 0.5f,  0.5f, -0.5f}; 
  mesh->vertices[3] = {-0.5f,  0.5f, -0.5f}; 

  // Front-face
  mesh->vertices[4] = {-0.5f, -0.5f, 0.5f};
  mesh->vertices[5] = { 0.5f, -0.5f, 0.5f};
  mesh->vertices[6] = { 0.5f,  0.5f, 0.5f};
  mesh->vertices[7] = {-0.5f,  0.5f, 0.5f};

  // Left-face
  mesh->vertices[8]  = {-0.5f,  0.5f,  0.5f};
  mesh->vertices[9]  = {-0.5f,  0.5f, -0.5f};
  mesh->vertices[10] = {-0.5f, -0.5f, -0.5f};
  mesh->vertices[11] = {-0.5f, -0.5f,  0.5f};

  // Right-face
  mesh->vertices[12] = {0.5f,  0.5f,  0.5f};
  mesh->vertices[13] = {0.5f,  0.5f, -0.5f};
  mesh->vertices[14] = {0.5f, -0.5f, -0.5f};
  mesh->vertices[15] = {0.5f, -0.5f,  0.5f};

  // Top-face
  mesh->vertices[16] = {-0.5f, -0.5f, -0.5f};
  mesh->vertices[17] = { 0.5f, -0.5f, -0.5f};
  mesh->vertices[18] = { 0.5f, -0.5f,  0.5f};
  mesh->vertices[19] = {-0.5f, -0.5f,  0.5f};

  // Bottom-face
  mesh->vertices[20] = {-0.5f, 0.5f, -0.5f};
  mesh->vertices[21] = { 0.5f, 0.5f, -0.5f};
  mesh->vertices[22] = { 0.5f, 0.5f,  0.5f};
  mesh->vertices[23] = {-0.5f, 0.5f,  0.5f};
  //////////////////////////////////////////

  // Indices init
  //////////////////////////////////////////
  mesh->index_count = CUBE_INDICES;

  u32 indices[] = {
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

  memcpy(mesh->indices, indices, sizeof(indices));
  //////////////////////////////////////////

  // VAO init 
  glGenVertexArrays(1, &mesh->vao_id);
  glBindVertexArray(mesh->vao_id);

  // VBO and EBO gen 
  glGenBuffers(1, &mesh->vbo_id);
  glGenBuffers(1, &mesh->ebo_id);
  
  // VBO set data
  glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->vertex_count, &mesh->vertices[0], GL_STATIC_DRAW);
  
  // EBO set data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh->index_count, &mesh->indices[0], GL_STATIC_DRAW);

  // Setting position attribute pointer
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(glm::vec3), 0);

  glBindVertexArray(0);
}
////////////////////////////////////////////////////////

// Mesh functions
////////////////////////////////////////////////////////
mesh_t* mesh_load()
{
  mesh_t* mesh = new mesh_t{};
  setup_buffers(mesh);

  return mesh;
}

void mesh_destroy(mesh_t* mesh)
{
  glDeleteBuffers(1, &mesh->vbo_id);
  glDeleteBuffers(1, &mesh->ebo_id);
  glDeleteVertexArrays(1, &mesh->vao_id);
 
  delete mesh;
}
////////////////////////////////////////////////////////
