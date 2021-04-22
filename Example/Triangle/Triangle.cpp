#include <memory>
#include <vector>
#include "Framework/Framework.h"
#include "SGL/SGL.h"

class ColorShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    ColorShaderProgram() {}
    ~ColorShaderProgram() {}

    SGL::Vertex VertexShader(const SGL::Vertex &modelVertex) override
    {
        return modelVertex;
    }
    SGL::Vector4f FragmentShader(const SGL::Vertex &screenVertex, const SGL::Vector2u32 &bufferExtent) override
    {
        return screenVertex.color;
    }
};

class ExampleTriangle : public Application
{

public:
    ExampleTriangle(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent) {}
    ~ExampleTriangle() {}

    void Init() override
    {
        Application::Init();
        SGL::Vertex v0;
        v0.position = SGL::Vector3(0.0f, 0.5f, 0.0f);
        v0.color = SGL::Vector3f(0.0f, 0.0f, 1.0f);
        SGL::Vertex v1;
        v1.position = SGL::Vector3(-0.5f, -0.5f, 0.0f);
        v1.color = SGL::Vector3f(0.0f, 1.0f, 0.0f);
        SGL::Vertex v2;
        v2.position = SGL::Vector3(0.5f, -0.5f, 0.0f);
        v2.color = SGL::Vector3f(1.0f, 0.0f, 0.0f);

        vertices = {v0, v1, v2};

        auto shader = std::make_shared<ColorShaderProgram>();

        m_Rasterizer->SetGraphicsShaderProgram(shader);
    }

    void ProcessInput() override
    {
        Application::ProcessInput();
        if (m_InputSystem->GetEventType() == SDL_QUIT || m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_ESCAPE) == BUTTON_STATE::PRESS)
            m_Status = ApplicationStatus::EXIT;
    }
    void Update() override
    {
        Application::Update();
    }
    void Draw() override
    {
        Application::Draw();
        m_Rasterizer->ClearColor(0.5f, 0.6f, 0.7f, 1.0f);
        m_Rasterizer->ClearDepth();

        m_Rasterizer->DrawArrays(SGL::RENDER_MODE::SOLID_TRIANGLE, 0, vertices);
    }

private:
    std::vector<SGL::Vertex> vertices;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleTriangle>("Example Triangle", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}