#ifndef VBO_HPP
#define VBO_HPP

#include "glad/glad.h"
#include <iostream>
#include <string>

class VBO {
public:
  VBO();
  void Bind();
  void BufferData(GLfloat *vertices, GLsizeiptr size, GLenum usage);
  void Unbind();
  void Delete();

private:
  GLuint ID;
};

#endif /*  VBO_HPP  */
