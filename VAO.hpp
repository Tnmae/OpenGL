#ifndef VAO_HPP
#define VAO_HPP

#include "glad/glad.h"
#include <iostream>
#include <string>

class VAO {
public:
  VAO();
  void Bind();
  void DataAttribute(int count, int size, int stride, int dataBeginIndex);
  void Unbind();
  void Delete();

private:
  GLuint ID;
};

#endif /*  VAO _HPP  */
