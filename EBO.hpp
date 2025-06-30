#ifndef EBO_HPP
#define EBO_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class EBO {
public:
  EBO();
  void Bind();
  void BufferData(std::vector<GLuint> &indices, GLenum usage);
  void Unbind();
  void Delete();

private:
  GLuint ID;
};

#endif /*  EBO_HPP  */
