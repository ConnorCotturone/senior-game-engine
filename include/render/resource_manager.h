// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "render/material.h"
#include "render/mesh.h"
#include "render/texture.h"
#include "render/model.h"
#include "render/shader.h"

#include <string>
#include <unordered_map>

namespace cgx::render
{
    class ResourceManager
    {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        std::shared_ptr<Model> getModel(const std::string& modelID);
        std::shared_ptr<Mesh> getMesh(const std::string& meshID);
        std::shared_ptr<Material> getMaterial(const std::string& materialID);
        std::shared_ptr<Texture> getTexture(const std::string& textureID);

        const std::unordered_map<std::string, std::shared_ptr<Model>>& GetModels() const { return m_models; }
        const std::unordered_map<std::string, std::shared_ptr<Shader>>& GetShaders() const { return m_shaders; }

        // source: https://github.com/chrisliebert/sdlgl3-wavefront/blob/master/src/Renderer.cpp
        std::shared_ptr<Model> loadModel(const std::string& path);

        std::shared_ptr<Texture> loadTexture(const std::string& path);
        std::shared_ptr<Shader> loadShader(const std::string& name, const std::string& shader_dir);


    private:
        std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
        std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;

        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
    };
}
