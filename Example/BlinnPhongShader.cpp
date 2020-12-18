#include "BlinnPhongShader.h"
#include "SGL.h"
#include <iostream>
BlinnPhongShader::BlinnPhongShader()
{
}

BlinnPhongShader::~BlinnPhongShader()
{
}

SGLVertex BlinnPhongShader::VertexShader(const SGLVertex& modelVertex)
{
	SGLVertex tmpVertex;
	tmpVertex.position = m_ProjectionMatrix * m_ViewMatrix * m_WorldMatrix * modelVertex.position;
	tmpVertex.normal = SGLMatrix4f::ToMatrix3(SGLMatrix4f::Transpose(SGLMatrix4f::Inverse(m_ViewMatrix * m_WorldMatrix))) * modelVertex.normal;
	return tmpVertex;
}

SGLVector4f BlinnPhongShader::FragmentShader(const SGLVertex& screenVertex, uint32_t bufferWidth, uint32_t bufferHeight)
{
	SGLVector3f normalVS = SGLVector3f::Normalize(SGLVector4f::ToVector3(m_NormalTexture->GetTexel(screenVertex.texcoord))*2.0f-1.0f);

	SGLVector3f fragPosNDC((screenVertex.position.x / bufferWidth * 2.0f) - 1.0f, (screenVertex.position.y / bufferHeight * 2.0f) - 1.0f, screenVertex.position.z);
	SGLVector4f fragPosCS = SGLVector4f(fragPosNDC, 1.0f) * screenVertex.position.w;
	SGLVector3f fragPosVS = SGLVector4f::ToVector3(fragPosCS * SGLMatrix4f::Inverse(m_ProjectionMatrix));
	SGLVector3f viewDirVS = SGLVector3f::Normalize(SGLVector3f(-fragPosVS));

	SGLVector4f ambientLight = m_AmbientLightIntensity * SGLVector4f::ToVector3(m_DiffuseTexture->GetTexel(screenVertex.texcoord));
	SGLVector4f diffuseLight = (SGLVector3f::Dot(-m_LightDir, normalVS) * 0.5f + 0.5f) * m_DiffuseTexture->GetTexel(screenVertex.texcoord);

	SGLVector3f h = SGLVector3f::Normalize(viewDirVS - m_LightDir);
	SGLVector4f specularLight = SGLMath::Pow(SGLMath::Max(0.0f, SGLVector3f::Dot(normalVS, h)), 32.0f) * m_SpecularTexture->GetTexel(screenVertex.texcoord);
	return  ambientLight + diffuseLight + specularLight;
}


void BlinnPhongShader::SetWorldMatrix(const SGLMatrix4f& matrix)
{
	m_WorldMatrix = matrix;
}

const SGLMatrix4f& BlinnPhongShader::GetWorldMatrix() const
{

	return m_WorldMatrix;
}

void BlinnPhongShader::SetViewMatrix(const SGLMatrix4f& matrix)
{
	m_ViewMatrix = matrix;
}

const SGLMatrix4f& BlinnPhongShader::GetViewMatrix() const
{

	return m_ViewMatrix;
}

void BlinnPhongShader::SetProjectionMatrix(const SGLMatrix4f& matrix)
{
	m_ProjectionMatrix = matrix;
}

const SGLMatrix4f& BlinnPhongShader::GetProjectionMatrix() const
{

	return m_ProjectionMatrix;
}

void BlinnPhongShader::SetDiffuseTexture(const std::shared_ptr<Texture>& tex)
{
	m_DiffuseTexture = tex;
}

const std::shared_ptr<Texture>& BlinnPhongShader::GetDiffuseTexture() const
{
	return m_DiffuseTexture;
}

void BlinnPhongShader::SetSpecularTexture(const std::shared_ptr<Texture>& tex)
{
	m_SpecularTexture = tex;
}

const std::shared_ptr<Texture>& BlinnPhongShader::GetSpecularTexture() const
{
	return m_SpecularTexture;
}

void BlinnPhongShader::SetNormalTexture(const std::shared_ptr<Texture>& tex)
{
	m_NormalTexture = tex;
}

const std::shared_ptr<Texture>& BlinnPhongShader::GetNormalTexture() const
{
	return m_NormalTexture;
}
