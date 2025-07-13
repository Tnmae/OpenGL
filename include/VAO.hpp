#ifndef VAO_HPP
#define VAO_HPP

#include "../lib/glad/glad.h"
#include "EBO.hpp"
#include "VBO.hpp"
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
