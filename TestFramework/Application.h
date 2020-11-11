#pragma once
#include <unordered_map>
#include <SDL2/SDL.h>
#include "Model.h"
#include "Camera.h"
#include "Window.h"
class Application
{
public:
	Application(const std::string& appName, uint32_t frameWidth, uint32_t frameHeight);
	~Application();


	void Run();
protected:
	virtual void Init();
	virtual void ProcessInput();
	virtual void Update() {}
	virtual void Draw() {};
	virtual void CleanUp();

	std::shared_ptr<SGLRasterizer> m_Rasterizer;
private:
	void GenerateFrame();

	bool m_IsRunning;
	bool m_IsFocusWindow;


	std::shared_ptr<Window> m_Window;
	std::shared_ptr<SDL_Renderer> m_SDLRenderer;


	uint32_t m_FrameWidth, m_FrameHeight;
	std::string m_AppName;
};

