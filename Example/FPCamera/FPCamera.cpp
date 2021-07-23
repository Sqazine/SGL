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
        varyings.CommitVector2fVarying("vTexcoord", vertices[vertexIndex].texcoord);
        return projectionMatrix * viewMatrix * modelMatrix * vertices[vertexIndex].position;
    }

    uniform SGL::Texture2D texture;
    uniform SGL::Matrix4f modelMatrix;
    uniform SGL::Matrix4f viewMatrix;
    uniform SGL::Matrix4f projectionMatrix;

    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return texture.GetTexel(varyings.GetVector2fVarying("vTexcoord"));
    }
};

class ExampleFPCamera : public Application
{

public:
    ExampleFPCamera(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent) {}
    ~ExampleFPCamera() {}

    void Init() override
    {
        Application::Init();

        m_InputSystem->GetMouse()->SetReleativeMode(true);

        cube = std::make_shared<Mesh>(MeshType::CUBE);

        //image from https://pixabay.com/photos/statue-sculpture-figure-1275469/
        std::string filePath = ASSET_DIR;
        filePath.append("statue-1275469_640.jpg");

        int width, height, channel;
        stbi_set_flip_vertically_on_load(true);
        uint8_t *pixels = stbi_load(filePath.c_str(), &width, &height, &channel, STBI_default);
        assert(pixels != nullptr);

        texture = SGL::Texture2D(std::vector<uint8_t>(pixels, pixels + (width * height * channel)), width, height, channel);

        shader = std::make_shared<TextureShaderProgram>();
        shader->vertices = cube->GetVertices();

        fpCamera=std::make_shared<FPCamera>(SGL::Math::ToRadian(60),m_FrameExtent.x/m_FrameExtent.y,0.1f,1000.0f);
    }

    void ProcessInput() override
    {
        Application::ProcessInput();
        if (m_InputSystem->GetEventType() == SDL_QUIT || m_InputSystem->GetKeyboard()->GetKeyState(KEYCODE_ESCAPE) == BUTTON_STATE::PRESS)
            m_Status = ApplicationStatus::EXIT;

        fpCamera->ProcessInput(m_InputSystem);
    }
    void Update() override
    {
        Application::Update();

        fpCamera->Update();
    }
    void Draw() override
    {
        Application::Draw();
         m_Rasterizer->SetClearColor(0.5f, 0.6f, 0.7f, 1.0f);
        m_Rasterizer->Clear(SGL::BufferType::COLOR_BUFFER|SGL::BufferType::DEPTH_BUFFER);


        shader->texture = texture;
        shader->modelMatrix = modelMatrix;
        shader->viewMatrix = fpCamera->GetViewMatrix();
        shader->projectionMatrix = fpCamera->GetProjectionMatrix();
        m_Rasterizer->SetGraphicsShaderProgram(shader);
        m_Rasterizer->DrawElements(SGL::RenderMode::SOLID_TRIANGLE, 0, cube->GetIndices());
    }

private:
    std::shared_ptr<FPCamera> fpCamera;
    std::shared_ptr<Mesh> cube;
    SGL::Matrix4f modelMatrix;
    std::shared_ptr<TextureShaderProgram> shader;
    SGL::Texture2D texture;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleFPCamera>("Example First-Person Camera", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}