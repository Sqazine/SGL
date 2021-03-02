#pragma once
#include <vector>
#include "SGL/SGL.h"
#include "texture/Texture.h"
#include <assimp/mesh.h>

enum class INTERNAL_MESH_TYPE
{
	TRIANGLE,
	QUAD,
	CUBE,
	SPHERE,
	CAPSULE
};

class Mesh
{
public:
	Mesh(INTERNAL_MESH_TYPE type);
	Mesh(const std::vector<SGL::Vertex>& verts, const std::vector<uint32_t>& inds=std::vector<uint32_t>());
	~Mesh();

	const std::vector<SGL::Vertex>& GetVertices() const;
	const std::vector<uint32_t>& GetIndices() const;
	const SGL::Vertex& GetVertex(uint32_t index) const;
private:
	void CreateTriangleMeshData();
	void CreateQuadMeshData();
	void CreateCubeMeshData();
	void CreateSphereMeshData();
	void CreateCapsuleMeshData();

	std::vector<SGL::Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
};

