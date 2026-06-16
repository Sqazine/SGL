#pragma once

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Init() {}
    virtual void ProcessInput(InputSystem* inputSystem) {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void CleanUp() {}

    SGL::GraphicsPipeline* GetGraphicsPipeline() { return m_GraphicsPipeline.get(); }

protected:
    std::shared_ptr<SGL::GraphicsPipeline> m_GraphicsPipeline;

    friend class Application;
    Application* m_OwnerApp;
};