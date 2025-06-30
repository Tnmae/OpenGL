#ifndef VBO_HPP
#define VBO_HPP

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec3 color;
  glm::vec2 texUV;
};

class VBO {
public:
  VBO();
  void Bind();
  void BufferData(std::vector<Vertex> &vertices, GLenum usage);
  void Unbind();
  void Delete();

private:
  GLuint ID;
};

#endif /*  VBO_HPP  */
