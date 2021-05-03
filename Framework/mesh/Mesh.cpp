#include "Mesh.h"

Mesh::Mesh(INTERNAL_MESH_TYPE type)
{
	switch (type)
	{
	case INTERNAL_MESH_TYPE::TRIANGLE:
		CreateTriangleMeshData();
		break;
	case INTERNAL_MESH_TYPE::QUAD:
		CreateQuadMeshData();
		break;
	case INTERNAL_MESH_TYPE::SPHERE:
		CreateSphereMeshData();
		break;
	case INTERNAL_MESH_TYPE::CUBE:
		CreateCubeMeshData();
		break;
	case INTERNAL_MESH_TYPE::CAPSULE:
		CreateCapsuleMeshData();
		break;
	default:
		break;
	}
}

Mesh::Mesh(const std::vector<Vertex> &verts, const std::vector<uint32_t> &inds)
{
}

Mesh::~Mesh()
{
}

const std::vector<Vertex> &Mesh::GetVertices() const
{
	return m_Vertices;
}

const std::vector<uint32_t> &Mesh::GetIndices() const
{
	return m_Indices;
}

void Mesh::CreateQuadMeshData()
{
	m_Vertices.emplace_back(Vertex{
		{-1.0f, 1.0f, 0.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{}});
}

void Mesh::CreateSphereMeshData()
{
	float latitudeBands = 64.0f;
	float longitudeBands = 64.0f;

	for (float latNumber = 0; latNumber <= latitudeBands; ++latNumber)
	{
		float theta = latNumber * SGL::Math::PI / latitudeBands;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (float longNumber = 0; longNumber <= longitudeBands; ++longNumber)
		{

			float phi = longNumber * 2 * SGL::Math::PI / longitudeBands;
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			Vertex v;
			v.normal = SGL::Vector3f(cosPhi * sinTheta, cosTheta, sinPhi * sinTheta);
			v.position = SGL::Vector4f(v.normal, 1.0f);
			v.texcoord = SGL::Vector2f(longNumber / longitudeBands, latNumber / latitudeBands);
			v.color = SGL::Vector4f(v.normal, 1.0f);

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

void Mesh::CreateTriangleMeshData()
{
}
void Mesh::CreateCubeMeshData()
{
}
void Mesh::CreateCapsuleMeshData()
{
}
