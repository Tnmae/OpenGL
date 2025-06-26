#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>

std::string get_file_contents(const char *filename);

class Shader {
public:
  GLuint shaderProgram;
  Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
  void Activate();
  void Delete();
};

#endif /*   SHADER_HPP   */
