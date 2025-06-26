#include "VAO.hpp"

VAO::VAO() { glGenVertexArrays(1, &ID); }

void VAO::DataAttribute(int count, int size, int stride, int dataBeginIndex) {
  glVertexAttribPointer(count, size, GL_FLOAT, GL_FALSE, stride * sizeof(float),
                        (void *)(dataBeginIndex * sizeof(float)));
  glEnableVertexAttribArray(count);
}

void VAO::Bind() { glBindVertexArray(ID); }

void VAO::Unbind() { glBindVertexArray(0); }

void VAO::Delete() { glDeleteVertexArrays(1, &ID); }
