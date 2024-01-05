// jacob curlin
// sandbox_app.h
// 12/30/2023

#include <string>
#include <app.h>

class SandboxApp : public App 
{

public:
    SandboxApp();              
    ~SandboxApp();     

protected:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Shutdown() override;

    std::string message;

};