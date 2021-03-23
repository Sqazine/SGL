#include "Application.h"
#include "shader/BlinnPhongShader.h"
#include "utilities/Timer.h"
#include "camera/FPSCamera.h"

Application::Application(const std::string &appName, const SGL::Vector2u32 &frameExtent)
	: m_IsRunning(true), m_AppName(appName), m_FrameExtent(frameExtent)
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

	m_SDLRenderer = SDL_CreateRenderer(m_Window->GetHandle(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	m_DefaultRenderTexture = SDL_CreateTexture(m_SDLRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, m_FrameExtent.x, m_FrameExtent.y);

	m_Rasterizer = std::make_shared<SGL::Rasterizer>(m_FrameExtent);
}

void Application::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_IsRunning = false;
	}

	const uint8_t *keyboardState = SDL_GetKeyboardState(nullptr);
	if (keyboardState[SDL_SCANCODE_ESCAPE])
		m_IsRunning = false;
}

void Application::Update()
{
	m_Rasterizer->ClearColor(0.5f, 0.6f, 0.7f, 1.0f);
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
	SDL_UpdateTexture(m_DefaultRenderTexture, nullptr, m_Rasterizer->GetFramebuffer()->GetColorbuffer()->GetBuffer(), m_FrameExtent.x * 4);
	SDL_RenderCopy(m_SDLRenderer, m_DefaultRenderTexture, NULL, NULL);
	SDL_RenderPresent(m_SDLRenderer);
}
