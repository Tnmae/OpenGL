#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Mesh.hpp"
#include "Texture.hpp"
#include "glad/glad.h"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <cmath>

#define PI 3.14

class Sphere {
public:
  Sphere(GLfloat radius, GLuint stackCount, GLuint sectorCount,
         std::vector<Texture> &textures); // initializes vertices;
  void Draw(GLuint shaderProgram);

private:
  VAO Vao;
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> texture;
};

#endif /* SPHERE_HPP */
