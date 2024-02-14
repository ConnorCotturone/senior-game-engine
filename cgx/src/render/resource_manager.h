// jacob curlin
// resource_manager.h
// 02/09/2024

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "material.h"
#include "mesh.h"
#include "texture.h"

#include "tinyobjloader/tinyobjloader.h"

#include <string>
#include <memory>
#include <unordered_map>


namespace cgx::graphics
{
    class ResourceManager
    {
    public:
        ResourceManager();
        ~ResourceManager();


        std::shared_ptr<Model> getModel(const std::string& modelID);
        std::shared_ptr<Mesh> getMesh(const std::string& meshID);
        std::shared_ptr<Material> getMaterial(const std::string& materialID);
        std::shared_ptr<Model> getTexture(const std::string& textureID);

    private:
        std::unordered_map<std::string, std::shared_ptr<Material>> m_material;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
        std::unordered_map<std::string, std::shared_ptr<Model>> m_meshes;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;

        std::shared_ptr<Texture> loadTexture(const std::string& path);
        std::shared_ptr<Material> loadMaterial(const std::string& path);


        std::shared_ptr<Mesh> loadMesh(
            std::string meshID, 
            std::vector<Vertex> vertices, 
            std::vector<unsigned int> indices, 
            std::shared_ptr<Material> material
        ) 



        std::shared_ptr<Model> loadFromObj(const std::string& path);

    }
};



#endif // RESOURCEMANAGER_H