#include "Sphere.hpp"

Sphere::Sphere(GLfloat radius, GLuint stackCount, GLuint sectorCount,
               std::vector<Texture> &textures) {
  GLfloat x, y, z, xy;
  GLfloat nx, ny, nz;
  GLfloat lengthInv = 1.0f / radius;
  GLfloat sectorStep = 2 * PI / sectorCount;
  GLfloat stackStep = PI / stackCount;
  for (int i = 0; i <= stackCount; ++i) {
    GLfloat stackAngle = PI / 2 - i * stackStep;
    xy = radius * cosf(stackAngle);
    z = radius * sinf(stackAngle);
    for (int j = 0; j <= sectorCount; ++j) {
      Vertex vertex;
      GLfloat sectorAngle = j * sectorStep;
      x = xy * cosf(sectorAngle);
      y = xy * sinf(sectorAngle);
      vertex.position = glm::vec3(x, y, z);

      nx = x * lengthInv;
      ny = y * lengthInv;
      nz = z * lengthInv;
      vertex.normal = glm::vec3(nx, ny, nz);

      float s, t;
      s = (float)j / sectorCount;
      t = (float)i / stackCount;
      vertex.texUV = glm::vec2(s, t);

      Sphere::vertices.push_back(vertex);
    }
  }

  for (int i = 0; i <= stackCount; ++i) {
    GLuint k1 = i * (sectorCount + 1);
    GLuint k2 = k1 + sectorCount + 1;
    for (int j = 0; j <= sectorCount; ++j, ++k1, ++k2) {
      if (i != 0) {
        Sphere::indices.push_back(k1);
        Sphere::indices.push_back(k2);
        Sphere::indices.push_back(k1 + 1);
      }

      if (i != (stackCount - 1)) {
        Sphere::indices.push_back(k1 + 1);
        Sphere::indices.push_back(k2);
        Sphere::indices.push_back(k2 + 1);
      }
    }
  }
  Sphere::texture = textures;
  VBO vbo;
  EBO ebo;

  Vao.Bind();

  vbo.Bind();
  vbo.BufferData(vertices, GL_STATIC_DRAW);

  ebo.Bind();
  ebo.BufferData(indices, GL_STATIC_DRAW);

  Vao.DataAttribute(0, 3, 8, 0);
  Vao.DataAttribute(1, 3, 8, 3);
  Vao.DataAttribute(2, 2, 8, 6);

  Vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();
}

void Sphere::Draw(GLuint shaderProgram) {
  glUseProgram(shaderProgram);
  Vao.Bind();

  unsigned int numDiffuse = 0;
  unsigned int numSpecular = 0;
  unsigned int numNormal = 0;
  unsigned int numHeight = 0;
  std::string num;

  for (int i = 0; i < texture.size(); i++) {
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
}
