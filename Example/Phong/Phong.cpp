#include <memory>
#include <vector>
#include "Framework/Framework.h"
#include "SGL/SGL.h"

struct Light
{
    SGL::Vector3f position;
    SGL::Vector3f ambient;
    SGL::Vector3f diffuse;
    SGL::Vector3f specular;
};

struct PhongMaterial
{
    SGL::Vector3f ambient;
    SGL::Vector3f diffuse;
    SGL::Vector3f specular;
    float shiness;
};

class PhongShaderProgram
    : public SGL::GraphicsShaderProgram
{
public:
    PhongShaderProgram() {}
    ~PhongShaderProgram() {}

    uniform std::vector<Vertex> vertices;

    uniform SGL::Matrix4f modelMatrix;
    uniform SGL::Matrix4f viewMatrix;
    uniform SGL::Matrix4f projectionMatrix;

    SGL::Vector4f VertexShader(uint32_t vertexIndex, SGL::Varyings &varyings) override
    {
        Vertex vertex = vertices[vertexIndex];
        SGL::Vector4f vPositionWS = modelMatrix * vertex.position;
        varyings.CommitVector3fVarying("vNormalWS", SGL::Vector3f::Normalize(SGL::Matrix4f::ToMatrix3(SGL::Matrix4f::Transpose(SGL::Matrix4f::Inverse(modelMatrix))) * vertex.normal));
        varyings.CommitVector3fVarying("vPositionWS", SGL::Vector4f::ToVector3(vPositionWS));
        varyings.CommitVector2fVarying("vTexcoord", vertex.texcoord);
        return projectionMatrix * viewMatrix * vPositionWS;
    }

    uniform PhongMaterial material;
    uniform Light light;
    uniform SGL::Vector3f viewPosWS;

    SGL::Vector4f FragmentShader(const SGL::Varyings &varyings) override
    {
        SGL::Vector3f vNormalWS = varyings.GetVector3fVarying("vNormalWS");
        SGL::Vector2f vTexcoord = varyings.GetVector2fVarying("vTexcoord");
        SGL::Vector3f vPositionWS = varyings.GetVector3fVarying("vPositionWS");
        SGL::Vector3f viewDirWS = SGL::Vector3f::Normalize(viewPosWS - vPositionWS);
        SGL::Vector3f lightDirWS = SGL::Vector3f::Normalize(light.position);
        SGL::Vector3f reflectDir = Reflect(-lightDirWS, vNormalWS);

        SGL::Vector3f ambientPart = light.ambient * material.ambient;
        SGL::Vector3f diffusePart = light.diffuse * material.diffuse * SGL::Math::Max(SGL::Vector3f::Dot(vNormalWS, lightDirWS), 0.0f);                                      //lambertian
        SGL::Vector3f specularPart = light.specular * material.specular * SGL::Math::Pow(SGL::Math::Max(SGL::Vector3f::Dot(viewDirWS, reflectDir), 0.0f), material.shiness); //phong specular
        return SGL::Vector4f(ambientPart + diffusePart + specularPart, 1.0);
    }
};

class ExamplePhong : public Application
{

public:
    ExamplePhong(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent) {}
    ~ExamplePhong() {}

    void Init() override
    {
        Application::Init();
        sphere = std::make_shared<Mesh>(MeshType::SPHERE);

        auto shader = std::make_shared<PhongShaderProgram>();
        shader->vertices = sphere->GetVertices();
        shader->modelMatrix = SGL::Matrix4f();
        shader->viewMatrix = SGL::Matrix4f::Translate(SGL::Vector3f(0.0f, 0.0f, -3.0f));
        shader->projectionMatrix = SGL::Matrix4f::GLPerspective(SGL::Math::ToRadian(45.0f), 800 / 600.0f, 0.1f, 100.0f);
        //parameter from http://devernay.free.fr/cours/opengl/materials.html
        shader->material.ambient = SGL::Vector3f(1.0f, 0.5f, 0.31f);
        shader->material.diffuse = SGL::Vector3f(1.0f, 0.5f, 0.31f);
        shader->material.specular = SGL::Vector3f(0.5f);
        shader->material.shiness = 32.0f;
        shader->light.position = SGL::Vector3f(1.0f, 1.0f, 0.0f);
        shader->light.ambient = SGL::Vector3f(0.2f);
        shader->light.diffuse = SGL::Vector3f(1.0f);
        shader->light.specular = SGL::Vector3f(1.0f);
        shader->viewPosWS = SGL::Vector3f(0.0f, 0.0f, 3.0f);

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
          m_Rasterizer->SetClearColor(0.5f, 0.6f, 0.7f, 1.0f);
        m_Rasterizer->Clear(SGL::BufferType::COLOR_BUFFER|SGL::BufferType::DEPTH_BUFFER);

        m_Rasterizer->DrawElements(SGL::RenderType::SOLID_TRIANGLE, 0, sphere->GetIndices());
    }

private:
    std::shared_ptr<Mesh> sphere;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExamplePhong>("Example Phong", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}