#include "Framework/Framework.h"
#include "ClearScreen.h"
#include "Triangle.h"
#include "TriangleWithTexture.h"
#include "RotateQuad.h"
#include "DrawQuad.h"
#include "DrawCube.h"
#include "Phong.h"
#include "BlinnPhong.h"
#include "CubeMap.h"
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
        if (m_InputSystem->GetEventType() == EventType::QUIT || m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_ESCAPE) == BUTTON_STATE::PRESS)
            m_Status = ApplicationStatus::EXIT;

        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_1) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 0;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_2) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 1;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_3) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 2;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_4) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 3;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_5) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 4;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_6) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 5;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_7) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 6;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_8) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 7;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_9) == BUTTON_STATE::PRESS)
            m_CurrentSceneIndex = 8;
        if (m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_0) == BUTTON_STATE::PRESS)
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

    app->RegisterScene(new ClearScreen());
    app->RegisterScene(new Triangle());
    app->RegisterScene(new TriangleWithTexture());
    app->RegisterScene(new RotateQuad());
    app->RegisterScene(new DrawQuad());
    app->RegisterScene(new DrawCube());
    app->RegisterScene(new Phong());
    app->RegisterScene(new BlinnPhong());
    app->RegisterScene(new CubeMap());

    app->Run();
    return 0;
}