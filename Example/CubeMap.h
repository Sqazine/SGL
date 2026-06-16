#pragma once
#include <memory>
#include <vector>
#include <cassert>
#include "Framework/Framework.h"

class CubeMapShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    CubeMapShaderProgram() = default;
    ~CubeMapShaderProgram() = default;

    uniform std::vector<SGL::Vector3f> positions;
    uniform SGL::Matrix4f modelMatrix;
    uniform SGL::Matrix4f viewMatrix;
    uniform SGL::Matrix4f projectionMatrix;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        varyings.CommitVector3fVarying("vTexcoord", positions[vertexIndex]);
        //viewMatrix.elements[12]=viewMatrix.elements[13]=viewMatrix.elements[14]=0.0f;
        return projectionMatrix * viewMatrix * SGL::Vector4f(positions[vertexIndex], 1.0f);
    }

    uniform SGL::TextureCube textureCube;

    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return textureCube.GetTexel(varyings.GetVector3fVarying("vTexcoord"));
    }
};

class CubeMap : public Scene
{

public:
    CubeMap() : cube(Mesh(MeshType::CUBE)) {}
    ~CubeMap() = default;

    void Init() override
    {
        Scene::Init();

        std::vector<std::string> filePaths;
        filePaths.resize(6, ASSET_DIR);
        filePaths[0].append("skybox/right.jpg");
        filePaths[1].append("skybox/left.jpg");
        filePaths[2].append("skybox/top.jpg");
        filePaths[3].append("skybox/bottom.jpg");
        filePaths[4].append("skybox/front.jpg");
        filePaths[5].append("skybox/back.jpg");

        int width, height, channel;
        stbi_set_flip_vertically_on_load(true);
        std::array<uint8_t *, 6> pixels;
        for (size_t i = 0; i < 6; ++i)
        {
            pixels[i] = stbi_load(filePaths[i].c_str(), &width, &height, &channel, STBI_default);
            assert(pixels[i] != nullptr);
        }

        SGL::TextureCubeCreateInfo textureCubeCreateInfo{};
        if (channel == STBI_rgb)
            textureCubeCreateInfo.channelMode = SGL::TextureChannelMode::RGB8;
        else if (channel == STBI_rgb_alpha)
            textureCubeCreateInfo.channelMode = SGL::TextureChannelMode::RGBA8;
        textureCubeCreateInfo.width = width;
        textureCubeCreateInfo.height = height;
        textureCubeCreateInfo.wrapModeS = SGL::TextureWrapMode::CLAMP_TO_EDGE;
        textureCubeCreateInfo.wrapModeT = SGL::TextureWrapMode::CLAMP_TO_EDGE;
        textureCubeCreateInfo.data[0] = pixels[0];
        textureCubeCreateInfo.data[1] = pixels[1];
        textureCubeCreateInfo.data[2] = pixels[2];
        textureCubeCreateInfo.data[3] = pixels[3];
        textureCubeCreateInfo.data[4] = pixels[4];
        textureCubeCreateInfo.data[5] = pixels[5];

        auto textureCube = SGL::TextureCube(textureCubeCreateInfo);

        auto frameExtent = m_OwnerApp->GetFrameExtent();

        fpCamera = std::make_shared<FPCamera>(SGL::Math::ToRadian(60), frameExtent.x / frameExtent.y, 0.1f, 1000.0f);

        shader = std::make_shared<CubeMapShaderProgram>();
        shader->positions = cube.GetPositions();
        shader->textureCube = textureCube;

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
        inputSystem->GetMouse()->SetReleativeMode(true);
        Scene::ProcessInput(inputSystem);

        fpCamera->ProcessInput(inputSystem);
        // inputSystem->GetMouse()->SetReleativeMode(false);
    }

    void Update() override
    {
        Scene::Update();
        fpCamera->Update();
    }
    void Draw() override
    {
        Scene::Draw();
        shader->viewMatrix = fpCamera->GetViewMatrix();
        shader->projectionMatrix = fpCamera->GetProjectionMatrix();
        m_GraphicsPipeline->ClearBuffer();
        m_GraphicsPipeline->DrawElements(0, cube.GetIndices());
    }

private:
    Mesh cube;
    std::shared_ptr<FPCamera> fpCamera;
    std::shared_ptr<CubeMapShaderProgram> shader;
};