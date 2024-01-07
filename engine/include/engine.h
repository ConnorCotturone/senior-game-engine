// jacob curlin
// engine.h
// 01/05/2023

#ifndef ENGINE_H
#define ENGINE_H


#include "../include/window.h"
#include "../include/input.h"
#include "../include/mesh.h"
#include "../include/model.h"
#include "../include/shader.h"
#include "../include/camera.h"


struct EngineSettings {
            int WindowWidth = 800;
            int WindowHeight = 600;
            // shader source / compile directory paths?
};
    

class Engine
{
public:
    
    
public:
    Engine();
    virtual ~Engine();


    void Run();

protected:
    virtual void Initialize();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Shutdown();

protected:
    EngineSettings settings;
    Window* m_windowHandler;
    Input* m_inputHandler; 
    Camera* m_camera;
    Shader* m_shader;
    Model* m_model;
    
    bool m_isRunning;

};

#endif // ENGINE_H