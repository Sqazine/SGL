#pragma once
#include <unordered_map>
#include <memory>
#include <windows.h>
#include <memory>
#include "Camera.h"
#include "Window.h"
#include "SGL/SGL.h"
#include "InputSystem.h"
#include "Scene.h"

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

	void RegisterScene(Scene* scene);

	SGL::Vector2u32 GetFrameExtent() const { return m_FrameExtent; }
protected:
	virtual void Init();
	virtual void ProcessInput();
	virtual void Update();
	virtual void Draw();
	virtual void CleanUp();

	ApplicationStatus m_Status;
	std::string m_AppName;

	SGL::Vector2u32 m_FrameExtent;
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<InputSystem> m_InputSystem;

	std::vector<std::unique_ptr<Scene>> m_Scenes;
	uint32_t m_CurrentSceneIndex{0};
private:
	void PreUpdate();
	void PostUpdate();
	void GenerateFrame();
};