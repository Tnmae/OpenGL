#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Mesh.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Sphere {
public:
  Vertex vertices;        // has members position, normal, texUV
  Sphere(GLfloat radius); // initializes vertices;

private:
  GLfloat radius;
};
#endif /* SPHERE_HPP */
