#pragma once
#include <memory>
#include <vector>
#include "Framework/Framework.h"
#include "SGL/SGL.h"

class TriangleShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    TriangleShaderProgram() = default;
    ~TriangleShaderProgram() = default;

    uniform std::vector<SGL::Vector3f> positions;
    uniform std::vector<SGL::Vector4f> vertexColors;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        varyings.CommitVector4fVarying("vColor", vertexColors[vertexIndex]);
        return SGL::Vector4f(positions[vertexIndex], 1.0f);
    }
    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return varyings.GetVector4fVarying("vColor");
    }
};

class Triangle : public Scene
{
public:
    Triangle() : triangle(Mesh(MeshType::TRIANGLE)) {}
    ~Triangle() {}

    void Init() override
    {
        Scene::Init();

        shader = std::make_shared<TriangleShaderProgram>();
        shader->positions = triangle.GetPositions();
        shader->vertexColors = triangle.GetVertexColors();

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
    std::shared_ptr<TriangleShaderProgram> shader;
};