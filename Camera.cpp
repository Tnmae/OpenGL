#include "Camera.hpp"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 cameraPos) { Camera::cameraPos = cameraPos; }

void Camera::updateMatrix(GLfloat nearPlane, GLfloat farPlane) {

  glm::mat4 cameraView = glm::mat4(1.0f);
  glm::mat4 cameraProj = glm::mat4(1.0f);

  cameraView = glm::lookAt(cameraPos, cameraPos + Orientation, Up);
  cameraProj = glm::perspective(
      glm::radians(45.0f), float(float(WIDTH) / HEIGHT), nearPlane, farPlane);

  camMatrix = cameraProj * cameraView;
};

void Camera::Inputs(GLFWwindow *window, GLfloat sensitivity) {
  GLfloat speed = 0.01f;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += speed * Orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos += speed * -glm::normalize(glm::cross(Orientation, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos += speed * -Orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos += speed * glm::normalize(glm::cross(Orientation, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    cameraPos += speed * Up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    cameraPos += speed * -Up;
  }

  // Handles mouse inputs
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    // Hides mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Prevents camera from jumping on the first click
    if (firstClick) {
      glfwSetCursorPos(window, ((float)(WIDTH) / 2), ((float)(HEIGHT) / 2));
      firstClick = false;
    }

    // Stores the coordinates of the cursor
    double mouseX;
    double mouseY;
    // Fetches the coordinates of the cursor
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Normalizes and shifts the coordinates of the cursor such that they begin
    // in the middle of the screen and then "transforms" them into degrees
    float rotX = sensitivity * (float)(mouseY - ((float)(HEIGHT) / 2)) / HEIGHT;
    float rotY = sensitivity * (float)(mouseX - ((float)(WIDTH) / 2)) / WIDTH;

    // Calculates upcoming vertical change in the Orientation
    glm::vec3 newOrientation =
        glm::rotate(Orientation, glm::radians(-rotX),
                    glm::normalize(glm::cross(Orientation, Up)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <=
        glm::radians(85.0f)) {
      Orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    // Sets mouse cursor to the middle of the screen so that it doesn't end up
    // roaming around
    glfwSetCursorPos(window, ((float)(WIDTH) / 2), ((float)(HEIGHT) / 2));
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    // Unhides cursor since camera is not looking around anymore
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // Makes sure the next time the camera looks around it doesn't jump
    firstClick = true;
  }
}

void Camera::SendMatrix(GLuint shaderProgram, const char *uniform) {
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE,
                     glm::value_ptr(camMatrix));
}
