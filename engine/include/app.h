// jacob curlin
// app.h
// 01/05/2023

class App
{
public:
    App();
    virtual ~App();

    void Run();

protected:
    virtual void Initialize();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Shutdown();

    bool m_isRunning;
};
