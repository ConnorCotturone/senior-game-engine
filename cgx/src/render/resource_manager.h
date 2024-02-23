// jacob curlin
// resource_manager.h
// 02/09/2024

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "material.h"
#include "mesh.h"
#include "texture.h"
#include "model.h"

#include "tinyobjloader/tiny_obj_loader.h"

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
        std::shared_ptr<Texture> getTexture(const std::string& textureID);


        std::shared_ptr<Model> loadModel(const std::string& path);
        std::shared_ptr<Texture> loadTexture(const std::string& path);

    private:
        std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
        std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
    };
}



#endif // RESOURCEMANAGER_H