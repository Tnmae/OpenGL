#include "EBO.hpp"

EBO::EBO() { glGenBuffers(1, &ID); }

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

void EBO::BufferData(std::vector<GLuint> &indices, GLenum usage) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), usage);
}

void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::Delete() { glDeleteBuffers(1, &ID); }
