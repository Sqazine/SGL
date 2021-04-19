#include <memory>
#include <vector>
#include "Framework.h"
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

class PhongShader
    : public SGL::Shader
{
public:
    PhongShader() {}
    ~PhongShader() {}

    uniform SGL::Matrix4f modelMatrix;
    uniform SGL::Matrix4f viewMatrix;
    uniform SGL::Matrix4f projectionMatrix;

    SGL::Vertex VertexShader(const SGL::Vertex &modelVertex) override
    {
        SGL::Vertex v=modelVertex;

        v.position= projectionMatrix*viewMatrix*modelMatrix*v.position;
        v.posWS=SGL::Vector4f::ToVector3(modelMatrix*v.position);
        v.normal=SGL::Matrix4f::ToMatrix3(SGL::Matrix4f::Transpose(SGL::Matrix4f::Inverse(modelMatrix)))*v.normal;
        return v;
    }

    uniform PhongMaterial material;
    uniform Light light;
    uniform SGL::Vector3f viewPosWS;
    SGL::Vector4f FragmentShader(const SGL::Vertex &screenVertex, const SGL::Vector2u32 &bufferExtent) override
    {

        auto normal=SGL::Vector3f::Normalize(screenVertex.normal);
        auto lightDir=SGL::Vector3f::Normalize(light.position-screenVertex.posWS);
        auto viewDir=SGL::Vector3f::Normalize(viewPosWS-screenVertex.posWS);
        auto reflectDir=Reflect(-lightDir,normal);

        auto ambientPart=light.ambient*material.ambient;
        auto diffusePart=light.diffuse*material.diffuse*SGL::Math::Max(SGL::Vector3f::Dot(normal,lightDir),0.0f);
        auto specularPart=light.specular*material.specular*SGL::Math::Pow(SGL::Math::Max(SGL::Vector3f::Dot(viewDir,reflectDir),0.0f),material.shiness);
        return SGL::Vector4f(ambientPart+diffusePart+specularPart,1.0);
    }
};

class ExampleTriangle : public Application
{

public:
    ExampleTriangle(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent) {}
    ~ExampleTriangle() {}

    void Init() override
    {
        Application::Init();
        sphere=std::make_shared<Mesh>(INTERNAL_MESH_TYPE::SPHERE);

        auto shader = std::make_shared<PhongShader>();
        shader->modelMatrix= SGL::Matrix4f();
        shader->viewMatrix= SGL::Matrix4f::Translate(SGL::Vector3f(0.0f, 0.0f, -3.0f));
        shader->projectionMatrix=SGL::Matrix4f::GLPerspective(SGL::Math::ToRadian(45.0f), 800 / 600.0f, 0.1f, 100.0f);
        //parameter from http://devernay.free.fr/cours/opengl/materials.html
        shader->material.ambient=SGL::Vector3f(1.0f,0.5f,0.31f);
        shader->material.diffuse=SGL::Vector3f(1.0f,0.5f,0.31f);
        shader->material.specular=SGL::Vector3f(0.5f);
        shader->material.shiness=32.0f;
        shader->light.position=SGL::Vector3f(1.0f,1.0f,1.0f);
        shader->light.ambient=SGL::Vector3f(0.2f);
        shader->light.diffuse=SGL::Vector3f(0.5f);
        shader->light.specular=SGL::Vector3f(1.0f);
        shader->viewPosWS=SGL::Vector3f(0.0f, 0.0f, 3.0f);

        m_Rasterizer->SetShader(shader);
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
        m_Rasterizer->ClearColor(0.5f, 0.6f, 0.7f, 1.0f);
        m_Rasterizer->ClearDepth();

        m_Rasterizer->DrawElements(SGL::RENDER_MODE::SOLID_TRIANGLE, 0,sphere->GetVertices(),sphere->GetIndices());
    }

private:
    std::shared_ptr<Mesh> sphere;
};

#undef main
int main(int argc, char **argv)
{
    std::unique_ptr<Application> app = std::make_unique<ExampleTriangle>("Example Phong", SGL::Vector2u32(800, 600));
    app->Run();
    return 0;
}