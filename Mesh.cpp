#include "Mesh.hpp"
#include "glad/glad.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices,
           std::vector<Texture> &texture) {
  Mesh::vertices = vertices;
  Mesh::indices = indices;
  Mesh::texture = texture;

  VBO VBO;
  EBO EBO;

  Vao.Bind();

  VBO.Bind();
  VBO.BufferData(vertices, GL_STATIC_DRAW);

  EBO.Bind();
  EBO.BufferData(indices, GL_STATIC_DRAW);

  Vao.DataAttribute(0, 3, 8, 0);
  Vao.DataAttribute(1, 3, 8, 3);
  Vao.DataAttribute(2, 2, 8, 6);

  Vao.Unbind();
  VBO.Unbind();
  EBO.Unbind();
};

void Mesh::Draw(GLuint shaderProgram) {
  glUseProgram(shaderProgram);
  Vao.Bind();

  unsigned int numDiffuse = 0;
  unsigned int numSpecular = 0;
  unsigned int numNormal = 0;
  unsigned int numHeight = 0;

  for (unsigned int i = 0; i < texture.size(); i++) {
    std::string num;
    std::string type = texture[i].type;

    if (type == "diffuse") {
      num = std::to_string(numDiffuse++);
    } else if (type == "specular") {
      num = std::to_string(numSpecular++);
    } else if (type == "normal") {
      num = std::to_string(numNormal++);
    } else if (type == "height") {
      num = std::to_string(numHeight++);
    }

    texture[i].TextureData(shaderProgram, (type + num).c_str(), i);
    texture[i].DrawTexture(i);
  }
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
};
