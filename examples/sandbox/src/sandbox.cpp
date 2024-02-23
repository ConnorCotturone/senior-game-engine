// jacob curlin
// sandbox.cpp
// 02/22/2024

#include "../include/sandbox.h"


Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize()
{
    Engine::Initialize();

    m_ecsHandler = new cgx::ecs::ECSManager();
    m_ecsHandler->Initialize();

    m_ecsHandler->RegisterComponent<TransformComponent>();
    m_ecsHandler->RegisterComponent<RenderComponent>();

    m_entities = std::vector<cgx::ecs::Entity>(2);


    std::filesystem::path subject_path = m_settings.asset_dir / "soccerball/ball.obj";
    std::filesystem::path light_path = m_settings.asset_dir / "objects/light_cube/light_cube.obj";

    


    // subject
    m_entities[0] = m_ecsHandler->CreateEntity();
    m_ecsHandler->AddComponent(
        m_entities[0],
        RenderComponent {
            .model = m_resource_manager->loadModel(subject_path.string()),
            .shader = std::make_shared<cgx::graphics::Shader>(m_settings.shader_dir, "model.vs", "model.fs")
        });
    m_ecsHandler->AddComponent(
        m_entities[0], 
        TransformComponent {
            .position = glm::vec3(0.0f, 0.0f, 0.0f),
            .rotation = glm::vec3(0.0f, 0.0f, 0.0f),
            .scale =    glm::vec3(1.0f, 1.0f, 1.0f)
        });

    // light source
    m_entities[1] = m_ecsHandler->CreateEntity();
    m_ecsHandler->AddComponent(
        m_entities[1],
        RenderComponent {
            .model = m_resource_manager->loadModel(light_path.string()),
            .shader = std::make_shared<cgx::graphics::Shader>(m_settings.shader_dir, "lighting.vs", "lighting.fs")
        });
    m_ecsHandler->AddComponent(
        m_entities[1], 
        TransformComponent {
            .position = glm::vec3(1.0f, 3.0f, 5.0f),
            .rotation = glm::vec3(1.0f, 0.0f, 0.0f),
            .scale =    glm::vec3(0.5f, 0.5f, 0.5f)
        });

}

void Sandbox::Update()
{
    Engine::Update();
}

void Sandbox::Render()
{
    Engine::Render();



}

void Sandbox::ImguiRender()
{
    m_imguiHandler->BeginRender();
    // todo
    m_imguiHandler->EndRender();
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