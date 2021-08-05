#pragma once
#include <vector>
#include "SGL/SGL.h"
#include <assimp/mesh.h>

enum class MeshType
{
	TRIANGLE,
	QUAD,
	CUBE,
	SPHERE,
	CAPSULE,
	CYLINDER,
	EXTERNAL
};

class Mesh
{
public:
	Mesh(MeshType type=MeshType::EXTERNAL);
	Mesh(const std::vector<SGL::Vector3f> &positions,
		 const std::vector<SGL::Vector3f> &normals = {},
		 const std::vector<SGL::Vector2f> &texcoords = {},
		 const std::vector<SGL::Vector3f> &tangents = {},
		 const std::vector<SGL::Vector3f> &binormals = {},
		 const std::vector<SGL::Vector4f> &vertexColors = {},
		 const std::vector<uint32_t> &indices = {});
	~Mesh();

	void SetPositions(const std::vector<SGL::Vector3f>& positions);
	void SetNormals(const std::vector<SGL::Vector3f>& normals);
	void SetTexcoords(const std::vector<SGL::Vector2f>& texcoords);
	void SetTangents(const std::vector<SGL::Vector3f>& tangents);
	void SetBinormals(const std::vector<SGL::Vector3f>& binormals);
	void SetVertexColors(const std::vector<SGL::Vector4f>& vertexColors);

	const std::vector<SGL::Vector3f> &GetPositions() const;
	const std::vector<SGL::Vector3f> &GetNormals() const;
	const std::vector<SGL::Vector2f> &GetTexcoords() const;
	const std::vector<SGL::Vector3f> &GetTangents() const;
	const std::vector<SGL::Vector3f> &GetBinormals() const;
	const std::vector<SGL::Vector4f> &GetVertexColors() const;
	const std::vector<uint32_t> &GetIndices() const;

private:
	void CreateTriangleMeshData();
	void CreateQuadMeshData();
	void CreateCubeMeshData();
	void CreateSphereMeshData();
	void CreateCapsuleMeshData();
	void CreateCylinderMeshData();

	std::vector<SGL::Vector3f> m_Positions;
	std::vector<SGL::Vector3f> m_Normals;
	std::vector<SGL::Vector2f> m_Texcoords;
	std::vector<SGL::Vector3f> m_Tangents;
	std::vector<SGL::Vector3f> m_Binormals;
	std::vector<SGL::Vector4f> m_VertexColors;
	std::vector<uint32_t> m_Indices;
};
