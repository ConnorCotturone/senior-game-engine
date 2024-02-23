// jacob curlin
// sandbox_app.cpp
// 12/30/2023 

#include "../include/sandbox.h"
#include "../include/primitives.h"


// temp
#include <iostream>

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {
}


void Sandbox::Initialize() {
    Engine::Initialize();

    std::__fs::filesystem::path shader_dir(SHADER_DIRECTORY);
    std::__fs::filesystem::path data_dir(DATA_DIRECTORY);
    
    std::__fs::filesystem::path model_obj_path = data_dir / "soccerball/ball.obj";
    std::__fs::filesystem::path light_obj_path = data_dir / "objects/light_cube/light_cube.obj"; 

    std::__fs::filesystem::path grid_texture_path = data_dir / "grid.jpg"; 

    std::__fs::filesystem::path model_vs_path = shader_dir / "model.vs";
    std::__fs::filesystem::path model_fs_path = shader_dir / "model.fs";
    std::__fs::filesystem::path light_vs_path = shader_dir / "lighting.vs";
    std::__fs::filesystem::path light_fs_path = shader_dir / "lighting.fs";

    std::__fs::filesystem::path wireframe_fs_path = shader_dir / "wireframe.fs";

    // std::__fs::filesystem::path grid_vs_path = shader_dir / "grid.vs";
    // std::__fs::filesystem::path grid_fs_path = shader_dir / "grid.fs";


    m_ecsHandler = new ECS::ECSManager();
    m_ecsHandler->Initialize();

    m_ecsHandler->RegisterComponent<TransformComponent>();
    m_ecsHandler->RegisterComponent<RenderComponent>();

    m_entities = std::vector<ECS::Entity>(2);

    // subject
    m_entities[0] = m_ecsHandler->CreateEntity();
    m_ecsHandler->AddComponent(
        m_entities[0],
        RenderComponent {
            .model = new Model(model_obj_path.string()),
            .shader = new Shader(model_vs_path.c_str(), model_fs_path.c_str())
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
            .model = new Model(light_obj_path.string()),
            .shader = new Shader(light_vs_path.c_str(), light_fs_path.c_str())
        });
    m_ecsHandler->AddComponent(
        m_entities[1], 
        TransformComponent {
            .position = glm::vec3(1.0f, 3.0f, 5.0f),
            .rotation = glm::vec3(1.0f, 0.0f, 0.0f),
            .scale =    glm::vec3(0.5f, 0.5f, 0.5f)
        });
     
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));

    std::string grid_texture_path_str = grid_texture_path.string();
    std::string grid_texture_path_dir = grid_texture_path_str.substr(0, grid_texture_path_str.find_last_of('/'));
    std::string grid_texture_path_fname = "grid.jpg";

    unsigned int planeTexture = TextureFromFile(grid_texture_path_fname.c_str(), grid_texture_path_dir, false);

    m_wireframe_shader = new Shader(light_vs_path.c_str(), wireframe_fs_path.c_str());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void Sandbox::Update() {
    Engine::Update();
}

void Sandbox::Render() {
    Engine::Render();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    ECS::Entity* e_subject = &m_entities[0];
    ECS::Entity* e_lightSrc = &m_entities[1];
    Model* mod_subject = m_ecsHandler->GetComponent<RenderComponent>(*e_subject).model;
    Model* mod_lightSrc = m_ecsHandler->GetComponent<RenderComponent>(*e_lightSrc).model;
    Shader* s_subject = m_ecsHandler->GetComponent<RenderComponent>(*e_subject).shader;
    Shader* s_lightSrc = m_ecsHandler->GetComponent<RenderComponent>(*e_lightSrc).shader;

    glm::mat4 proj_mat, view_mat; 
    glm::mat4 obj_model_mat = glm::mat4(1.0f);
    glm::mat4 light_model_mat = glm::mat4(1.0f);

    proj_mat = glm::perspective(glm::radians(m_camera->getZoom()), 
                (float) settings.WindowWidth / (float) settings.WindowHeight, 0.1f, 100.0f);
    
    view_mat = m_camera->GetViewMatrix();


    s_subject->use();
    // setup lighting
    s_subject->setVec3("light.position", m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).position);
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


    s_lightSrc->use();
    light_model_mat = glm::mat4(1.0f);
    s_lightSrc->setMat4("projection", proj_mat);
    s_lightSrc->setMat4("view", view_mat);

    light_model_mat = glm::translate(light_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).position);
    light_model_mat = glm::rotate(light_model_mat, glm::radians(140.0f), m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).rotation);
    light_model_mat = glm::scale(light_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).scale);
    s_lightSrc->setMat4("model", light_model_mat);


    glStencilMask(0x00);
    s_subject->use();
    mod_subject->Draw(*s_subject);

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);

    s_lightSrc->use();
    mod_lightSrc->Draw(*s_lightSrc);

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    
    m_wireframe_shader->use();

    light_model_mat = glm::scale(light_model_mat, glm::vec3(1.1f, 1.1f, 1.1f));
    m_wireframe_shader->setMat4("view", view_mat);
    m_wireframe_shader->setMat4("projection", proj_mat);

    m_wireframe_shader->setMat4("model", light_model_mat);
    mod_lightSrc->Draw(*m_wireframe_shader);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);


    if (m_imguiActive) 
        Sandbox::ImguiRender();
}


void Sandbox::ImguiRender()
{
    m_imguiHandler->BeginRender();

    ECS::Entity* imgui_current_entity = &m_entities[0];

    const char* items[] = {"entity0", "entity1"};
    static int entity_current_idx = 0;
    if (ImGui::BeginListBox("Entities"))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            const bool is_selected = (entity_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected))
            {
                entity_current_idx = n;
                if (is_selected)
                    ImGui::SetItemDefaultFocus();

            }
        }
        ImGui::EndListBox();
    }

    imgui_current_entity = &m_entities[entity_current_idx];
    glm::vec3* curr_pos = &(m_ecsHandler->GetComponent<TransformComponent>(*imgui_current_entity).position);
    glm::vec3* curr_rot = &(m_ecsHandler->GetComponent<TransformComponent>(*imgui_current_entity).rotation);
    glm::vec3* curr_scl = &(m_ecsHandler->GetComponent<TransformComponent>(*imgui_current_entity).scale);

    ImGui::SeparatorText("Transform");
    ImGui::InputFloat3("Position", (float*)curr_pos);
    ImGui::InputFloat3("Rotation", (float*)curr_rot);
    ImGui::InputFloat3("Scale", (float*)curr_scl);

    m_imguiHandler->EndRender();
}


void Sandbox::Shutdown() {
    Engine::Shutdown();
}

int main() {
    Sandbox app;
    app.Run();
    return 0;
}