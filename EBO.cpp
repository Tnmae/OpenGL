#include "EBO.hpp"

EBO::EBO() { glGenBuffers(1, &ID); }

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

void EBO::BufferData(GLuint *indices, GLsizeiptr size, GLenum usage) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}

void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::Delete() { glDeleteBuffers(1, &ID); }
