#pragma once
#include "../libSGL/libSGL.h"
#include "Texture.h"
class BlinnPhongShader
	:SGLShader
{
public:
	BlinnPhongShader();
	~BlinnPhongShader();

	SGLVertex VertexShader(const SGLVertex& modelVertex) override;
	SGLVector4f FragmentShader(const SGLVertex& screenVertex,uint32_t bufferWidth, uint32_t bufferHeight) override;


	void SetWorldMatrix(const SGLMatrix4f& matrix);
	const SGLMatrix4f& GetWorldMatrix() const;

	void SetViewMatrix(const SGLMatrix4f& matrix);
	const SGLMatrix4f& GetViewMatrix() const;

	void SetProjectionMatrix(const SGLMatrix4f& matrix);
	const SGLMatrix4f& GetProjectionMatrix() const;

	void SetDiffuseTexture(const std::shared_ptr<Texture>& tex);
	const std::shared_ptr<Texture>& GetDiffuseTexture() const;

	void SetSpecularTexture(const std::shared_ptr<Texture>& tex);
	const std::shared_ptr<Texture>& GetSpecularTexture() const;

	void SetNormalTexture(const std::shared_ptr<Texture>& tex);
	const std::shared_ptr<Texture>& GetNormalTexture() const;
private:
	SGLMatrix4f m_WorldMatrix;
	SGLMatrix4f m_ViewMatrix;
	SGLMatrix4f m_ProjectionMatrix;

	std::shared_ptr<Texture> m_DiffuseTexture;
	std::shared_ptr<Texture> m_SpecularTexture;
	std::shared_ptr<Texture> m_NormalTexture;

	SGLVector3f m_LightDir = SGLVector3f(0.0f, -1.0f, 0.0f);
	SGLVector3f m_AmbientLightIntensity = SGLVector3f(0.2f, 0.2f, 0.2f);
};

