// jacob curlin
// sandbox_app.h
// 12/30/2023

#ifndef SANDBOX_H
#define SANDBOX_H

#include <string>
#include "cpgx.h"

class Sandbox : public Engine
{

public:
    Sandbox();              
    ~Sandbox();     

protected:
    void Initialize() override;
    void Update() override;
    void Render() override;
    void Shutdown() override;

    void ImguiRender();
    void EditTransformComponent(int entity_index);
    void EditRenderComponent(int entity_index);


    std::string message;

private:
    std::vector<std::string> model_filenames;
    std::unordered_map<std::string, std::shared_ptr<cgx::graphics::Model>> loaded_models;

    std::vector<std::string> shader_names;
    std::unordered_map<std::string, std::shared_ptr<cgx::graphics::Shader>> loaded_shaders;
    
    int selected_entity_index = -1;

};

#endif // SANDBOX_H