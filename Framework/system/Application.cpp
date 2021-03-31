#include "Application.h"
#include "shader/BlinnPhongShader.h"
#include "utilities/Timer.h"
#include "camera/FPSCamera.h"

Application::Application(const std::string &appName, const SGL::Vector2u32 &frameExtent)
	: m_Status(ApplicationStatus::INIT), m_FrameExtent(frameExtent), m_AppName(appName)
{
}

Application::~Application()
{
}

void Application::Run()
{
	Init();
	while (m_Status != ApplicationStatus::EXIT)
	{
		m_Status = ApplicationStatus::RUN;
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
	m_Status = ApplicationStatus::INIT;
	//初始化SDL
	SDL_Init(SDL_INIT_VIDEO);

	m_Window = std::make_shared<Window>(m_AppName, m_FrameExtent);
	m_Rasterizer = std::make_shared<SGL::Rasterizer>(m_FrameExtent);

	m_InputSystem = std::make_shared<InputSystem>();

	m_SDLRenderer = SDL_CreateRenderer(m_Window->GetHandle(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	m_DefaultRenderTexture = SDL_CreateTexture(m_SDLRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, m_FrameExtent.x, m_FrameExtent.y);
}

void Application::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	m_InputSystem->ProcessInput(event);
}

void Application::PreUpdate()
{
	m_InputSystem->PreUpdate();
}

void Application::Update()
{
}

void Application::PostUpdate()
{
	m_InputSystem->PostUpdate();
}

void Application::Draw()
{
}

void Application::CleanUp()
{
	m_Status = ApplicationStatus::EXIT;
	SDL_DestroyRenderer(m_SDLRenderer);
	SDL_Quit();
}

void Application::GenerateFrame()
{
	SDL_UpdateTexture(m_DefaultRenderTexture, nullptr, m_Rasterizer->GetFramebuffer()->GetColorbuffer()->GetBuffer(), m_FrameExtent.x * 4);
	SDL_RenderCopy(m_SDLRenderer, m_DefaultRenderTexture, NULL, NULL);
	SDL_RenderPresent(m_SDLRenderer);
}
