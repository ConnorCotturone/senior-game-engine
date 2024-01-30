// jacob curlin
// sandbox_app.h
// 12/30/2023

#ifndef SANDBOX_H
#define SANDBOX_H

#include <string>
#include "cpgx.h"

class Sandbox : public Engine
{

public:
    Sandbox();              
    ~Sandbox();     

protected:
    void Initialize() override;
    void Update() override;
    void Render() override;
    void Shutdown() override;

    std::string message;

};

#endif // SANDBOX_H