#pragma once
#include <memory>
#include "Framework/Framework.h"
class ClearScreen : public Scene
{

public:
	ClearScreen() = default;
	~ClearScreen() = default;

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