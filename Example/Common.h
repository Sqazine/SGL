#pragma once

struct Light
{
    SGL::Vector3f position;
    SGL::Vector3f ambient;
    SGL::Vector3f diffuse;
    SGL::Vector3f specular;
};

class TexturedShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    TexturedShaderProgram() = default;
    ~TexturedShaderProgram() = default;

    uniform std::vector<SGL::Vector3f> positions;
    uniform std::vector<SGL::Vector2f> texcoords;

    uniform SGL::Matrix4f modelMatrix;
    uniform SGL::Matrix4f viewMatrix;
    uniform SGL::Matrix4f projectionMatrix;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        varyings.CommitVector2fVarying("vTexcoord", texcoords[vertexIndex]);
        return projectionMatrix * viewMatrix * modelMatrix * SGL::Vector4f(positions[vertexIndex], 1.0f);
    }

    uniform SGL::Texture2D texture;

    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        return texture.GetTexel(varyings.GetVector2fVarying("vTexcoord"));
    }
};