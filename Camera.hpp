#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#define WIDTH 1080
#define HEIGHT 720

class Camera {
public:
  glm::vec3 cameraPos = glm::vec3(0.0f);
  glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);

  bool firstClick = true;

  glm::mat4 camMatrix = glm::mat4(1.0f);

  Camera(glm::vec3 cameraPos);

  void Inputs(GLFWwindow *window, GLfloat sensitivity);
  void updateMatrix(GLfloat nearPlane, GLfloat farPlane);
  void SendMatrix(GLuint shaderProgram, const char *uniform);
};

#endif /* CAMERA_HPP */
