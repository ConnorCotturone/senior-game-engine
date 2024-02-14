// jacob curlin
// resource_manager.cpp
// 02/09/2024


#include "resource_manager.h"
#include "utility/logging.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <sstream>
#include <iomanip>


namespace cgx::graphics 
{

    ResourceManager::ResourceManager() {}
    ResourceManager::~ResourceManager() {}

    std::shared_ptr<Model> ResourceManager::getModel(const string& modelID)
    {
        auto it = m_models.find(modelID);
        if (it != m_models.end())
        {
            return it->second;
        }
        else // modelID not found
        {
            return loadModel(modelID);  // load model obj file (which = its system file path)
        }
    }

    std::shared_ptr<Mesh> ResourceManager::getMesh(const std::string& meshID)
    {
        auto it = m_meshes.find(meshID);
        if (it != m_meshes.end())
        {
            return it->second;
        }
        else // (meshID not found)
        {
            // todo: return a placehold mesh
            CGX_ERROR("Failed to fetch mesh -- mesh ID not found.");
        }
    }

    std::shared_ptr<Material> ResourceManager::getMaterial(const std::string& materialID)
    {
        auto it = m_materials.find(materialID);
        if (it != m_materials.end())
        {
            return it->second;
        }
        else // (materialID not found)
        {
            // todo: return a standard placeholder material    
            CGX_ERROR("Failed to fetch material -- material ID not found.");
        }
    }

    std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& textureID)
    {
        auto it = m_textures.find(textureID);
        if (it != m_textures.end())
        {
            return it->second;
        }
        else // (textureID not found)
        {
            // todo: return a standard placeholder texture    
            CGX_ERROR("Failed to fetch texture -- texture ID not found.");
        }
    }

    // sources: 
    // https://github.com/chrisliebert/sdlgl3-wavefront/blob/master/src/Renderer.cpp
    std::shared_ptr<Model> ResourceManager::loadFromObj(const std::string& path)
    {
        std::__fs::filesystem::path obj_file_path = path;
        std::__fs::filesystem::path mat_dir_path = obj_file_path.parent_path();

        tinyobj::attrib_t attributes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string error;
        std::string warning;

        bool success = tinyobj::LoadObj(
            &attributes,
            &shapes,
            &materials,
            &error, &warning,
            obj_file_path.c_str(), mat_dir_path.c_str();
            true 
        )
        
        for (size_t m = 0; m < materials.size(), m++)
        {
            std::ostream idStream;
            idStream << path << "_" << materials[m].name;
            std::string id = idStream.str();

            Material material(id);

            material.m_ambientColor = glm::vec3(materials[m].ambient[0], materials[m].ambient[1], materials.ambient[2]);
            material.m_diffuseColor = glm::vec3(materials[m].diffuse[0], materials[m].diffuse[1], materials.diffuse[2]);
            material.m_specularColor = glm::vec3(materials[m].specular[0], materials[m].specular[1], materials.specular[2]);
            material.m_shininess = static_cast<float>(materials[i].shininess);

            if (!materials[m].ambient_texname.empty()) {
                std::filesystem::path texPath = mat_dir_path / materials[m].ambient_texname;
                material.m_ambientMap = loadTexture(texPath.string());
            }

            if (!materials[m].diffuse_texname.empty()) {
                std::filesystem::path texPath = mat_dir_path / materials[m].diffuse_texname;
                material.m_diffuseMap = loadTexture(texPath.string());
            }

            if (!materials[m].specular_texname.empty()) {
                std::filesystem::path texPath = mat_dir_path / materials[m].specular_texname;
                material.m_specularMap = loadTexture(texPath.string());
            }

            if (!materials[m].bump_texname.empty()) { 
                std::filesystem::path texPath = mat_dir_path / materials[m].normal_texname;
                material.m_normalMap = loadTexture(texPath.string());
            }

            m_materials[id] = std::make_shared<Material>(material);
        }

        std::vector<shared_ptr<Mesh>> meshes;

        for (size_t s = 0; s < shapes.size(); s++)                                     // iterates meshes
        {
            std::vector<Vertex> vertices;
            std::unordered_map<Vertex, uint32_t> unique_vertices{};
            std::vector<unsigned int> indices;

            std::ostream materialIdStream;
            materialIdStream << path << "_" << materials[shapes[s].mesh.material_ids[0]].name;
            std::string materialId = materialIdStream.str();

            std::shared_ptr<Material> material = m_materials[materialId];

            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)        // iterate faces
            {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                for (size_t v = 0; v < fv; v++)                                         // iterate vertices
                {
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                    Vertex vertex;
                    glm::vec3 data;

                    data.x = attrib.vertices[3*size_t(idx.vertex_index)+0];
                    data.y = attrib.vertices[3*size_t(idx.vertex_index)+1]; 
                    data.z = attrib.vertices[3*size_t(idx.vertex_index)+2]; 
                    vertex.position = data;
                    
                    if (idx.normal_index >= 0)
                    {
                        data.x = attrib.normals[3*size_t(idx.normal_index)+0];
                        data.y = attrib.normals[3*size_t(idx.normal_index)+1];
                        data.z = attrib.normals[3*size_t(idx.normal_index)+2];
                        vertex.normal = data;
                    }

                    if (idx.texcoord_index >= 0)
                    {
                        data.x = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                        data.y = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
                        vertex.texCoord = glm::vec2(data.x, data.y);
                    }

                    if (unique_vertices.count(vertex) == 0)
                    {
                        unique_vertices[vertex] = static_cast<uint32_t>(vertices.size());
                        vertices.push_back(vertex)
                    }

                    indices.push_back(unique_vertices[vertex]);
                }
                index_offset += fv;
            }

            mesh = std::shared_ptr<Mesh>(vertices, indices, material);
            meshes.push_back(mesh);
        }

    }


    std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string& path)
    {
        stbi_set_flip_vertically_on_load(1);

        stbi_uc* data = nullptr;
        unsigned int width, height, num_channels;
        data = stbi_load(path.c_str(), &width, &height, &num_channels, 0);

        GLenum format = 0;
        if (data)
        {
            m_width = (uint32_t) width;
            m_height = (uint32_t) height;
            m_num_channels = (uint32_t) num_channels;

            if (m_num_channels == 1) 
            { 
                format = GL_RED; 
            }            
            else if (m_num_channels == 3) 
            { 
                format = GL_RGB; 
            }
            else if (m_num_channels == 4) 
            { 
                format = GL_RGBA; 
            }

            if (format == 0)
            {
                CGX_ERROR("Failed to determine valid texture data format");
            }
        }
        else
        {
            CGX_ERROR("Failed to load texture data.");
        }

        std::ostringstream idStream;
        idStream << path << "_" << std::setfill('0') << std::setw(3) << m_textures.size();
        std::string id = idStream.str();

        if (data && format != 0)
        {
            auto texture = std::make_shared<Texture>(id, width, height, num_channels, format, data);
            m_textures[id] = texture;
            return texture;
        }
        else
        {
            float placeholder_data[] = {  
                1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,
                1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f,
                1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,
                1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f
            };    

            m_width = 4;
            m_height = 4;
            m_num_channels = 3;

            auto texture = std::make_shared<Texture>(id, width, height, num_channels, format, placeholder_data);
            m_textures[id] = texture;
            return texture;
        }
    }


}