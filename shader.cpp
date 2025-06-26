#include "shader.hpp"
#include <iostream>

std::string get_file_contents(const char *filename) {
  std::ifstream in(filename, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw(errno);
}

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {

  std::string vertShader = get_file_contents(vertexShaderPath);
  std::string fragShader = get_file_contents(fragmentShaderPath);

  const char *ver = vertShader.c_str();
  const char *frag = fragShader.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &ver, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &frag, NULL);
  glCompileShader(fragmentShader);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
};

void Shader::Activate() { glUseProgram(shaderProgram); };

void Shader::Delete() { glDeleteProgram(shaderProgram); };
