// Copyright © 2024 Jacob Curlin

#include "imgui_ecs_system.h"
#include "../components/transform_component.h"
#include "../components/render_component.h"
#include "../components/light_component.h"
#include "../utility/logging.h"

#include <vector>
#include <memory>
#include <utility>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace cgx::gui 
{
    void ImguiECSSystem::Initialize(
        std::shared_ptr<cgx::ecs::ECSManager> ecs_manager, 
        std::shared_ptr<cgx::graphics::ResourceManager> resource_manager
    )
    {
        m_ecs_manager = ecs_manager;
        m_resource_manager = resource_manager;
        m_current_entity = cgx::ecs::MAX_ENTITIES;
    }

    void ImguiECSSystem::RenderECSMenu()
    {
        ImGui::Begin("ECS Management Panel");
        // ImGui::Separator();

        RenderActiveEntitiesSection();
         
        if (m_current_entity != cgx::ecs::MAX_ENTITIES)
        {
            ImGui::Separator();
            DisplayRenderComponentEditor(m_current_entity);
            DisplayTransformComponentEditor(m_current_entity);
            DisplayLightComponentEditor(m_current_entity);
        }

        ImGui::End();
    }

    void ImguiECSSystem::RenderActiveEntitiesSection()
    {
        const char* count_field_text = "Count: ###";
        float count_field_width = ImGui::CalcTextSize(count_field_text).x + ImGui::GetStyle().FramePadding.x;

        ImGui::Text("Active Entities");

        ImGui::SameLine();

        float available_space = ImGui::GetContentRegionAvail().x;
        ImGui::SameLine(available_space - count_field_width);

        ImGui::Text("Count: %zu", m_entities.size());

        if (ImGui::BeginChild("ActiveEntityList##ActiveEntityList", ImVec2(0, 150), true))
        {
            for (const auto& entity : m_entities)
            {
                if (ImGui::Selectable(("Entity_" + std::to_string(entity)).c_str(), entity == m_current_entity))
                {
                    m_current_entity = entity;
                    CGX_TRACE("> Selected Entity {}", m_current_entity);
                }
            }
            ImGui::EndChild();
        }

        float button_width = ImGui::GetContentRegionAvail().x * 0.45f;
        ImGui::NewLine();
        ImGui::SameLine((ImGui::GetWindowWidth() - 2 * button_width - ImGui::GetStyle().ItemSpacing.x) / 2);

        if (ImGui::Button("Create Entity##ActiveEntityList", ImVec2(button_width, 0)))
        {
            cgx::ecs::Entity new_entity = m_ecs_manager->CreateEntity();
            m_entities.insert(new_entity);
            m_current_entity = new_entity;
            CGX_INFO("> Created Entity {}", m_current_entity);
        }

        ImGui::SameLine();
        
        bool delete_button_active = (m_current_entity == cgx::ecs::MAX_ENTITIES);
        if (delete_button_active) { ImGui::BeginDisabled(); }
        if (ImGui::Button("Destroy Entity##ActiveEntityList", ImVec2(button_width, 0)))
        {
            m_ecs_manager->DestroyEntity(m_current_entity);
            CGX_TRACE("> Destroyed Entity {}", m_current_entity);
            m_current_entity = cgx::ecs::MAX_ENTITIES;
        }
        if (delete_button_active) { ImGui::EndDisabled(); }
    }


    void ImguiECSSystem::DisplayRenderComponentEditor(cgx::ecs::Entity entity)
    {
        bool has_render_component = m_ecs_manager->HasComponent<RenderComponent>(entity);

        const char* button_text = has_render_component ? "Remove" : "Add";
        float button_width = ImGui::CalcTextSize(button_text).x + ImGui::GetStyle().FramePadding.x * 2.0f;

        ImGui::Text("Render Component");

        float available_space = ImGui::GetContentRegionAvail().x;
        ImGui::SameLine(available_space - button_width);

        ImGui::PushID(entity);

        if (has_render_component)
        {
            if (ImGui::Button("Remove##RemoveRenderComponent"))
            {
                m_ecs_manager->RemoveComponent<RenderComponent>(entity);
                CGX_TRACE("Entity {}: Removed RenderComponent", entity);
                has_render_component = false;
            }
        }
        else
        {
            if (ImGui::Button("Add##AddRenderComponent"))
            {
                m_ecs_manager->AddComponent(
                    entity,
                    RenderComponent {
                        .model = nullptr,
                        .shader = nullptr
                });
                CGX_TRACE("Entity {}: Added RenderComponent", entity)
                has_render_component = true;
            }
        }

        if (has_render_component)
        {
            RenderComponent& render_component = m_ecs_manager->GetComponent<RenderComponent>(entity);

            if (ImGui::BeginCombo(
                "Model##RenderComponentModel", 
                render_component.model ? 
                render_component.model->GetName().c_str() : "No Model Selected"
            ))
            {
                const std::unordered_map<std::string, std::shared_ptr<cgx::graphics::Model>>& models = m_resource_manager->GetModels();
                for (const auto& pair : models)
                {
                    bool is_selected = (render_component.model == pair.second);
                    if (ImGui::Selectable(pair.first.c_str(), is_selected))
                    {
                        render_component.model = pair.second;
                        CGX_TRACE("Entity {}: RenderComponent Model changed to {}.", entity, pair.first);
                    }
                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
            if (ImGui::BeginCombo(
                "Shader##RenderComponentShader", 
                render_component.shader ? 
                render_component.shader->GetName().c_str() : "No Shader Selected"
            ))
            {
                const std::unordered_map<std::string, std::shared_ptr<cgx::graphics::Shader>>& shaders = m_resource_manager->GetShaders();
                for (const auto& pair : shaders)
                {
                    bool is_selected = (render_component.shader == pair.second);
                    if (ImGui::Selectable(pair.first.c_str(), is_selected))
                    {
                        render_component.shader = pair.second;
                        CGX_TRACE("Entity {}: RenderComponent Shader changed to {}.", entity, pair.first);
                    }
                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
        }

        ImGui::Separator();

        ImGui::PopID();
    }

    void ImguiECSSystem::DisplayTransformComponentEditor(cgx::ecs::Entity entity)
    {
        bool has_transform_component = m_ecs_manager->HasComponent<TransformComponent>(entity);

        const char* button_text = has_transform_component ? "Remove" : "Add";
        float button_width = ImGui::CalcTextSize(button_text).x + ImGui::GetStyle().FramePadding.x * 2.0f;

        ImGui::Text("Transform Component");

        float available_space = ImGui::GetContentRegionAvail().x;
        ImGui::SameLine(available_space - button_width);

        ImGui::PushID(entity);

        if (has_transform_component)
        {
            if (ImGui::Button("Remove##RemoveTransformComponent"))
            {
                m_ecs_manager->RemoveComponent<TransformComponent>(entity);
                CGX_TRACE("Entity {}: Removed TransformComponent", entity);
                has_transform_component = false;
            }
        }
        else
        {
            if (ImGui::Button("Add##AddTransformComponent"))
            {
                m_ecs_manager->AddComponent(
                    entity, 
                    TransformComponent {
                        .position = glm::vec3(0.0f, 0.0f, 0.0f),
                        .rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                        .scale = glm::vec3(1.0f, 1.0f, 1.0f)
                    });
                CGX_TRACE("Entity {}: Added TransformComponent", entity)
                has_transform_component = true;
            }
        }

        if (has_transform_component)
        {
            auto& component = m_ecs_manager->GetComponent<TransformComponent>(entity);
            
            if (ImGui::SliderFloat3("Position##TransformComponentPosition", &component.position[0], -25.0f, 25.0f)) {
                CGX_TRACE("Entity {}: TransformComponent Position changed to [{}, {}, {}]", entity, component.position.x, component.position.y, component.position.z);
            }
            if (ImGui::SliderFloat3("Rotation##TransformComponentRotation", &component.rotation[0], -180.0f, 180.0f)) {
                CGX_TRACE("Entity {}: TransformComponent Rotation changed to [{}, {}, {}]", entity, component.rotation.x, component.rotation.y, component.rotation.z);
            }
            if (ImGui::SliderFloat3("Scale##TransformComponentScale", &component.scale[0], -10.0f, 10.0f)) {
                CGX_TRACE("Entity {}: TransformComponent Scale changed to [{}, {}, {}]", entity, component.scale.x, component.scale.y, component.scale.z);
            }
        }

        ImGui::Separator();

        ImGui::PopID();
        
    }

    void ImguiECSSystem::DisplayLightComponentEditor(cgx::ecs::Entity entity)
    {
        bool has_light_component = m_ecs_manager->HasComponent<LightComponent>(entity);

        const char* button_text = has_light_component ? "Remove" : "Add";
        float button_width = ImGui::CalcTextSize(button_text).x + ImGui::GetStyle().FramePadding.x * 2.0f;

        ImGui::Text("Light Component");

        float available_space = ImGui::GetContentRegionAvail().x;
        ImGui::SameLine(available_space - button_width);

        ImGui::PushID(entity);

        if (has_light_component)
        {
            if (ImGui::Button("Remove##RemoveLightComponent"))
            {
                m_ecs_manager->RemoveComponent<LightComponent>(entity);
                CGX_TRACE("Entity {}: Removed LightComponent", entity);
                has_light_component = false;
            }
        }
        else
        {
            if (ImGui::Button("Add##AddLightComponent"))
            {
                CGX_TRACE("Entity {}: Added LightComponent", entity)
                m_ecs_manager->AddComponent(
                    entity,
                    LightComponent {
                        .position = glm::vec3(0.0f, 0.0f, 0.0f),
                        .color = glm::vec3(0.0f, 0.0f, 0.0f),
                        .intensity = 1.0f
                });
                has_light_component = true;
            }
        }

        if (has_light_component)
        {
            auto& component = m_ecs_manager->GetComponent<LightComponent>(entity);
            if (ImGui::SliderFloat3("Position##LightPosition", &component.position[0], -100.0f, 100.0f))
            {
                CGX_TRACE("Entity {}: LightComponent Position changed to [{}, {}, {}]", entity, component.position.x, component.position.y, component.position.z);
            }
            if (ImGui::SliderFloat3("Color##LightColor", &component.color[0], 0.0f, 1.0f)) { 
                CGX_TRACE("Entity {}: LightComponent Color changed to [{}, {}, {}]", entity, component.color.x, component.color.y, component.color.z);
            }
            if (ImGui::SliderFloat("Intensity##LightIntensity", &component.intensity, 0.0f, 100.0f)) {
                CGX_TRACE("Entity {}: LightComponent Intensity changed to {}", entity, component.intensity); 
            }
        }

        ImGui::Separator();

        ImGui::PopID();
    }

}