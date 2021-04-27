#include "BlinnPhongShader.h"
#include "SGL/SGL.h"
BlinnPhongShaderProgram::BlinnPhongShaderProgram()
{
}

BlinnPhongShaderProgram::~BlinnPhongShaderProgram()
{
}

SGL::Vector4f BlinnPhongShaderProgram::VertexShader(const SGL::Vertex &vertex, SGL::Varyings &varyings)
{
	varyings.CommitVector3fVarying("vNormalVS", SGL::Matrix4f::ToMatrix3(SGL::Matrix4f::Transpose(SGL::Matrix4f::Inverse(m_ViewMatrix * m_WorldMatrix))) * vertex.normal);
	varyings.CommitVector3fVarying("vPositionVS", SGL::Vector4f::ToVector3( m_ViewMatrix * m_WorldMatrix * vertex.position));
	varyings.CommitVector2fVarying("vTexcoord",vertex.texcoord);
	return m_ProjectionMatrix * m_ViewMatrix * m_WorldMatrix * vertex.position;
}

SGL::Vector4f BlinnPhongShaderProgram::FragmentShader(SGL::Varyings varyings)
{
	SGL::Vector2f vTexcoordVS = varyings.GetVector2fVarying("vTexcoordVS");
	SGL::Vector3f vPositionVS = varyings.GetVector3fVarying("vPositionVS");

	SGL::Vector3f viewDirVS=-vPositionVS;

	SGL::Vector3f normalVS = SGL::Vector3f::Normalize(SGL::Vector4f::ToVector3(m_NormalTexture->GetTexel(vTexcoordVS)) * 2.0f - 1.0f);

	SGL::Vector4f ambientLight = SGL::Vector4f::ToVector3(m_DiffuseTexture->GetTexel(vTexcoordVS));
	SGL::Vector4f diffuseLight = (SGL::Vector3f::Dot(-m_LightDir, normalVS) * 0.5f + 0.5f) * m_DiffuseTexture->GetTexel(vTexcoordVS);

	SGL::Vector3f h = SGL::Vector3f::Normalize(viewDirVS - m_LightDir);
	SGL::Vector4f specularLight = SGL::Math::Pow(SGL::Math::Max(0.0f, SGL::Vector3f::Dot(normalVS, h)), 32.0f) * m_SpecularTexture->GetTexel(vTexcoordVS);
	return ambientLight + diffuseLight + specularLight;
}