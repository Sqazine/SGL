#include "BlinnPhongShader.h"
#include "SGL/SGL.h"
#include <iostream>
BlinnPhongShader::BlinnPhongShader()
{
}

BlinnPhongShader::~BlinnPhongShader()
{
}

SGL::Vertex BlinnPhongShader::VertexShader(const SGL::Vertex& modelVertex)
{
	SGL::Vertex tmpVertex;
	tmpVertex.position = m_ProjectionMatrix * m_ViewMatrix * m_WorldMatrix * modelVertex.position;
	tmpVertex.normal = SGL::Matrix4f::ToMatrix3(SGL::Matrix4f::Transpose(SGL::Matrix4f::Inverse(m_ViewMatrix * m_WorldMatrix))) * modelVertex.normal;
	return tmpVertex;
}

SGL::Vector4f BlinnPhongShader::FragmentShader(const SGL::Vertex& screenVertex,const SGL::Vector2u32& bufferExtent)
{
	SGL::Vector3f normalVS = SGL::Vector3f::Normalize(SGL::Vector4f::ToVector3(m_NormalTexture->GetTexel(screenVertex.texcoord))*2.0f-1.0f);

	SGL::Vector3f fragPosNDC((screenVertex.position.x / bufferExtent.x * 2.0f) - 1.0f, (screenVertex.position.y / bufferExtent.y * 2.0f) - 1.0f, screenVertex.position.z);
	SGL::Vector4f fragPosCS = SGL::Vector4f(fragPosNDC, 1.0f) * screenVertex.position.w;
	SGL::Vector3f fragPosVS = SGL::Vector4f::ToVector3(fragPosCS * SGL::Matrix4f::Inverse(m_ProjectionMatrix));
	SGL::Vector3f viewDirVS = SGL::Vector3f::Normalize(SGL::Vector3f(-fragPosVS));

	SGL::Vector4f ambientLight = SGL::Vector4f::ToVector3(m_DiffuseTexture->GetTexel(screenVertex.texcoord));
	SGL::Vector4f diffuseLight = (SGL::Vector3f::Dot(-m_LightDir, normalVS) * 0.5f + 0.5f) * m_DiffuseTexture->GetTexel(screenVertex.texcoord);

	SGL::Vector3f h = SGL::Vector3f::Normalize(viewDirVS - m_LightDir);
	SGL::Vector4f specularLight = SGL::Math::Pow(SGL::Math::Max(0.0f, SGL::Vector3f::Dot(normalVS, h)), 32.0f) * m_SpecularTexture->GetTexel(screenVertex.texcoord);
	return  ambientLight + diffuseLight + specularLight;
}