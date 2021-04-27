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

    SGL::Vector4f VertexShader(const SGL::Vertex& vertex,SGL::Varyings &varyings) override
    {
        varyings.CommitVector2fVarying("vTexcoord",vertex.texcoord);
        return vertex.position;
    }

    uniform SGL::Texture2D texture;

    SGL::Vector4f FragmentShader(const SGL::Varyings& varyings) override
    {
        return texture.GetTexel(varyings.GetVector2fVarying("vTexcoord"));
    }
};
class ExampleIndexQuadWithTexture : public Application
{

public:
    ExampleIndexQuadWithTexture(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent) {}
    ~ExampleIndexQuadWithTexture() {}

    void Init() override
    {
        Application::Init();
        SGL::Vertex v0;
        v0.position = SGL::Vector3(-0.5f, 0.5f, 0.0f);
        v0.texcoord = SGL::Vector2f(0.0f, 1.0f);
        v0.color = SGL::Vector3f(1.0f, 0.0f, 0.0f);
        SGL::Vertex v1;
        v1.position = SGL::Vector3(-0.5f, -0.5f, 0.0f);
        v1.texcoord = SGL::Vector2f(0.0f, 0.0f);
        v1.color = SGL::Vector3f(1.0f, 1.0f, 1.0f);
        SGL::Vertex v2;
        v2.position = SGL::Vector3(0.5f, -0.5f, 0.0f);
        v2.texcoord = SGL::Vector2f(1.0f, 0.0f);
        v2.color = SGL::Vector3f(0.0f, 1.0f, 0.0f);
        SGL::Vertex v3;
        v3.position = SGL::Vector3(0.5f, 0.5f, 0.0f);
        v3.texcoord = SGL::Vector2f(1.0f, 1.0f);
        v3.color = SGL::Vector3f(0.0f, 0.0f, 1.0f);

        vertices = {v0, v1, v2, v3};

        indices = {
            0, 1, 2,
            0, 2, 3};

        //image from https://pixabay.com/photos/statue-sculpture-figure-1275469/
        std::string filePath = ASSET_DIR;
        filePath.append("statue-1275469_640.jpg");

        int width, height, channel;
        stbi_set_flip_vertically_on_load(true);
        uint8_t *pixels = stbi_load(filePath.c_str(), &width, &height, &channel, STBI_default);
        assert(pixels != nullptr);
        auto texture = SGL::Texture2D(std::vector<uint8_t>(pixels, pixels + (width * height * channel)), width, height, channel);

        auto shader = std::make_shared<TextureShaderProgram>();
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
        m_Rasterizer->ClearColor(0.5f, 0.6f, 0.7f, 1.0f);
        m_Rasterizer->ClearDepth();

        m_Rasterizer->DrawElements(SGL::RENDER_MODE::SOLID_TRIANGLE, 0, vertices, indices);
    }

private:
    std::vector<SGL::Vertex> vertices;
    std::vector<uint32_t> indices;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleIndexQuadWithTexture>("Example Index Quad With Texture", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}