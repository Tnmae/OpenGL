#ifndef MODEL_HPP
#define MODEL_HPP

#include "Mesh.hpp"
#include "Texture.hpp"
#include "shader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

class Model {
public:
  std::vector<Texture>
      textures_loaded; // stores all the textures loaded so far, optimization to
                       // make sure textures aren't loaded more than once.
  std::vector<Mesh> meshes;
  std::string directory;
  bool gammaCorrection;
  Model(std::string path);
  void loadModel(std::string path);
  void Draw(Shader &shader);

private:
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            std::string typeName,
                                            GLenum format);
};

#endif /*  MODEL_HPP  */
