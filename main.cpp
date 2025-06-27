#include "Camera.hpp"
#include "EBO.hpp"
#include "Texture.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

#define WIDTH 1080
#define HEIGHT 720

// Vertices coordinates
GLfloat vertices[] = {
    -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f,
    0.0f,  0.0f, 0.0f,  -1.0f, 0.0f, // Bottom side
    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    0.0f,  5.0f, 0.0f,  -1.0f, 0.0f, // Bottom side
    0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    5.0f,  5.0f, 0.0f,  -1.0f, 0.0f, // Bottom side
    0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f,
    5.0f,  0.0f, 0.0f,  -1.0f, 0.0f, // Bottom side

    -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f,
    0.0f,  0.0f, -0.8f, 0.5f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    5.0f,  0.0f, -0.8f, 0.5f,  0.0f, // Left Side
    0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f,
    2.5f,  5.0f, -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    5.0f,  0.0f, 0.0f,  0.5f,  -0.8f, // Non-facing side
    0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    0.0f,  0.0f, 0.0f,  0.5f,  -0.8f, // Non-facing side
    0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f,
    2.5f,  5.0f, 0.0f,  0.5f,  -0.8f, // Non-facing side

    0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    0.0f,  0.0f, 0.8f,  0.5f,  0.0f, // Right side
    0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f,
    5.0f,  0.0f, 0.8f,  0.5f,  0.0f, // Right side
    0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f,
    2.5f,  5.0f, 0.8f,  0.5f,  0.0f, // Right side

    0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f,
    5.0f,  0.0f, 0.0f,  0.5f,  0.8f, // Facing side
    -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f,
    0.0f,  0.0f, 0.0f,  0.5f,  0.8f, // Facing side
    0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f,
    2.5f,  5.0f, 0.0f,  0.5f,  0.8f // Facing side
};

// Indices for vertices order
GLuint indices[] = {
    0,  1,  2,  // Bottom side
    0,  2,  3,  // Bottom side
    4,  6,  5,  // Left side
    7,  9,  8,  // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14  // Facing side
};

GLfloat lightVertices[] = {
    //     COORDINATES     //
    -0.1f, -0.1f, 0.1f,  -0.1f, -0.1f, -0.1f, 0.1f, -0.1f,
    -0.1f, 0.1f,  -0.1f, 0.1f,  -0.1f, 0.1f,  0.1f, -0.1f,
    0.1f,  -0.1f, 0.1f,  0.1f,  -0.1f, 0.1f,  0.1f, 0.1f};

GLuint lightIndices[] = {0, 1, 2, 0, 2, 3, 0, 4, 7, 0, 7, 3, 3, 7, 6, 3, 6, 2,
                         2, 6, 5, 2, 5, 1, 1, 5, 4, 1, 4, 0, 4, 5, 6, 4, 6, 7};
int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Poopie", NULL, NULL);

  glfwMakeContextCurrent(window);

  gladLoadGL();

  glViewport(0, 0, WIDTH, HEIGHT);

  Shader defaultShader("default.vert", "default.frag");

  VAO vao;
  VBO vbo;
  EBO ebo;

  vao.Bind();

  vbo.Bind();
  vbo.BufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);

  ebo.Bind();
  ebo.BufferData(indices, sizeof(indices), GL_STATIC_DRAW);

  vao.DataAttribute(0, 3, 11, 0);
  vao.DataAttribute(1, 3, 11, 3);
  vao.DataAttribute(2, 2, 11, 6);
  vao.DataAttribute(3, 3, 11, 8);

  vbo.Unbind();
  vao.Unbind();
  ebo.Unbind();

  Shader lightShader("light.vert", "light.frag");

  VAO vaoLight;
  VBO vboLight;
  EBO eboLight;

  vaoLight.Bind();

  vboLight.Bind();
  vboLight.BufferData(lightVertices, sizeof(lightVertices), GL_STATIC_DRAW);

  eboLight.Bind();
  eboLight.BufferData(lightIndices, sizeof(lightIndices), GL_STATIC_DRAW);

  vaoLight.DataAttribute(0, 3, 3, 0);

  vboLight.Unbind();
  vaoLight.Unbind();
  eboLight.Unbind();

  glm::vec3 lightPos = glm::vec3(0.25f, 0.7f, 0.3f);
  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

  Texture texture("images/planks.png", GL_TEXTURE_2D, GL_RGBA);

  texture.TextureData(defaultShader.shaderProgram, "tex0", 0);

  Texture textureSpec("images/planksSpec.png", GL_TEXTURE_2D, GL_RED);

  textureSpec.TextureData(defaultShader.shaderProgram, "texSpec", 1);

  float rotation = 0.5;
  double prevTime = glfwGetTime();

  glEnable(GL_DEPTH_TEST);

  Camera camera(glm::vec3(0.0f, 0.3f, 2.0f));

  glm::vec3 modelPos = glm::vec3(0.0f, 0.2f, -0.5f);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double crntTime = glfwGetTime();
    if (crntTime - prevTime >= 1.0 / 60) {
      rotation += 0.5;
      prevTime = crntTime;
    }

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, modelPos);
    //   model =
    //        glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f,
    //        0.0f));

    camera.Inputs(window, 0.5f);
    camera.updateMatrix(0.1f, 100.0f);

    defaultShader.Activate();

    camera.SendMatrix(defaultShader.shaderProgram, "camMatrix");

    GLuint modelLoc =
        glGetUniformLocation(defaultShader.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4f(glGetUniformLocation(defaultShader.shaderProgram, "lightColor"),
                lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(defaultShader.shaderProgram, "lightPos"),
                lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(defaultShader.shaderProgram, "cameraPos"),
                camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

    texture.DrawTexture(0);
    textureSpec.DrawTexture(1);
    vao.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT,
                   0);

    lightShader.Activate();

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    camera.SendMatrix(lightShader.shaderProgram, "camMatrix");
    glUniformMatrix4fv(
        glGetUniformLocation(lightShader.shaderProgram, "lightModel"), 1,
        GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.shaderProgram, "lightColor"),
                lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    vaoLight.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int),
                   GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  defaultShader.Delete();
  vao.Delete();
  vbo.Delete();
  ebo.Delete();
  lightShader.Delete();
  vaoLight.Delete();
  vboLight.Delete();
  eboLight.Delete();
  texture.DeleteTexture();
  textureSpec.DeleteTexture();
  glfwTerminate();
  return EXIT_SUCCESS;
}
