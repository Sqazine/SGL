#pragma once
#include <memory>
#include <vector>
#include <cassert>

class ExampleFPCamera : public Scene
{

public:
    ExampleFPCamera() : cube(Mesh(MeshType::CUBE)) {}
    ~ExampleFPCamera() {}

    void Init() override
    {
        Scene::Init();

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

        texture = SGL::Texture2D(texture2DCreateInfo);

        shader = std::make_shared<TexturedShaderProgram>();
        shader->positions = cube.GetPositions();
        shader->texcoords = cube.GetTexcoords();

        auto frameExtent = m_OwnerApp->GetFrameExtent();

        fpCamera = std::make_shared<FPCamera>(SGL::Math::ToRadian(60), frameExtent.x / frameExtent.y, 0.1f, 1000.0f);

        SGL::GraphicsPipelineCreateInfo info;
        info.defaultBufferExtent = frameExtent;
        info.shaderProgram = shader.get();
        info.renderType = SGL::RenderType::SOLID_TRIANGLE;
        info.clearBufferType = SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER;
        info.clearColor = SGL::Vector4f(0.5f, 0.6f, 0.7f, 1.0f);

        m_GraphicsPipeline = std::make_unique<SGL::GraphicsPipeline>(info);
    }

    void ProcessInput(InputSystem *inputSystem) override
    {
        inputSystem->GetMouse()->SetReleativeMode(true);

        Scene::ProcessInput(inputSystem);

        fpCamera->ProcessInput(inputSystem);
    }
    void Update() override
    {
        Scene::Update();

        fpCamera->Update();
    }
    void Draw() override
    {
        Scene::Draw();

        shader->texture = texture;
        shader->modelMatrix = modelMatrix;
        shader->viewMatrix = fpCamera->GetViewMatrix();
        shader->projectionMatrix = fpCamera->GetProjectionMatrix();
        m_GraphicsPipeline->ClearBuffer();
        m_GraphicsPipeline->DrawElements(0, cube.GetIndices());
    }

private:
    std::shared_ptr<FPCamera> fpCamera;
    Mesh cube;
    SGL::Matrix4f modelMatrix;
    std::shared_ptr<TexturedShaderProgram> shader;
    SGL::Texture2D texture;
};