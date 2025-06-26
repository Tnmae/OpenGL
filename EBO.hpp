#ifndef EBO_HPP
#define EBO_HPP

#include "glad/glad.h"

class EBO {
public:
  EBO();
  void Bind();
  void BufferData(GLuint *indices, GLsizeiptr size, GLenum usage);
  void Unbind();
  void Delete();

private:
  GLuint ID;
};

#endif /*  EBO_HPP  */
