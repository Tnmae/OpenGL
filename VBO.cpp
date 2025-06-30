#include "VBO.hpp"

VBO::VBO() { glGenBuffers(1, &ID); };

void VBO::BufferData(std::vector<Vertex> &vertices, GLenum usage) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               vertices.data(), usage);
}

void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }

void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::Delete() { glDeleteBuffers(1, &ID); }
