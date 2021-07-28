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

    uniform std::vector<Vertex> vertices;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        Vertex vertex=vertices[vertexIndex];
        varyings.CommitVector4fVarying("vColor", vertex.color);
        return vertex.position;
    }
    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return varyings.GetVector4fVarying("vColor");
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
       
        triangle=std::make_shared<Mesh>(MeshType::TRIANGLE);

        auto shader = std::make_shared<ColorShaderProgram>();
        shader->vertices=triangle->GetVertices();

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
         m_Rasterizer->SetClearColor(0.5f, 0.6f, 0.7f, 1.0f);
        m_Rasterizer->Clear(SGL::BufferType::COLOR_BUFFER|SGL::BufferType::DEPTH_BUFFER);
        m_Rasterizer->DrawElements(SGL::RenderType::SOLID_TRIANGLE, 0, triangle->GetIndices());
    }

private:
    std::shared_ptr<Mesh> triangle;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleTriangle>("Example Triangle", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}