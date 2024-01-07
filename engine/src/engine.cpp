// jacob curlin
// engine.cpp
// 01/05/2023



#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <assert.h>

// temp - remove
#include <unistd.h>
#include <limits.h>

#include "../include/engine.h"

Engine::Engine() {
    m_windowHandler = nullptr;
    m_inputHandler = nullptr;
    m_isRunning = false;
}
    
Engine::~Engine() {
    assert(m_windowHandler == nullptr);
    assert(m_inputHandler == nullptr); 
}

// main game loop
void Engine::Run() {
    Initialize();

    m_isRunning = true;

    float deltaTime = 0.0f;
    float currentFrame = 0.0f;
    float lastFrame = 0.0f;
    while (m_isRunning) {
        // frame timing
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        Update(deltaTime);
        Render();

        m_windowHandler->SwapBuffers();
    }
    Shutdown();
}

void Engine::Initialize() {
    
    m_windowHandler = new Window(settings.WindowWidth,
                                 settings.WindowHeight,
                                 "engine");

    m_inputHandler = new Input(m_windowHandler->GetGLFWWindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);

    // temp - remove
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current Working Directory: " << cwd << std::endl;
    } else {
        std::cerr << "getcwd() error" << std::endl;
        exit(1);
    }


    m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    m_shader = new Shader("../shaders/model_loading.vs", "../shaders/model_loading.fs");

    stbi_set_flip_vertically_on_load(true);
    m_model = new Model("objects/backpack/backpack.obj");
    
}

void Engine::Update(float deltaTime) {
    m_windowHandler->Update();
    if (m_inputHandler->isKeyPressed(GLFW_KEY_ESCAPE)) {
        m_isRunning = false;
    }
    
    if (m_inputHandler->isKeyPressed(GLFW_KEY_W)) 
        m_camera->KeyboardUpdate(FORWARD, deltaTime);
    if (m_inputHandler->isKeyPressed(GLFW_KEY_S)) 
        m_camera->KeyboardUpdate(BACKWARD, deltaTime);
    if (m_inputHandler->isKeyPressed(GLFW_KEY_A)) 
        m_camera->KeyboardUpdate(LEFT, deltaTime);
    if (m_inputHandler->isKeyPressed(GLFW_KEY_D)) 
        m_camera->KeyboardUpdate(RIGHT, deltaTime);
}

void Engine::Render() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->use();

    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), 
                            (float) settings.WindowWidth / (float) settings.WindowHeight,
                            0.1f, 100.0f);
    glm::mat4 view = m_camera->GetViewMatrix();

    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.04, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    m_shader->setMat4("model", model);
    m_model->Draw(*m_shader);
}

void Engine::Shutdown() {
    delete m_inputHandler;
    delete m_windowHandler;
}
