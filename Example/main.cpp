#include <memory>
#include "Application.h"
#include "Camera.h"
#include "../libSGL/libSGL.h"

class PureColorShader :
	public SGLShader
{
public:
	PureColorShader() {}
	~PureColorShader() {}

	SGLVertex VertexShader(const SGLVertex& modelVertex) override
	{
		return modelVertex;
	}
	SGLVector4f FragmentShader(const SGLVertex& screenVertex /* = SGLVertex() */, uint32_t bufferWidth /* = 0 */, uint32_t bufferHeight /* = 0 */) override
	{
		return SGLVector4f(1.0f);
	}
};



class ExampleTriangle:public Application 
{
public:
	ExampleTriangle(const std::string& exampleName,uint32_t windowWidth,uint32_t windowHeight) :Application(exampleName,windowWidth,windowHeight){}
private:
	void Init() override
	{
		Application::Init();
	}

	void Draw() override
	{
		m_Rasterizer->ClearColor(0.5f, 0.6f, 0.7f, 1.0f);
		m_Rasterizer->ClearDepth();
	}

	std::shared_ptr<PureColorShader> m_Shader;
	std::shared_ptr<Model> m_Model;
};

#undef main
int main(int argc, char** argv)
{
	std::unique_ptr<ExampleTriangle> exampleTriangle = std::make_unique<ExampleTriangle>("Example-Triangle",800, 600);
	exampleTriangle->Run();
	return 0;
}