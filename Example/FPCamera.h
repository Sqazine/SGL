#pragma once
#include <memory>
#include <vector>
#include <cassert>
#include "Framework/Framework.h"

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
        return projectionMatrix * viewMatrix * modelMatrix * SGL::Vector4f(positions[vertexIndex], 1.0f);
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

class ExampleFPCamera : public Scene
{

public:
    ExampleFPCamera(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent), cube(Mesh(MeshType::CUBE)) {}
    ~ExampleFPCamera() {}

    void Init() override
    {
        Scene::Init();

        m_InputSystem->GetMouse()->SetReleativeMode(true);

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

        shader = std::make_shared<TextureShaderProgram>();
        shader->positions = cube.GetPositions();
        shader->texcoords = cube.GetTexcoords();

        fpCamera = std::make_shared<FPCamera>(SGL::Math::ToRadian(60), m_FrameExtent.x / m_FrameExtent.y, 0.1f, 1000.0f);

        SGL::GraphicsPipelineCreateInfo info;
        info.defaultBufferExtent = m_FrameExtent;
        info.shaderProgram = shader.get();
        info.renderType = SGL::RenderType::SOLID_TRIANGLE;
        info.clearBufferType = SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER;
        info.clearColor = SGL::Vector4f(0.5f, 0.6f, 0.7f, 1.0f);

        m_GraphicsPipeline = std::make_unique<SGL::GraphicsPipeline>(info);
    }

    void ProcessInput(InputSystem* inputSystem) override
    {
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
    std::shared_ptr<TextureShaderProgram> shader;
    SGL::Texture2D texture;
};