// jacob curlin
// sandbox_app.h
// 12/30/2023

#ifndef SANDBOX_H
#define SANDBOX_H

#include <string>
#include "cpgx.h"
#include "grid.h"

class Sandbox : public Engine
{

public:
    Sandbox();              
    ~Sandbox();     

protected:
    void Initialize() override;
    void Update() override;
    void Render() override;
    void ImguiRender();
    void Shutdown() override;

    std::string message;

private:
    Shader* m_wireframe_shader;

};

#endif // SANDBOX_H