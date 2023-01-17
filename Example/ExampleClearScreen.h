#pragma once
#include <memory>
#include "Scene.h"
#include "SGL/SGL.h"
#include "InputSystem.h"
#include "Application.h"
class ExampleClearScreen : public Scene
{

public:
	ExampleClearScreen() = default;
	~ExampleClearScreen() = default;

	void Init() override
	{
		SGL::GraphicsPipelineCreateInfo info;
		info.defaultBufferExtent = m_OwnerApp->GetFrameExtent();
		info.clearBufferType = SGL::BufferType::COLOR_BUFFER | SGL::BufferType::DEPTH_BUFFER;
		info.clearColor = SGL::Vector4f(0.5f, 0.6f, 0.7f, 1.0f);

		m_GraphicsPipeline = std::make_unique<SGL::GraphicsPipeline>(info);
	}

	void ProcessInput(InputSystem *inputSystem) override
	{
		Scene::ProcessInput(inputSystem);
	}
	void Draw() override
	{
		Scene::Draw();
		m_GraphicsPipeline->ClearBuffer();
	}
};