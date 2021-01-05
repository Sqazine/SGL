#pragma once
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>
#include "mesh/Model.h"
#include "camera/Camera.h"
#include "Window.h"
#include "SGL.h"
class Application
{
public:
	Application(const std::string& appName, const SGLVector2u32& frameExtent);
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
	SDL_Renderer* m_SDLRenderer;
	std::shared_ptr<SGLRasterizer> m_Rasterizer;
	
	SGLVector2u32 m_FrameExtent;
	std::string m_AppName;
};

