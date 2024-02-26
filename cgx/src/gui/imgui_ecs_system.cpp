// Copyright © 2024 Jacob Curlin

#include "imgui_ecs_system.h"
#include "../components/transform_component.h"
#include "../components/render_component.h"
#include "../components/light_component.h"


#include <vector>
#include <memory>
#include <utility>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace cgx::gui 
{
    void ImguiECSSystem::Initialize(std::shared_ptr<cgx::ecs::ECSManager> ecs_manager)
    {
        m_ecs_manager = ecs_manager;
        m_current_entity = cgx::ecs::MAX_ENTITIES;
    }

    void ImguiECSSystem::DisplayEntityDropdown()
    {
        if (ImGui::BeginCombo("Entities", 
            m_current_entity != cgx::ecs::MAX_ENTITIES ? 
            ("Entity_" + std::to_string(m_current_entity)).c_str() : "Select Entity"))
        {
            if (m_entities.empty())
            {
                ImGui::Text("No Active Entities.");
            }
            else
            {
                for (const auto& entity : m_entities)
                {
                    std::string label = "Entity_" + std::to_string(entity);
                    bool is_selected = (entity == m_current_entity);

                    if (ImGui::Selectable(label.c_str(), is_selected))
                    {
                        m_current_entity = entity;
                    }

                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Add Entity"))
        {
            cgx::ecs::Entity new_entity = m_ecs_manager->CreateEntity();
            m_entities.insert(new_entity);
            m_current_entity = new_entity;
        }

        ImGui::SameLine();

        if (m_current_entity != cgx::ecs::MAX_ENTITIES && ImGui::Button("Delete Entity"))
        {
            m_ecs_manager->DestroyEntity(m_current_entity);
            m_current_entity = cgx::ecs::MAX_ENTITIES;
        }

    }
    
    void ImguiECSSystem::DisplayComponentEditors()
    {
        // I've included the headers for the three components I want to render component editors for.  
        // When an entity is selected, I want to render menus conditionally for each component, 
        // dependent on if the entity is associated with said component. 
        // m_ecs_manager->GetSignature(entity) will return the signature of an entity. 
        // m_ecs_manager->GetComponentType<ComponentTypeName>() will return the type id of a component, which as explained
        // can be compared to the entity's signature to see if an entity posseses said component. 
        // m_ecs_managger->GetComponent<ComponentTypeName>(entity) will return component data. 
        // for example, m_ecs_manager->GetComponent<RenderComponent>(entity) will return entity's render component data. 

        // The three registered component types we are working with are RenderComponent, TransformComponent, and LightComponent
        // I want you to, for the current entity, conditionally render menus allowing for the editing of each component's
        // data, i.e. do not render the menu if the entity does not possess the component. 

        // RenderComponent should just be a "rendercomponent editor" text value since i have to setup backend 
        // to provide the gui with the available models / shaders to be selected
        // TransformComponent should just have sliders / modifiable values for its 3 vec3s
        // LightComponent should jsut have sliders / modifable values for its two vec2s and float


        if (m_current_entity == cgx::ecs::MAX_ENTITIES)     // no entity selected -> don't display component list
        {
            return;
        }

        auto signature = m_ecs_manager->GetSignature(m_current_entity);

        // Assuming you have methods to check if a component is associated with the current entity
        if (signature.test(m_ecs_manager->GetComponentType<RenderComponent>())) {
            DisplayRenderComponentEditor(m_current_entity);
        }
        if (signature.test(m_ecs_manager->GetComponentType<TransformComponent>())) {
            DisplayTransformComponentEditor(m_current_entity);
        }
        if (signature.test(m_ecs_manager->GetComponentType<LightComponent>())) {
            DisplayLightComponentEditor(m_current_entity);
        }
    }

    void ImguiECSSystem::DisplayRenderComponentEditor(cgx::ecs::Entity entity)
    {
        if (ImGui::TreeNode("Render Component")) 
        {
            ImGui::Text("RenderComponent editor setup pending.");
            ImGui::TreePop();
        }
    }

    void ImguiECSSystem::DisplayTransformComponentEditor(cgx::ecs::Entity entity)
    {
        if (m_ecs_manager->HasComponent<TransformComponent>(entity)) 
        {
            auto& component = m_ecs_manager->GetComponent<TransformComponent>(entity);
            if (ImGui::TreeNode("Transform Component")) 
            {
                ImGui::SliderFloat3("Position", &component.position[0], -100.0f, 100.0f);
                ImGui::SliderFloat3("Rotation", &component.rotation[0], -180.0f, 180.0f);
                ImGui::SliderFloat3("Scale", &component.scale[0], -10.0f, 10.0f);
                ImGui::TreePop();
            }
        }
    }

    void ImguiECSSystem::DisplayLightComponentEditor(cgx::ecs::Entity entity)
    {
        if (m_ecs_manager->HasComponent<LightComponent>(entity)) 
        {
            auto& component = m_ecs_manager->GetComponent<LightComponent>(entity);
            if (ImGui::TreeNode("Light Component")) 
            {
                ImGui::SliderFloat3("Position", &component.position[0], -100.0f, 100.0f);
                ImGui::SliderFloat3("Color", &component.color[0], 0.0f, 1.0f);
                ImGui::SliderFloat("Intensity", &component.intensity, 0.0f, 100.0f);
                ImGui::TreePop();
            }
        }
    }

}