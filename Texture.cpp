#include "Texture.hpp"

unsigned char *loadImage(std::string fileName, int &width, int &height,
                         int &channels) {
  const char *file = fileName.c_str();
  stbi_set_flip_vertically_on_load(true);
  unsigned char *img = stbi_load(file, &width, &height, &channels, 0);
  if (img == NULL) {
    std::cout << "error loading image\n" << "path = " << file << "\n";
  }
  if (img == NULL) {
    std::cerr << "ERROR::STB_IMAGE::Failed to load image\n";
    std::cerr << "Path = " << file << "\n";
    std::cerr << "Reason = " << stbi_failure_reason() << "\n";
  }
  return img;
}

Texture::Texture(std::string fileName, std::string type) {
  Texture::type = type;
  Texture::path =
      fileName.substr(fileName.find_last_of('/') + 1, fileName.length() - 1);
  int width, height, channels;
  unsigned char *imgData = loadImage(fileName, width, height, channels);
  if (!imgData) {
    std::cerr << "Failed to load texture image: " << fileName << std::endl;
    return; // or throw an exception or handle it properly
  }

  GLenum format;
  if (channels == 4) {
    format = GL_RGBA;
  } else if (channels == 3) {
    format = GL_RGB;
  } else if (channels == 1) {
    format = GL_RED;
  }

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format,
               GL_UNSIGNED_BYTE, imgData);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(imgData);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::TextureData(GLuint shaderProgram, std::string uniformName,
                          GLint unit) {
  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, uniformName.c_str()), unit);
};

void Texture::DrawTexture(GLint unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, texture);
};

void Texture::DeleteTexture() { glDeleteTextures(1, &texture); };
