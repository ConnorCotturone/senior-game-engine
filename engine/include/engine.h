// jacob curlin
// app.h
// 01/05/2023

#ifndef ENGINE_H
#define ENGINE_H

#include "../include/window.h"
#include "../include/input.h"

class Engine
{
public:
    
    struct EngineSettings {
            int WindowWidth = 800;
            int WindowHeight = 600;
            // shader source / compile directory paths?
    };
    

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
    bool m_isRunning;

};

#endif // ENGINE_H