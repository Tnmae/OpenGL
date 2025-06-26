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
  Texture(std::string imagePath, GLenum type, GLenum format);
  void TextureData(GLuint shaderProgram, std::string uniformName, GLint unit);
  void DrawTexture(GLint unit);
  void DeleteTexture();

private:
  GLuint texture;
};

#endif /*  TEXTURE_HPP */
