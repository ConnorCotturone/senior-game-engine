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

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

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

        RenderCoreMenu();

        for (auto& window : m_imgui_windows)
        {
            if (window->isVisible())
            {
                window->Begin();
                window->Render();
                window->End();
            }
        }

        EndRender();
    }

    void ImGuiManager::BeginRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Dock Space
        static bool dockSpaceOpen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
        ImGui::PopStyleVar(3);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::End(); // End the DockSpace window
    }

    void ImGuiManager::EndRender()
    {
        ImGui::Render();
        ImGuiIO& io = ImGui::GetIO(); (void)io;                             
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)              
        {                                                                        
            GLFWwindow* backup_current_context = glfwGetCurrentContext();       
            ImGui::UpdatePlatformWindows();                                     
            ImGui::RenderPlatformWindowsDefault();                              
            glfwMakeContextCurrent(backup_current_context);
        }
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiManager::RenderCoreMenu()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("CGX_GUI_CORE"))
            {
                for (auto& window : m_imgui_windows)
                {
                    if (ImGui::MenuItem(window->getTitle().c_str(), "", window->isVisible()))
                    {
                        window->Show();
                    }
                }
            ImGui::EndMenu();
            }
        ImGui::EndMainMenuBar();
        }
    }
}