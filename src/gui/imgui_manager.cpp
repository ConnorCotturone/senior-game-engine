// Copyright © 2024 Jacob Curlin

#include "gui/imgui_manager.h"
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <glad/glad.h>

namespace cgx::gui
{
    void ImGuiManager::Initialize(GLFWwindow* window)
    {
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ioConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void ImGuiManager::Shutdown() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiManager::RegisterImGuiWindow(ImGuiWindow* window)
    {
        auto it = std::find(m_imgui_windows.begin(), m_imgui_windows.end(), window);
        if (it == m_imgui_windows.end())
        {
            m_imgui_windows.push_back(window);
        }
        else
        {
            CGX_ERROR("ImGuiManager : Window {} already registered.", window->getTitle());
        }
    }

    void ImGuiManager::UnregisterImGuiWindow(ImGuiWindow* window)
    {
        auto it = std::find(m_imgui_windows.begin(), m_imgui_windows.end(), window);
        if (it != m_imgui_windows.end())
        {
            m_imgui_windows.erase(it);
        }
        else
        {
            CGX_ERROR("ImGuiManager : Window {} already registered.", window->getTitle());
        }
    }

    void ImGuiManager::Render()
    {
        BeginRender();

        for (auto& window : m_imgui_windows)
        {
            if (window->isVisible())
            {
                window->Render();
            }
        }

        EndRender();
    }

    void ImGuiManager::BeginRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiManager::EndRender()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    /*
    void ImguiManager::RenderGameview(uint32_t texture)
    {
        ImGui::Begin("Game View");
        ImVec2 image_size = ImGui::GetContentRegionAvail();
        ImGui::Image(
            (void*) (GLuint)texture, 
            image_size,
            ImVec2(0.0f, 1.0f),
            ImVec2(1.0f, 0.0f)
        );
        ImGui::End();
    }
    */
}