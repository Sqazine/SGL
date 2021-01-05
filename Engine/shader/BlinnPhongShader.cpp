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

SGLVector4f BlinnPhongShader::FragmentShader(const SGLVertex& screenVertex,const SGLVector2u32& bufferExtent)
{
	SGLVector3f normalVS = SGLVector3f::Normalize(SGLVector4f::ToVector3(m_NormalTexture->GetTexel(screenVertex.texcoord))*2.0f-1.0f);

	SGLVector3f fragPosNDC((screenVertex.position.x / bufferExtent.x * 2.0f) - 1.0f, (screenVertex.position.y / bufferExtent.y * 2.0f) - 1.0f, screenVertex.position.z);
	SGLVector4f fragPosCS = SGLVector4f(fragPosNDC, 1.0f) * screenVertex.position.w;
	SGLVector3f fragPosVS = SGLVector4f::ToVector3(fragPosCS * SGLMatrix4f::Inverse(m_ProjectionMatrix));
	SGLVector3f viewDirVS = SGLVector3f::Normalize(SGLVector3f(-fragPosVS));

	SGLVector4f ambientLight = SGLVector4f::ToVector3(m_DiffuseTexture->GetTexel(screenVertex.texcoord));
	SGLVector4f diffuseLight = (SGLVector3f::Dot(-m_LightDir, normalVS) * 0.5f + 0.5f) * m_DiffuseTexture->GetTexel(screenVertex.texcoord);

	SGLVector3f h = SGLVector3f::Normalize(viewDirVS - m_LightDir);
	SGLVector4f specularLight = SGLMath::Pow(SGLMath::Max(0.0f, SGLVector3f::Dot(normalVS, h)), 32.0f) * m_SpecularTexture->GetTexel(screenVertex.texcoord);
	return  ambientLight + diffuseLight + specularLight;
}