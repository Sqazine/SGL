#pragma once
#include "SGL.h"
#include "texture/Texture.h"
class BlinnPhongShader
	: SGLShader
{
public:
	BlinnPhongShader();
	~BlinnPhongShader();

	SGLVertex VertexShader(const SGLVertex &modelVertex) override;
	SGLVector4f FragmentShader(const SGLVertex &screenVertex, const SGLVector2u32 &bufferExtent) override;

	SGLMatrix4f m_WorldMatrix;
	SGLMatrix4f m_ViewMatrix;
	SGLMatrix4f m_ProjectionMatrix;

	std::shared_ptr<Texture> m_DiffuseTexture;
	std::shared_ptr<Texture> m_SpecularTexture;
	std::shared_ptr<Texture> m_NormalTexture;
};
