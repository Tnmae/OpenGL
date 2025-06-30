#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include "Camera.hpp"
#include "Texture.hpp"
#include "VAO.hpp"

class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> texture;

  VAO Vao;

  Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices,
       std::vector<Texture> &texture);

  void Draw(GLuint shaderProgram, Camera &camera);

private:
};

#endif /* MESH_HPP */
