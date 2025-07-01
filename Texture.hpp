#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "stb/stb_image.h"

unsigned char *loadImage(const char *fileName);

class Texture {
public:
  std::string type;
  std::string path;
  Texture(std::string fileName, std::string type);
  void TextureData(GLuint shaderProgram, std::string uniformName, GLint unit);
  void DrawTexture(GLint unit);
  void DeleteTexture();
  GLuint texture;
};

#endif /*  TEXTURE_HPP */
