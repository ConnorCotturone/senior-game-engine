// jacob curlin
// sandbox.cpp
// 02/22/2024

#include "../include/sandbox.h"
#include <glm/gtc/type_ptr.hpp>

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize()
{
    Engine::Initialize();

    model_filenames = {"soccerball/ball.obj", "objects/light_cube/light_cube.obj"};
    shader_names = {"model", "lighting"};

    for (const auto& filename : model_filenames)
    {
        std::filesystem::path model_path = m_settings.asset_dir / filename;
        loaded_models[filename] = m_resource_manager->loadModel(model_path.string());
    }

    for (const auto& name : shader_names)
    {
        std::filesystem::path vert_path = (m_settings.shader_dir / (name + ".vs")).string();
        std::filesystem::path frag_path = (m_settings.shader_dir / (name + ".fs")).string();

        loaded_shaders[name] = std::make_shared<cgx::graphics::Shader>(name, m_settings.shader_dir, vert_path, frag_path);
    }

    m_entities = std::vector<cgx::ecs::Entity>();

}

void Sandbox::Update()
{
    Engine::Update();
}

void Sandbox::Render()
{
    Engine::Render();

    glm::mat4 proj_mat, view_mat;

    view_mat = m_camera->GetViewMatrix();
    proj_mat = glm::perspective(
        glm::radians(m_camera->getZoom()),
        (float) m_settings.WindowWidth / (float) m_settings.WindowHeight,
        0.1f, 100.0f
    );

    glm::mat4 model_mat;
    for (auto& entity : m_entities)
    {
        model_mat = glm::mat4(1.0f);        

        std::shared_ptr<cgx::graphics::Model> model = m_ecsHandler->GetComponent<RenderComponent>(entity).model;
        std::shared_ptr<cgx::graphics::Shader> shader = m_ecsHandler->GetComponent<RenderComponent>(entity).shader;

        if (model && shader)
        {
            shader->use();
            // shader->setVec3("light.position", (m_ecsHandler->GetComponent<TransformComponent>(light))) /TODO
            shader->setVec3("light.position", 1.0f, 1.0f, 1.0f);
            shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

            model_mat = glm::translate(model_mat, m_ecsHandler->GetComponent<TransformComponent>(entity).position);
            // model_mat = glm::rotate(model_mat, glm::radians(140.0f), m_ecsHandler->GetComponent<TransformComponent>(entity).rotation);
            model_mat = glm::scale(model_mat, m_ecsHandler->GetComponent<TransformComponent>(entity).scale);

            shader->setMat4("projection", proj_mat);
            shader->setMat4("view", view_mat);
            shader->setMat4("model", model_mat);

            model->draw(*shader);
        }
    }

    if (m_imguiActive)
        Sandbox::ImguiRender();
}

void Sandbox::ImguiRender()
{
    m_imguiHandler->BeginRender();

    if (ImGui::Begin("Entities")) 
    {
        if (ImGui::Button("Add Entity"))
        {
            auto new_entity = m_ecsHandler->CreateEntity();

            m_ecsHandler->AddComponent(
                new_entity,
                RenderComponent {
                    .model = nullptr,
                    .shader = nullptr
            });
            m_ecsHandler->AddComponent(
                new_entity,
                TransformComponent {
                    .position = glm::vec3(0.0f, 0.0f, 0.0f),
                    .rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                    .scale =    glm::vec3(1.0f, 1.0f, 1.0f)
            });

            m_entities.push_back(new_entity);
            selected_entity_index = m_entities.size() - 1;   // select newly created (last) entity
        }

        ImGui::SameLine();

        if (ImGui::Button("Delete Entity") && selected_entity_index != -1 && !m_entities.empty())
        {
            m_ecsHandler->DestroyEntity(m_entities[selected_entity_index]);
            m_entities.erase(m_entities.begin() + selected_entity_index);
            selected_entity_index = -1;     // deselect entity
        }

        if (ImGui::BeginListBox("##Entitites"))
        {
            for (int i=0; i < m_entities.size(); ++i)
            {
                std::string label = "Entity " + std::to_string(i);
                bool is_selected = (i == selected_entity_index);
                if (ImGui::Selectable(label.c_str(), is_selected))
                {
                    selected_entity_index = i;
                }
            }
            ImGui::EndListBox();
        }
        ImGui::End();
    }

    if (selected_entity_index >= 0 && selected_entity_index < m_entities.size())
    {
        if (ImGui::Begin("Component Management"))
        {
            EditTransformComponent(selected_entity_index);
            EditRenderComponent(selected_entity_index);
        }
        ImGui::End();
    }

    m_imguiHandler->EndRender();
}

void Sandbox::EditTransformComponent(int entity_index)
{
    auto& transform = m_ecsHandler->GetComponent<TransformComponent>(m_entities[entity_index]);

    ImGui::Text("Transform Component");
    ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.1f);
    ImGui::DragFloat3("Roatation", glm::value_ptr(transform.rotation), 0.1f);
    ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.1f);
}

void Sandbox::EditRenderComponent(int entity_index)
{
    auto& render_component = m_ecsHandler->GetComponent<RenderComponent>(m_entities[entity_index]);

    const char* model_name = render_component.model ? render_component.model->GetName().c_str() : "No Model";
    if (ImGui::BeginCombo("Model", model_name))
    {
        for (auto& [model_name, model_ptr] : loaded_models)
        {
            bool is_selected = (render_component.model == model_ptr);
            if (ImGui::Selectable(model_name.c_str(), is_selected))
            {
                render_component.model = model_ptr;
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    const char* shader_name = render_component.shader ? render_component.shader->GetName().c_str() : "No Shader";
    if (ImGui::BeginCombo("Shader", shader_name))
    {
        for (auto& [shader_name, shader_ptr] : loaded_shaders)
        {
            bool is_selected = (render_component.shader == shader_ptr);
            if (ImGui::Selectable(shader_name.c_str(), is_selected))
            {
                render_component.shader = shader_ptr;
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

void Sandbox::Shutdown() 
{
    Engine::Shutdown();
}

int main()
{
    Sandbox app;
    app.Run();
    return 0;
}