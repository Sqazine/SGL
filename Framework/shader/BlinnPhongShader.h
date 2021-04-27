#pragma once
#include "SGL/SGL.h"
#include "texture/Texture.h"
class BlinnPhongShaderProgram
	: SGL::GraphicsShaderProgram
{
public:
	BlinnPhongShaderProgram();
	~BlinnPhongShaderProgram();

	SGL::Vector4f VertexShader(const SGL::Vertex &vertex, SGL::Varyings &varyings) override;
	SGL::Vector4f FragmentShader(SGL::Varyings varyings) override;

	SGL::Matrix4f m_WorldMatrix;
	SGL::Matrix4f m_ViewMatrix;
	SGL::Matrix4f m_ProjectionMatrix;

	std::shared_ptr<Texture> m_DiffuseTexture;
	std::shared_ptr<Texture> m_SpecularTexture;
	std::shared_ptr<Texture> m_NormalTexture;

	SGL::Vector3f m_LightDir;
};
