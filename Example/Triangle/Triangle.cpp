#include <memory>
#include <vector>
#include "Engine/Engine.h"
#include "SGL/SGL.h"

class ColorShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    ColorShaderProgram() {}
    ~ColorShaderProgram() {}

    uniform std::vector<SGL::Vector3f> positions;
    uniform std::vector<SGL::Vector4f> vertexColors;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        varyings.CommitVector4fVarying("vColor", vertexColors[vertexIndex]);
        return SGL::Vector4f(positions[vertexIndex], 1.0f);
    }
    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return varyings.GetVector4fVarying("vColor");
    }
};

class ExampleTriangle : public Application
{

public:
    ExampleTriangle(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent), triangle(Mesh(MeshType::TRIANGLE)) {}
    ~ExampleTriangle() {}

    void Init() override
    {
        Application::Init();

        shader = std::make_shared<ColorShaderProgram>();
        shader->positions = triangle.GetPositions();
        shader->vertexColors = triangle.GetVertexColors();

        SGL::GraphicsPipelineCreateInfo info;
        info.defaultBufferExtent = m_FrameExtent;
        info.shaderProgram = shader.get();
        info.renderType = SGL::RenderType::SOLID_TRIANGLE;
        info.clearBufferType = SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER;
        info.clearColor = SGL::Vector4f(0.5f, 0.6f, 0.7f, 1.0f);

        m_GraphicsPipeline = std::make_unique<SGL::GraphicsPipeline>(info);
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

        m_GraphicsPipeline->ClearBuffer();
        m_GraphicsPipeline->DrawElements(0, triangle.GetIndices());
    }

private:
    Mesh triangle;
    std::shared_ptr<ColorShaderProgram> shader;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleTriangle>("Example Triangle", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}