#pragma once
#include <memory>
#include <vector>
#include <cassert>
#include "Framework/Framework.h"
#include "Common.h"

class TriangleWithTexture : public Scene
{

public:
    TriangleWithTexture() : triangle(Mesh(MeshType::TRIANGLE)) {}
    ~TriangleWithTexture() {}

    void Init() override
    {
        Scene::Init();

        //image from https://pixabay.com/photos/statue-sculpture-figure-1275469/
        image2D = IO::LoadImage2D<uint8_t>(ASSET_DIR "statue-1275469_640.jpg", true);

        SGL::Texture2DCreateInfo texture2DCreateInfo{};
        if (image2D.channel == STBI_rgb)
            texture2DCreateInfo.channelMode = SGL::TextureChannelMode::RGB8;
        else if (image2D.channel == STBI_rgb_alpha)
            texture2DCreateInfo.channelMode = SGL::TextureChannelMode::RGBA8;
        texture2DCreateInfo.width = image2D.width;
        texture2DCreateInfo.height = image2D.height;
        texture2DCreateInfo.wrapModeS = SGL::TextureWrapMode::REPEAT;
        texture2DCreateInfo.wrapModeT = SGL::TextureWrapMode::REPEAT;
        texture2DCreateInfo.data = image2D.pixels.data();

        texture = SGL::Texture2D(texture2DCreateInfo);

        shader = std::make_shared<TexturedShaderProgram>();
        shader->positions = triangle.GetPositions();
        shader->texcoords = triangle.GetTexcoords();
        shader->texture = texture;

        SGL::GraphicsPipelineCreateInfo info;
        info.defaultBufferExtent = m_OwnerApp->GetFrameExtent();
        info.shaderProgram = shader.get();
        info.renderType = SGL::RenderType::SOLID_TRIANGLE;
        info.clearBufferType = SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER;
        info.clearColor = SGL::Vector4f(0.5f, 0.6f, 0.7f, 1.0f);

        m_GraphicsPipeline = std::make_unique<SGL::GraphicsPipeline>(info);
    }

    void ProcessInput(InputSystem *inputSystem) override
    {
        Scene::ProcessInput(inputSystem);
    }
    void Update() override
    {
        Scene::Update();
    }
    void Draw() override
    {
        Scene::Draw();

        m_GraphicsPipeline->ClearBuffer();
        m_GraphicsPipeline->DrawElements(0, triangle.GetIndices());
    }

private:
    Mesh triangle;
    std::shared_ptr<TexturedShaderProgram> shader;

    Image2D<uint8_t> image2D;
    SGL::Texture2D texture;
};