#include "Mesh.h"

Mesh::Mesh(INTERNAL_MESH_TYPE type, const std::vector<std::shared_ptr<Texture>> &textures)
{
	// switch (type)
	// {
	// case INTERNAL_MESH_TYPE::TRIANGLE:
	// 	CreateTriangleMeshData();
	// 	break;
	// case INTERNAL_MESH_TYPE::QUAD:
	// 	CreateQuadMeshData();
	// 	break;
	// case INTERNAL_MESH_TYPE::SPHERE:
	// 	CreateSphereMeshData();
	// 	break;
	// case INTERNAL_MESH_TYPE::CUBE:
	// 	CreateCubeMeshData();
	// 	break;
	// case INTERNAL_MESH_TYPE::CAPSULE:
	// 	CreateCapsuleMeshData();
	// 	break;
	// default:break;
	// }
}

Mesh::Mesh(const std::vector<SGLVertex> &verts, const std::vector<uint32_t> &inds, const std::vector<std::shared_ptr<Texture>> &texts)
{
}

Mesh::~Mesh()
{
}

const std::vector<SGLVertex> &Mesh::GetVertices() const
{
	return m_Vertices;
}

const std::vector<uint32_t> &Mesh::GetIndices() const
{
	return m_Indices;
}

const std::vector<std::shared_ptr<Texture>> &Mesh::GetTextures() const
{
	return m_Textures;
}

const SGLVertex &Mesh::GetVertex(uint32_t index) const
{

	return m_Vertices.at(index);
}

const std::shared_ptr<Texture> &Mesh::GetTexture(uint32_t index) const
{
	return m_Textures.at(index);
}

const std::shared_ptr<Texture> &Mesh::GetTexture(const std::string &name) const
{
	for (const auto &texture : m_Textures)
		if (texture->GetTextureName().compare(name) == 0)
			return texture;
	return nullptr;
}

const std::shared_ptr<Texture> &Mesh::GetTexture(const aiTextureType &type) const
{
	for (const auto tex : m_Textures)
		if (tex->GetTextureType() == type)
			return tex;
	return nullptr;
}

void Mesh::CreateQuadMeshData()
{
	m_Vertices.emplace_back(SGLVertex{
		{-1.0f, 1.0f, 0.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{}});
}

void Mesh::CreateSphereMeshData()
{
	float latitudeBands = 20.0f;
	float longitudeBands = 20.0f;

	for (float latNumber = 0; latNumber <= latitudeBands; ++latNumber)
	{
		float theta = latNumber * SGLMath::PI / latitudeBands;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (float longNumber = 0; longNumber <= longitudeBands; ++longNumber)
		{

			float phi = longNumber * 2 * SGLMath::PI / longitudeBands;
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			SGLVertex v;
			v.normal = SGLVector3f(cosPhi * sinTheta, cosTheta, sinPhi * sinTheta);
			v.position = SGLVector4f(v.normal, 1.0f);
			v.texcoord = SGLVector2f(longNumber / longitudeBands, latNumber / latitudeBands);
			v.color = SGLVector4f(v.normal, 1.0f);

			m_Vertices.emplace_back(v);
		}
	}

	for (uint32_t latNumber = 0; latNumber < latitudeBands; latNumber++)
	{
		for (uint32_t longNumber = 0; longNumber < longitudeBands; longNumber++)
		{
			uint32_t first = (latNumber * (longitudeBands + 1)) + longNumber;
			uint32_t second = first + longitudeBands + 1;

			m_Indices.emplace_back(first);
			m_Indices.emplace_back(second);
			m_Indices.emplace_back(first + 1);

			m_Indices.emplace_back(second);
			m_Indices.emplace_back(second + 1);
			m_Indices.emplace_back(first + 1);
		}
	}
}
