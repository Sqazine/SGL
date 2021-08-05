#include "Mesh.h"

Mesh::Mesh(MeshType type)
{
	switch (type)
	{
	case MeshType::TRIANGLE:
		CreateTriangleMeshData();
		break;
	case MeshType::QUAD:
		CreateQuadMeshData();
		break;
	case MeshType::SPHERE:
		CreateSphereMeshData();
		break;
	case MeshType::CUBE:
		CreateCubeMeshData();
		break;
	case MeshType::CAPSULE:
		CreateCapsuleMeshData();
		break;
	default:
		break;
	}
}

Mesh::Mesh(const std::vector<SGL::Vector3f> &positions,
		   const std::vector<SGL::Vector3f> &normals,
		   const std::vector<SGL::Vector2f> &texcoords,
		   const std::vector<SGL::Vector3f> &tangents,
		   const std::vector<SGL::Vector3f> &binormals,
		   const std::vector<SGL::Vector4f> &vertexColors,
		   const std::vector<uint32_t> &indices)
	: m_Positions(positions),
	  m_Normals(normals),
	  m_Texcoords(texcoords),
	  m_Tangents(tangents),
	  m_Binormals(binormals),
	  m_VertexColors(vertexColors),
	  m_Indices(indices)
{
}

Mesh::~Mesh()
{
}

const std::vector<SGL::Vector3f> &Mesh::GetPositions() const
{
	return m_Positions;
}
const std::vector<SGL::Vector3f> &Mesh::GetNormals() const
{
	return m_Normals;
}
const std::vector<SGL::Vector2f> &Mesh::GetTexcoords() const
{
	return m_Texcoords;
}
const std::vector<SGL::Vector3f> &Mesh::GetTangents() const
{
	return m_Tangents;
}
const std::vector<SGL::Vector3f> &Mesh::GetBinormals() const
{
	return m_Binormals;
}
const std::vector<SGL::Vector4f> &Mesh::GetVertexColors() const
{
	return m_VertexColors;
}

const std::vector<uint32_t> &Mesh::GetIndices() const
{
	return m_Indices;
}

void Mesh::CreateQuadMeshData()
{

	m_Positions = {
		{-0.5f, 0.5f, 0.0f},
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
	};

	m_Texcoords =
		{
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
		};

	m_Normals.resize(4, SGL::Vector3f::UNIT_Z);
	m_Tangents.resize(4, SGL::Vector3f::UNIT_X);
	m_Binormals.resize(4, SGL::Vector3f::UNIT_Y);

	m_VertexColors.resize(4, SGL::Vector4f(1.0f));

	m_Indices =
		{
			0, 1, 2,
			0, 2, 3};
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

			m_Normals.emplace_back(SGL::Vector3f(cosPhi * sinTheta, cosTheta, sinPhi * sinTheta));
			m_Positions.emplace_back(m_Normals.back());
			m_Texcoords.emplace_back(SGL::Vector2f(longNumber / longitudeBands, latNumber / latitudeBands));
			m_VertexColors.emplace_back(SGL::Vector4f(1.0f));
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

	m_Positions =
		{
			{-0.5f, -0.5f, 0.0f},
			{0.5f, -0.5f, 0.0f},
			{0.0f, 0.5f, 0.0f}};

	m_Texcoords =
		{
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{0.5f, 1.0f}};

	m_Normals.resize(3, SGL::Vector3f::UNIT_Z);
	m_Tangents.resize(3, SGL::Vector3f::UNIT_X);
	m_Binormals.resize(3, SGL::Vector3f::UNIT_Y);

	m_VertexColors =
		{
			{1.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f, 1.0f}};

	m_Indices = {0, 1, 2};
}
void Mesh::CreateCubeMeshData()
{
	m_Positions =
		{
			//+z
			{-0.5f, 0.5f, 0.5f},
			{-0.5f, -0.5f, 0.5f},
			{0.5f, -0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			//-z
			{0.5f, 0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},
			{-0.5f, -0.5f, -0.5f},
			{-0.5f, 0.5f, -0.5f},
			//+x
			{0.5f, 0.5f, 0.5f},
			{0.5f, -0.5f, 0.5f},
			{0.5f, -0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			//-x
			{-0.5f, 0.5f, -0.5f},
			{-0.5f, -0.5f, -0.5f},
			{-0.5f, -0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f},
			//+y
			{-0.5f, 0.5f, -0.5f},
			{-0.5f, 0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			{0.5f, 0.5f, -0.5f},
			//-y
			{-0.5f, -0.5f, 0.5f},
			{-0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, 0.5f},
		};

	m_Normals =
		{
			//+z
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
			//-z
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,
			//+x
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			//-x
			-SGL::Vector3f::UNIT_X,
			-SGL::Vector3f::UNIT_X,
			-SGL::Vector3f::UNIT_X,
			-SGL::Vector3f::UNIT_X,
			//+y
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			//-y
			-SGL::Vector3f::UNIT_Y,
			-SGL::Vector3f::UNIT_Y,
			-SGL::Vector3f::UNIT_Y,
			-SGL::Vector3f::UNIT_Y,

		};

	m_Texcoords =
		{
			//+z
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			//-z
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			//+x
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			//-x
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			//+y
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			//-y
			{0.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
		};

	m_Tangents =
		{
			//+z
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,

			//-z
			-SGL::Vector3f::UNIT_X,
			-SGL::Vector3f::UNIT_X,
			-SGL::Vector3f::UNIT_X,
			-SGL::Vector3f::UNIT_X,

			//+x
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,

			//-x
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,

			//+y
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,

			//-y
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,
			SGL::Vector3f::UNIT_X,

		};

	m_Binormals =
		{
			//+z
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,

			//-z
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,

			//+x
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,

			//-x
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,
			SGL::Vector3f::UNIT_Y,

			//+y
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,
			-SGL::Vector3f::UNIT_Z,

			//-y
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
			SGL::Vector3f::UNIT_Z,
		};

	m_VertexColors.resize(24, SGL::Vector4f(1.0f));

	m_Indices =
		{
			0,
			1,
			2,
			0,
			2,
			3,

			4,
			5,
			6,
			4,
			6,
			7,

			8,
			9,
			10,
			8,
			10,
			11,

			12,
			13,
			14,
			12,
			14,
			15,

			16,
			17,
			18,
			16,
			18,
			19,

			20,
			21,
			22,
			20,
			22,
			23,
		};
}
void Mesh::CreateCapsuleMeshData()
{
}
