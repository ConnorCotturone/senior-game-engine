// jacob curlin
// resource_manager.cpp
// 02/09/2024


#include "resource_manager.h"
#include "../utility/logging.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"

#include <sstream>
#include <iomanip>


namespace cgx::graphics 
{

    ResourceManager::ResourceManager() {}
    ResourceManager::~ResourceManager() {}

    std::shared_ptr<Model> ResourceManager::getModel(const std::string& modelID)
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
            return nullptr;
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
            return nullptr;
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
            return nullptr;
        }
    }

    // sources: 
    // https://github.com/chrisliebert/sdlgl3-wavefront/blob/master/src/Renderer.cpp
    std::shared_ptr<Model> ResourceManager::loadModel(const std::string& path)
    {
        std::__fs::filesystem::path obj_file_path = path;
        std::__fs::filesystem::path mat_dir_path = obj_file_path.parent_path();


        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = "";

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(path, reader_config))
        {
            if (!reader.Error().empty())
            {
                CGX_ERROR("TinyObjReader: {}", reader.Error());
            }
            exit(1);
        }

        if (!reader.Warning().empty())
        {
            CGX_WARN("TinyObjReader: {}", reader.Warning())
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        
        for (const auto& src_mat: materials)
        {
            // create material id ( {.obj model path}_{material name} )
            std::ostringstream id_stream;
            id_stream << path << "_" << src_mat.name;
            std::string id = id_stream.str();

            glm::vec3 ambient_color, diffuse_color, specular_color;
            std::filesystem::path ambient_tex_path, diffuse_tex_path, specular_tex_path, normal_tex_path;
            float shininess;

            shininess = static_cast<float>(src_mat.shininess);
            ambient_color = glm::vec3(src_mat.ambient[0], src_mat.ambient[1], src_mat.ambient[2]);
            diffuse_color = glm::vec3(src_mat.diffuse[0], src_mat.diffuse[1], src_mat.diffuse[2]);
            specular_color = glm::vec3(src_mat.specular[0], src_mat.specular[1], src_mat.specular[2]);

            if (!src_mat.ambient_texname.empty()) { ambient_tex_path = mat_dir_path / src_mat.ambient_texname; }
            if (!src_mat.diffuse_texname.empty()) { diffuse_tex_path = mat_dir_path / src_mat.diffuse_texname; }
            if (!src_mat.specular_texname.empty()) { specular_tex_path = mat_dir_path / src_mat.specular_texname; } 
            if (!src_mat.bump_texname.empty()) { normal_tex_path = mat_dir_path / src_mat.normal_texname; }

            Material material(
                id,
                ambient_color,
                diffuse_color,
                specular_color,
                shininess,
                loadTexture(ambient_tex_path),
                loadTexture(diffuse_tex_path),
                loadTexture(specular_tex_path),
                loadTexture(normal_tex_path)
            );

            m_materials[id] = std::make_shared<Material>(material);
        }

        std::vector<std::shared_ptr<Mesh>> meshes;
        size_t last_material_id = 0;


        std::unordered_map<unsigned int, std::vector<Vertex>> material_to_vertices;
        std::unordered_map<unsigned int, std::vector<unsigned int>> material_to_indices;

        // iterate shapes 
        for (size_t s = 0; s < shapes.size(); s++)
        {
            size_t index_offset = 0;
            unsigned int material_id;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)                                                  // iterate faces
            {
                // check if material ID is new and initialize it in material maps if so
                material_id = shapes[s].mesh.material_ids[f];
                if (material_to_vertices.find(material_id) == material_to_vertices.end())
                {
                    material_to_vertices[material_id] = std::vector<Vertex>();
                    material_to_indices[material_id] = std::vector<unsigned int>();
                }

                // process face's vertices
                size_t fv = shapes[s].mesh.num_face_vertices[f];
                for (size_t v = 0; v < fv; v++)
                {
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    Vertex vertex;

                    // get current vertex position vector {x,y,z}
                    vertex.position = glm::vec3(
                        attrib.vertices[3 * size_t(idx.vertex_index) + 0],
                        attrib.vertices[3 * size_t(idx.vertex_index) + 1], 
                        attrib.vertices[3 * size_t(idx.vertex_index) + 2] 
                    );

                    // if present, get current vertex normal vector {x,y,z}
                    if (idx.normal_index >= 0)
                    {
                        vertex.normal = glm::vec3(
                            attrib.normals[3 * size_t(idx.normal_index) + 0],
                            attrib.normals[3 * size_t(idx.normal_index) + 1],
                            attrib.normals[3 * size_t(idx.normal_index) + 2]
                        );
                    }

                    // if present, get current vertex texture (uv) coordinates {u,v}
                    if (idx.texcoord_index >= 0)
                    {
                        vertex.texCoord = glm::vec2(
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 0],
                            attrib.texcoords[2 * size_t(idx.texcoord_index) + 1]
                        );
                    }

                    material_to_vertices[material_id].push_back(vertex);      
                    // add index of vertex (within its by-material vertex vector) to its by-material index vector
                    material_to_indices[material_id].push_back(material_to_vertices[material_id].size() - 1);   
                }
                index_offset += fv;
            }
        }

        for (auto& [material_id, vertices] : material_to_vertices) 
        {
            std::string material_id_str = path + "_" + materials[material_id].name;
            std::shared_ptr<cgx::graphics::Material> material = m_materials[material_id_str];

            std::vector<unsigned int>& indices = material_to_indices[material_id];
            
            auto mesh = std::make_shared<cgx::graphics::Mesh>(vertices, indices, material);
            meshes.push_back(mesh);
        }

        std::shared_ptr<Model> model = std::make_shared<Model>(path, meshes);
        m_models[path] = model;
        return model;
    }

    std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string& path)
    {
        if (path.empty()) { return nullptr; }

        stbi_set_flip_vertically_on_load(1);

        stbi_uc* data = nullptr;
        int width, height, num_channels;
        data = stbi_load(path.c_str(), &width, &height, &num_channels, 0);

        GLenum format = 0;
        if (data)
        {
            if (num_channels == 1)      { format = GL_RED; }
            else if (num_channels == 3) { format = GL_RGB; }
            else if (num_channels == 4) { format = GL_RGBA; }

            if (format == 0) { CGX_ERROR("Failed to determine valid texture data format"); } 
        }
        else { CGX_ERROR("Failed to load texture data."); }

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
            unsigned char placeholder_data[] = {
                255, 0, 255,   255, 255, 255,   255, 0, 255,   255, 255, 255,
                255, 255, 255, 255, 0, 255,     255, 255, 255, 255, 0, 255,
                255, 0, 255,   255, 255, 255,   255, 0, 255,   255, 255, 255,
                255, 255, 255, 255, 0, 255,     255, 255, 255, 255, 0, 255
            };

            width = 4;
            height = 4;
            num_channels = 3;

            auto texture = std::make_shared<Texture>(id, width, height, num_channels, format, placeholder_data);
            m_textures[id] = texture;
            return texture;
        }
    }

}
