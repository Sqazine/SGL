#pragma once
#include <unordered_map>
#include <memory>
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
private:
	void Init();
	void ProcessInput();
	void Update();
	void Draw();
	void CleanUp();

	void GenerateFrame();

	bool m_IsRunning;
	
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<SDL_Renderer> m_SDLRenderer;
	std::shared_ptr<SGLRasterizer> m_Rasterizer;


	uint32_t m_FrameWidth, m_FrameHeight;
	std::string m_AppName;
};

