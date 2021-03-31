#include <memory>
#include "system/Application.h"
class ExampleClearScreen : public Application
{

public:
	ExampleClearScreen(const std::string &appName, const SGL::Vector2u32 &frameExtent) : Application(appName, frameExtent) {}
	~ExampleClearScreen() {}

	void ProcessInput() override
	{
		Application::ProcessInput();
		if (m_InputSystem->GetEventType() == SDL_QUIT || m_InputSystem->GetKeyboard()->GetKeyState(SDL_SCANCODE_ESCAPE) == BUTTON_STATE::PRESS)
			m_Status = ApplicationStatus::EXIT;
	}
	void Draw() override
	{
		Application::Draw();
		m_Rasterizer->ClearColor(0.5f, 0.6f, 0.7f, 1.0f);
		m_Rasterizer->ClearDepth();
	}
};

#undef main
int main(int argc, char **argv)
{
	std::unique_ptr<Application> app = std::make_unique<ExampleClearScreen>("Example Clear Screen", SGL::Vector2u32(800, 600));
	app->Run();
	return 0;
}