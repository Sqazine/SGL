#include "Application.h"
#include "shader/BlinnPhongShader.h"
#include "utilities/Timer.h"
#include "camera/FPSCamera.h"

Application::Application(const std::string& appName, const SGL::Vector2u32& frameExtent)
	:m_IsRunning(true),m_AppName(appName),m_FrameExtent(frameExtent)
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

	m_Window = std::make_shared<Window>(m_AppName, m_FrameExtent);

	m_SDLRenderer =SDL_CreateRenderer(m_Window->GetHandle(), -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
	m_Rasterizer = std::make_shared<SGL::Rasterizer>(m_FrameExtent);
	
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

void Application::Update()
{
	m_Rasterizer->ClearColor(0.5f,0.6f,0.7f,1.0f);
	m_Rasterizer->ClearDepth();
}

void Application::Draw()
{
	
}
	

void Application::CleanUp()
{
	SDL_DestroyRenderer(m_SDLRenderer);
	SDL_Quit();
}


void Application::GenerateFrame()
{
	for (uint32_t x = 0; x < m_FrameExtent.x; ++x)
	{
		for (uint32_t y = 0; y < m_FrameExtent.y; ++y)
		{
			SGL::Vector4u8 color = m_Rasterizer->GetFramebuffer()->GetColorbuffer()->GetValue(x, y);
			SDL_SetRenderDrawColor(m_SDLRenderer, color.x, color.y, color.z, color.w);
			SDL_RenderDrawPoint(m_SDLRenderer, x, m_FrameExtent.y - 1 - y);
		}
	}
	SDL_RenderPresent(m_SDLRenderer);
}
