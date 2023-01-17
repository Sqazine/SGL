#include "Application.h"
#include "Timer.h"
#include "Camera.h"
#include <chrono>

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
		ProcessInput();
		PreUpdate();
		Update();
		PostUpdate();
		Draw();
		GenerateFrame();
	}
	CleanUp();
}

void Application::RegisterScene(Scene *scene)
{
	scene->m_OwnerApp = this;
	m_Scenes.emplace_back(scene);
}

void Application::Init()
{
	m_Status = ApplicationStatus::INIT;

	m_Window = std::make_shared<Window>(m_AppName, m_FrameExtent);

	m_InputSystem = std::make_shared<InputSystem>();

	for (auto &scene : m_Scenes)
		scene->Init();
}

void Application::ProcessInput()
{
	m_InputSystem->ProcessInput();
	if (m_CurrentSceneIndex < m_Scenes.size())
		m_Scenes[m_CurrentSceneIndex]->ProcessInput(m_InputSystem.get());
}

void Application::PreUpdate()
{
	Timer::CalcDeltaTime();
	m_InputSystem->PreUpdate();
}

void Application::Update()
{
	if (m_CurrentSceneIndex < m_Scenes.size())
		m_Scenes[m_CurrentSceneIndex]->Update();
}

void Application::PostUpdate()
{
	m_InputSystem->PostUpdate();
}

void Application::Draw()
{
	if (m_CurrentSceneIndex < m_Scenes.size())
		m_Scenes[m_CurrentSceneIndex]->Draw();
}

void Application::CleanUp()
{
	m_Status = ApplicationStatus::EXIT;

	for (auto &scene : m_Scenes)
		scene->CleanUp();
}

void Application::GenerateFrame()
{
	if (m_CurrentSceneIndex >= m_Scenes.size())
		return;

	auto graphicsPipeline = m_Scenes[m_CurrentSceneIndex]->GetGraphicsPipeline();

	if (!graphicsPipeline)
		return;

	auto framebuffer = graphicsPipeline->GetFramebuffer();
	if (!framebuffer)
		return;

	auto colorAttachment = framebuffer->GetColorAttahment();
	if (!colorAttachment)
		return;

	auto bufferData = colorAttachment->GetBuffer().GetBufferData();
	if (bufferData.empty())
		return;

	m_Window->SetBufferData(bufferData.data());
}