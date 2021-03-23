#pragma once
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>
#include "mesh/Model.h"
#include "camera/Camera.h"
#include "Window.h"
#include "SGL/SGL.h"
class Application
{
public:
	Application(const std::string& appName, const SGL::Vector2u32& frameExtent);
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
	std::shared_ptr<SGL::Rasterizer> m_Rasterizer;
	
	SGL::Vector2u32 m_FrameExtent;
	std::string m_AppName;


	SDL_Renderer* m_SDLRenderer;
	SDL_Texture* m_DefaultRenderTexture;
};

