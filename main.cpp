#include "Mesh.hpp"
#include "Model.hpp"
#include "Sphere.hpp"
#include "shader.hpp"
#include <assimp/mesh.h>

#define WIDTH 1080
#define HEIGHT 720

// Vertices coordinates
Vertex vertices[] =
    { //               COORDINATES           /            COLORS          /
      //               NORMALS         /       TEXTURE COORDINATES    //
        Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec2(1.0f, 0.0f)}};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, 0, 2, 3};

Vertex lightVertices[] = { //     COORDINATES     //
    Vertex{glm::vec3(-1.5f, -1.5f, 1.5f)},
    Vertex{glm::vec3(-1.5f, -1.5f, -1.5f)},
    Vertex{glm::vec3(1.5f, -1.5f, -1.5f)},
    Vertex{glm::vec3(1.5f, -1.5f, 1.5f)},
    Vertex{glm::vec3(-1.5f, 1.5f, 1.5f)},
    Vertex{glm::vec3(-1.5f, 1.5f, -1.5f)},
    Vertex{glm::vec3(1.5f, 1.5f, -1.5f)},
    Vertex{glm::vec3(1.5f, 1.5f, 1.5f)}};

GLuint lightIndices[] = {0, 1, 2, 0, 2, 3, 0, 4, 7, 0, 7, 3, 3, 7, 6, 3, 6, 2,
                         2, 6, 5, 2, 5, 1, 1, 5, 4, 1, 4, 0, 4, 5, 6, 4, 6, 7};

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Arch OpenGL", NULL, NULL);

  glfwMakeContextCurrent(window);

  gladLoadGL();

  Shader defaultShader("default.vert", "default.frag");

  std::vector<Texture> tex = {Texture("images/earth2048.bmp", "diffuse")};
  // Sphere sphere(2.0f, 24, 72, tex);
  //   Texture textures[] = {Texture("images/planks.png", "diffuse"),
  //                    Texture("images/planksSpec.png", "specular")};

  //  std::vector<Vertex> vert(vertices,
  //                           vertices + sizeof(vertices) / sizeof(Vertex));
  //  std::vector<GLuint> ind(indices, indices + sizeof(indices) /
  //  sizeof(GLuint)); std::vector<Texture> tex(textures,
  //                          textures + sizeof(textures) / sizeof(Texture));

  //  Mesh floor(vert, ind, tex);

  Shader lightShader("light.vert", "light.frag");
  std::vector<Vertex> lightVert(
      lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
  std::vector<GLuint> lightInd(
      lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

  Mesh light(lightVert, lightInd, tex);

  Shader modelShader("model.vert", "model.frag");

  Model ourModel("model/Tree/Tree.obj");

  Model scape("model/ground/scene.gltf");

  glViewport(0, 0, WIDTH, HEIGHT);

  glm::vec3 lightPos = glm::vec3(0.0f, 15.0f, 0.0f);
  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

  float rotation = 0.5;
  double prevTime = glfwGetTime();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));

  glm::vec3 modelPos = glm::vec3(0.0f, 1.6f, -6.5f);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double crntTime = glfwGetTime();
    if (crntTime - prevTime >= 1.0 / 60) {
      rotation += 0.5;
      prevTime = crntTime;
    }
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 tree = glm::mat4(1.0f);
    //    model = glm::rotate(glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));

    tree = glm::translate(tree, modelPos);
    //    model =
    //        glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f,
    //        0.0f));

    // model = glm::translate(model, modelPos);

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

    // sphere.Draw(defaultShader.shaderProgram);

    lightShader.Activate();

    camera.SendMatrix(lightShader.shaderProgram, "camMatrix");
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    glUniformMatrix4fv(
        glGetUniformLocation(lightShader.shaderProgram, "lightModel"), 1,
        GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.shaderProgram, "lightColor"),
                lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    // floor.Draw(defaultShader.shaderProgram);
    light.Draw(lightShader.shaderProgram);

    modelShader.Activate();

    glUniform3f(glGetUniformLocation(modelShader.shaderProgram, "lightPos"),
                lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(modelShader.shaderProgram, "cameraPos"),
                camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
    glUniform4f(glGetUniformLocation(modelShader.shaderProgram, "lightColor"),
                lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    camera.SendMatrix(modelShader.shaderProgram, "view");
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    tree = glm::translate(glm::mat4(1.0f), glm::vec3(2.3f, 1.6f, -6.5f));
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    tree = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.6f, -5.0f));
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    tree = glm::translate(glm::mat4(1.0f), glm::vec3(-1.8f, 1.6f, 9.0f));
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    tree = glm::translate(glm::mat4(1.0f), glm::vec3(-2.4f, 1.6f, -3.4f));
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    tree = glm::translate(glm::mat4(1.0f), glm::vec3(-3.8f, 1.1f, -3.7f));
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    tree = glm::translate(glm::mat4(1.0f), glm::vec3(-1.1f, 1.4f, -7.8f));
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    tree = glm::translate(glm::mat4(1.0f), glm::vec3(5.4f, 1.3f, -2.8f));
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(tree));
    ourModel.Draw(modelShader);
    glUniformMatrix4fv(glGetUniformLocation(modelShader.shaderProgram, "model"),
                       1, GL_FALSE, glm::value_ptr(model));
    scape.Draw(modelShader);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  // defaultShader.Delete();
  lightShader.Delete();
  modelShader.Delete();

  glfwTerminate();
  return EXIT_SUCCESS;
};
