#include <memory>
#include <vector>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Engine/Engine.h"
#include "SGL/SGL.h"

class TextureShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    TextureShaderProgram() {}
    ~TextureShaderProgram() {}

    uniform std::vector<SGL::Vector3f> positions;
    uniform std::vector<SGL::Vector2f> texcoords;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        varyings.CommitVector2fVarying("vTexcoord", texcoords[vertexIndex]);
        return SGL::Vector4f(positions[vertexIndex], 1.0f);
    }

    uniform SGL::Texture2D texture;

    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return texture.GetTexel(varyings.GetVector2fVarying("vTexcoord"));
    }
};
class ExampleIndexQuadWithTexture : public Application
{

public:
    ExampleIndexQuadWithTexture(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent), quad(Mesh(MeshType::QUAD)) {}
    ~ExampleIndexQuadWithTexture() {}

    void Init() override
    {
        Application::Init();

        //image from https://pixabay.com/photos/statue-sculpture-figure-1275469/
        std::string filePath = ASSET_DIR;
        filePath.append("statue-1275469_640.jpg");

        int width, height, channel;
        stbi_set_flip_vertically_on_load(true);
        uint8_t *pixels = stbi_load(filePath.c_str(), &width, &height, &channel, STBI_default);
        assert(pixels != nullptr);

        SGL::Texture2DCreateInfo texture2DCreateInfo{};
        if (channel == STBI_rgb)
            texture2DCreateInfo.channelMode = SGL::TextureChannelMode::RGB8;
        else if (channel == STBI_rgb_alpha)
            texture2DCreateInfo.channelMode = SGL::TextureChannelMode::RGBA8;
        texture2DCreateInfo.width = width;
        texture2DCreateInfo.height = height;
        texture2DCreateInfo.wrapModeS = SGL::TextureWrapMode::REPEAT;
        texture2DCreateInfo.wrapModeT = SGL::TextureWrapMode::REPEAT;
        texture2DCreateInfo.data = pixels;

        auto texture = SGL::Texture2D(texture2DCreateInfo);
        auto shader = std::make_shared<TextureShaderProgram>();
        shader->positions = quad.GetPositions();
        shader->texcoords = quad.GetTexcoords();
        shader->texture = texture;

        m_GraphicsPipeline->SetGraphicsShaderProgram(shader);
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
        m_GraphicsPipeline->SetClearColor(0.5f, 0.6f, 0.7f, 1.0f);
        m_GraphicsPipeline->Clear(SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER);

        m_GraphicsPipeline->DrawElements(SGL::RenderType::SOLID_TRIANGLE, 0, quad.GetIndices());
    }

private:
    Mesh quad;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleIndexQuadWithTexture>("Example Quad With Texture", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}