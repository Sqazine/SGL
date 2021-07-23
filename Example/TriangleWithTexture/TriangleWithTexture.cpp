#include <memory>
#include <vector>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Framework/Framework.h"
#include "SGL/SGL.h"

class TextureShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    TextureShaderProgram() {}
    ~TextureShaderProgram() {}

    uniform std::vector<Vertex> vertices;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        Vertex vertex = vertices[vertexIndex];
        varyings.CommitVector2fVarying("vTexcoord", vertex.texcoord);
        return vertex.position;
    }

    uniform SGL::Texture2D texture;

    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return texture.GetTexel(varyings.GetVector2fVarying("vTexcoord"));
    }
};

class ExampleTriangleWithTexture : public Application
{

public:
    ExampleTriangleWithTexture(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent) {}
    ~ExampleTriangleWithTexture() {}

    void Init() override
    {
        Application::Init();

        triangle = std::make_shared<Mesh>(MeshType::TRIANGLE);

        //image from https://pixabay.com/photos/statue-sculpture-figure-1275469/
        std::string filePath = ASSET_DIR;
        filePath.append("statue-1275469_640.jpg");

        int width, height, channel;
        stbi_set_flip_vertically_on_load(true);
        uint8_t *pixels = stbi_load(filePath.c_str(), &width, &height, &channel, STBI_default);
        assert(pixels != nullptr);
        auto texture = SGL::Texture2D(std::vector<uint8_t>(pixels, pixels + (width * height * channel)), width, height, channel);

        auto shader = std::make_shared<TextureShaderProgram>();
        shader->vertices = triangle->GetVertices();
        shader->texture = texture;

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
        m_Rasterizer->Clear(SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER);

        m_Rasterizer->DrawElements(SGL::RenderMode::SOLID_TRIANGLE, 0, triangle->GetIndices());
    }

private:
    std::shared_ptr<Mesh> triangle;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleTriangleWithTexture>("Example Triangle With Texture", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}