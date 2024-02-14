// jacob curlin
// model.h
// 01/06/2023

#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stb/stb_image.h>
#include <vector>
#include <string>
#include <iostream>

namespace cgx::graphics
{
    class Model {
    public:
        Model(std::string path);  
        ~Model();

        void Draw(Shader &shader);

    public:
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> m_meshes;
        std::string directory;
        bool gammaCorrection;

    private:
        // model data

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        glm::vec3 getMaterialColor(aiMaterial *mat, const char *pKey, unsigned int type, unsigned int idx); 

    };

    unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma);

}

#endif // MODEL_H