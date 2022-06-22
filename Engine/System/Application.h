#pragma once
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>
#include "../Mesh/Model.h"
#include "../Camera/Camera.h"
#include "Window.h"
#include "SGL/SGL.h"
#include "InputSystem.h"

enum class ApplicationStatus
{
	INIT,
	RUN,
	EXIT
};

class Application
{
public:
	Application(const std::string &appName, const SGL::Vector2u32 &frameExtent);
	virtual ~Application();

	void Run();

protected:
	virtual void Init();
	virtual void ProcessInput();
	virtual void Update();
	virtual void Draw();
	virtual void CleanUp();

	ApplicationStatus m_Status;
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<SGL::GraphicsPipeline> m_GraphicsPipeline;
	std::shared_ptr<InputSystem> m_InputSystem;

	SGL::Vector2u32 m_FrameExtent;
	std::string m_AppName;

private:
	void PreUpdate();
	void PostUpdate();
	void GenerateFrame();

	SDL_Renderer *m_SDLRenderer;
	SDL_Texture *m_DefaultRenderTexture;
};
