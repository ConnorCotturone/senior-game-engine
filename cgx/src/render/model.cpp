// jacob curlin
// model.cpp
// 01/06/2023

#include "model.h"

namespace cgx::graphics
{

    Model::Model(std::string path) { loadModel(path); }

    Model::~Model() {}

    void Model::Draw(Shader &shader)
    {
        for (unsigned int i = 0; i < m_meshes.size(); i++)
        {
            m_meshes[i].Draw(shader);                           // loop over meshes and call their respective Draw() functions
        }
    }

    void Model::loadModel(std::string path)
    {
        Assimp::Importer import;

        // aiProcess_Triangulate    : tells assimp to transform primitive shapes to triangles first
        // aiProcessFlipUVs         : tells assimp to flip the texture coordinates on the y-axis 
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);   

        // scene error check
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));     // get directory path of given file path 

        processNode(scene->mRootNode, scene);                   // process scene's nodes
    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)     // process current node's meshes
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_meshes.push_back(processMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)   // recursively process current node's children nodes
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        // Material material;

        // std::vector<Texture> textures; ( deprecated )

        // retreive vertex data for {mesh->mNumVertices} individual vertices from assimp aiMesh structure
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;                       // temporary vec3 for transferring assimp's data

            // position vector data
            vector.x = mesh->mVertices[i].x;        
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            // normal vector data
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            // texture coordinate data
            if (mesh->mTextureCoords[0])                    // check that texture coords present
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;

                /*
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vector.Tangent = vector;


                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vector.Bitangent = vector;
                */
            } else {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);   // 0 vec if no texture coords present
            }

            vertices.push_back(vertex);
        }

        // iterate through mesh's faces and retreive corresponding vertex indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)          // (for each face)
        {
            aiFace face = mesh->mFaces[i];
            
            for (unsigned int j = 0; j < face.mNumIndices; j++)     // (for each index of current face)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // process materials
        aiMaterial* ai_material = scene->mMaterials[mesh->mMaterialIndex];

        bool useDiffuseMap = false;
        unsigned int diffuseMap = 0;
        std::vector<Texture> diffuseTextures = loadMaterialTextures(ai_material, aiTextureType_DIFFUSE, "texture_diffuse");
        if (diffuseTextures.size() > 0) 
        {
            useDiffuseMap = true;
            diffuseMap = diffuseTextures[0].id;
        }

        bool useSpecularMap = false;
        unsigned int specularMap = 0;
        std::vector<Texture> specularTextures = loadMaterialTextures(ai_material, aiTextureType_SPECULAR, "texture_specular");
        if (specularTextures.size() > 0)
        {
            useSpecularMap = true;
            specularMap = specularTextures[0].id;
        }

        glm::vec3 diffuseColor = getMaterialColor(ai_material, AI_MATKEY_COLOR_DIFFUSE);
        glm::vec3 specularColor = getMaterialColor(ai_material, AI_MATKEY_COLOR_SPECULAR);

        /*  ( deprecated )
        // append diffuse maps to end of textures vector
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // append specular maps to end of textures vector 
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        */

        /*
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        */

        return Mesh(vertices, indices, Material(diffuseColor, specularColor, diffuseMap, specularMap, useDiffuseMap, useSpecularMap));
    }

    /* iterate over all texture locations for given type, retreive corresponding file locations, load/generate textures & store in vertex struct */
    std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)    
        {
            aiString str;
            mat->GetTexture(type, i, &str);     // get texture path

            bool skip = false; 
            for (unsigned int j = 0; j < textures_loaded.size(); j++)                   // iterate through currently loaded textures
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)      // if texture loaded, add to textures[] & loop
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)                                                                  // else, 
            {
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), directory, false);            // load texture
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        return textures;
    }

    glm::vec3 Model::getMaterialColor(aiMaterial *mat, const char *pKey, unsigned int type, unsigned int idx) 
    {
        aiColor3D color(0.f, 0.f, 0.f);
        if (mat->Get(pKey, 0, 0, color) == AI_SUCCESS)
        {
            return glm::vec3(color.r, color.g, color.b);
        }
        return glm::vec3(1.0f);
    }

    /* load texture data */
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
    {
        std::string filename = std::string(path);   
        filename = directory + '/' + filename;

        unsigned int textureID;             
        glGenTextures(1, &textureID);       // generate texture

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);   // load texture image w/ lib stb_image.h
        if (data)
        {
            // determine format from num components [R (1), RGB (3), RGBA (4)]
            GLenum format;
            if (nrComponents == 1) {                
                format = GL_RED;
            } else if (nrComponents == 3) {
                format = GL_RGB;
            } else if (nrComponents == 4) {
                format = GL_RGBA;
            }

            glBindTexture(GL_TEXTURE_2D, textureID);    
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0 , format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }

}


