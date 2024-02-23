// jacob curlin
// sandbox.cpp
// 02/22/2024

#include "../include/sandbox.h"


Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize()
{
    Engine::Initialize();


    std::filesystem::path subject_path = m_settings.asset_dir / "soccerball/ball.obj";
    std::filesystem::path light_path = m_settings.asset_dir / "objects/light_cube/light_cube.obj";

    m_entities = std::vector<cgx::ecs::Entity>(2);

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

    cgx::ecs::Entity* e_subject = &m_entities[0];
    cgx::ecs::Entity* e_light_src = &m_entities[1];

    std::shared_ptr<cgx::graphics::Model> mod_subject = m_ecsHandler->GetComponent<RenderComponent>(*e_subject).model;
    std::shared_ptr<cgx::graphics::Model> mod_light_src = m_ecsHandler->GetComponent<RenderComponent>(*e_light_src).model;
    std::shared_ptr<cgx::graphics::Shader> s_subject = m_ecsHandler->GetComponent<RenderComponent>(*e_subject).shader;
    std::shared_ptr<cgx::graphics::Shader> s_light_src= m_ecsHandler->GetComponent<RenderComponent>(*e_light_src).shader;

    glm::mat4 proj_mat, view_mat;
    glm::mat4 obj_model_mat = glm::mat4(1.0f);
    glm::mat4 light_model_mat = glm::mat4(1.0f);

    proj_mat = glm::perspective(
        glm::radians(m_camera->getZoom()), 
        (float) m_settings.WindowWidth / (float) m_settings.WindowHeight, 
        0.1f, 100.0f
    );

    view_mat = m_camera->GetViewMatrix();

    s_subject->use();
    s_subject->setVec3("light.position", (m_ecsHandler->GetComponent<TransformComponent>(*e_light_src)).position);
    s_subject->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    s_subject->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    s_subject->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // model matrix - translate/scale model into world space 
    obj_model_mat = glm::mat4(1.0f);
    obj_model_mat = glm::translate(obj_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_subject).position);
    obj_model_mat = glm::scale(obj_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_subject).scale);

    s_subject->setMat4("projection", proj_mat);
    s_subject->setMat4("view", view_mat);
    s_subject->setMat4("model", obj_model_mat);  


    s_light_src->use();
    light_model_mat = glm::mat4(1.0f);
    s_light_src->setMat4("projection", proj_mat);
    s_light_src->setMat4("view", view_mat);

    light_model_mat = glm::translate(light_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_light_src).position);
    light_model_mat = glm::rotate(light_model_mat, glm::radians(140.0f), m_ecsHandler->GetComponent<TransformComponent>(*e_light_src).rotation);
    light_model_mat = glm::scale(light_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_light_src).scale);
    s_light_src->setMat4("model", light_model_mat);

    s_subject->use();
    mod_subject->draw(*s_subject);

    s_light_src->use();
    mod_light_src->draw(*s_light_src);

    if (m_imguiActive)
        Sandbox::ImguiRender();
}

void Sandbox::ImguiRender()
{
    m_imguiHandler->BeginRender();
    ImGui::ShowDemoWindow();
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