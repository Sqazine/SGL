#include "ExampleClearScreen.h"
#include "ExampleTriangle.h"
#include "ExampleTriangleWithTexture.h"
#include "ExampleRotateQuad.h"
#include "ExampleDrawQuad.h"
#include "ExampleDrawCube.h"
#include "ExamplePhong.h"
#include "ExampleBlinnPhong.h"
#include "ExampleCubeMap.h"
#include "ExampleFPCamera.h"
class MultiSceneApp : public Application
{
public:
    MultiSceneApp(const std::string &appName, const SGL::Vector2u32 &frameExtent)
        : Application(appName, frameExtent)
    {
    }

    void Init() override
    {
        Application::Init();
    }

    void ProcessInput() override
    {
        Application::ProcessInput();
        if (m_InputSystem->GetEventType() == EventType::QUIT || m_InputSystem->GetKeyState(KEYCODE_ESCAPE) == BUTTON_STATE::PRESS)
            m_Status = ApplicationStatus::EXIT;

        if (m_InputSystem->GetKeyState(KEYCODE_1) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 0;
        if (m_InputSystem->GetKeyState(KEYCODE_2) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 1;
        if (m_InputSystem->GetKeyState(KEYCODE_3) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 2;
        if (m_InputSystem->GetKeyState(KEYCODE_4) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 3;
        if (m_InputSystem->GetKeyState(KEYCODE_5) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 4;
        if (m_InputSystem->GetKeyState(KEYCODE_6) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 5;
        if (m_InputSystem->GetKeyState(KEYCODE_7) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 6;
        if (m_InputSystem->GetKeyState(KEYCODE_8) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 7;
        if (m_InputSystem->GetKeyState(KEYCODE_9) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 8;
        if (m_InputSystem->GetKeyState(KEYCODE_0) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 9;
    }
    void Update() override
    {
        Application::Update();
    }
    void Draw() override
    {
        Application::Draw();
    }
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<MultiSceneApp>("SGLExample", SGL::Vector2u32(800, 600));

    app->RegisterScene(new ExampleClearScreen());
    app->RegisterScene(new ExampleTriangle());
    app->RegisterScene(new ExampleTriangleWithTexture());
    app->RegisterScene(new ExampleRotateQuad());
    app->RegisterScene(new ExampleDrawQuad());
    app->RegisterScene(new ExampleDrawCube());
    app->RegisterScene(new ExampleFPCamera());
    app->RegisterScene(new ExamplePhong());
    app->RegisterScene(new ExampleBlinnPhong());
    app->RegisterScene(new ExampleCubeMap());

    app->Run();
    return 0;
}