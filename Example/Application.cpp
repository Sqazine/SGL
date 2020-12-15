#include "Application.h"
#include "BlinnPhongShader.h"
#include "Timer.h"
#include "FPSCamera.h"

Application::Application(const std::string& appName,uint32_t frameWidth, uint32_t frameHeight)
	:m_IsRunning(true),m_IsFocusWindow(false),m_AppName(appName),m_FrameWidth(frameWidth),m_FrameHeight(frameHeight)
{

}

Application::~Application()
{
}

void Application::Run()
{
	Init();
	while (m_IsRunning)
	{
		//计算增量时间
		Timer::CalcDeltaTime();
		ProcessInput();
		Update();
		Draw();
		GenerateFrame();
	}
	CleanUp();
}

void Application::Init()
{
	//初始化SDL
	SDL_Init(SDL_INIT_VIDEO);

	m_Window = std::make_shared<Window>(m_AppName, m_FrameWidth, m_FrameHeight);

	m_SDLRenderer =std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_Window->GetHandle(), -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED));
	m_Rasterizer = std::make_shared<SGLRasterizer>(m_FrameWidth,m_FrameHeight);

	if (m_IsFocusWindow)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else SDL_SetRelativeMouseMode(SDL_FALSE);

}

void Application::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case  SDL_QUIT:
		m_IsRunning = false;
	}

	const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
	if (keyboardState[SDL_SCANCODE_ESCAPE])
		m_IsRunning = false;
}

void Application::CleanUp()
{
	//SDL_DestroyRenderer(m_SDLRenderer.get());
	SDL_Quit();
}


void Application::GenerateFrame()
{
	for (uint32_t x = 0; x < m_FrameWidth; ++x)
	{
		for (uint32_t y = 0; y < m_FrameHeight; ++y)
		{
			SGLVector4u8 color = m_Rasterizer->GetFramebuffer()->GetColorbuffer()->GetValue(x, y);
			SDL_SetRenderDrawColor(m_SDLRenderer.get(), color.x, color.y, color.z, color.w);
			SDL_RenderDrawPoint(m_SDLRenderer.get(), x, m_FrameHeight - 1 - y);
		}
	}
	SDL_RenderPresent(m_SDLRenderer.get());
}
