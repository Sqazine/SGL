#pragma once
#include <memory>
#include <vector>
#include <cassert>
#include "Framework/Framework.h"
#include "Common.h"

class DrawCube : public Scene
{
public:
    DrawCube() : cube(Mesh(MeshType::CUBE)) {}
    ~DrawCube() = default;

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

        viewMatrix = SGL::Matrix4f::LookAt(SGL::Vector3f(0.0f, 1.0f, 3.0f), SGL::Vector3f(0.0f), SGL::Vector3f::UNIT_Y);
        projectionMatrix = SGL::Matrix4f::GLPerspective(SGL::Math::ToRadian(45.0f), 800 / 600.0f, 0.1f, 100.0f);

        shader = std::make_shared<TexturedShaderProgram>();
        shader->positions = cube.GetPositions();
        shader->texcoords = cube.GetTexcoords();

        SGL::GraphicsPipelineCreateInfo info;
        info.defaultBufferExtent = m_OwnerApp->GetFrameExtent();
        info.shaderProgram = shader.get();
        info.renderType = SGL::RenderType::SOLID_TRIANGLE;
        info.clearBufferType = SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER;
        info.clearColor = SGL::Vector4f(0.5f, 0.6f, 0.7f, 1.0f);

        m_GraphicsPipeline = std::make_unique<SGL::GraphicsPipeline>(info);
    }

    void ProcessInput(InputSystem* inputSystem) override
    {
        Scene::ProcessInput(inputSystem);
    }
    void Update() override
    {
        Scene::Update();

        rotation.y -= 100 * Timer::deltaTime;

        modelMatrix = SGL::Matrix4f();
        modelMatrix *= SGL::Matrix4f::Rotate(SGL::Vector3f(1.0f, 0.0f, 0.0f), SGL::Math::ToRadian(rotation.x));
        modelMatrix *= SGL::Matrix4f::Rotate(SGL::Vector3f(0.0f, 1.0f, 0.0f), SGL::Math::ToRadian(rotation.y));
        modelMatrix *= SGL::Matrix4f::Rotate(SGL::Vector3f(0.0f, 0.0f, 1.0f), SGL::Math::ToRadian(rotation.z));
    }
    void Draw() override
    {
        Scene::Draw();

        shader->texture = texture;
        shader->modelMatrix = modelMatrix;
        shader->viewMatrix = viewMatrix;
        shader->projectionMatrix = projectionMatrix;

        m_GraphicsPipeline->ClearBuffer();
        m_GraphicsPipeline->DrawElements(0, cube.GetIndices());
    }

private:
    SGL::Vector3f rotation;
    Mesh cube;
    SGL::Matrix4f modelMatrix;
    SGL::Matrix4f viewMatrix;
    SGL::Matrix4f projectionMatrix;
    std::shared_ptr<TexturedShaderProgram> shader;
    SGL::Texture2D texture;
};