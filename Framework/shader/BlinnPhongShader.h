#pragma once
#include "SGL/SGL.h"
#include "texture/Texture.h"
class BlinnPhongShader
	: SGL::Shader
{
public:
	BlinnPhongShader();
	~BlinnPhongShader();

	SGL::Vertex VertexShader(const SGL::Vertex &modelVertex) override;
	SGL::Vector4f FragmentShader(const SGL::Vertex &screenVertex, const SGL::Vector2u32 &bufferExtent) override;

	SGL::Matrix4f m_WorldMatrix;
	SGL::Matrix4f m_ViewMatrix;
	SGL::Matrix4f m_ProjectionMatrix;

	std::shared_ptr<Texture> m_DiffuseTexture;
	std::shared_ptr<Texture> m_SpecularTexture;
	std::shared_ptr<Texture> m_NormalTexture;

	SGL::Vector3f m_LightDir;
};
