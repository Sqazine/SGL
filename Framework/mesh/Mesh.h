#pragma once
#include <vector>
#include "SGL/SGL.h"
#include "Vertex.h"
#include "texture/Texture.h"
#include <assimp/mesh.h>

enum class MeshType
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
	Mesh(MeshType type);
	Mesh(const std::vector<Vertex>& verts, const std::vector<uint32_t>& inds=std::vector<uint32_t>());
	~Mesh();

	const std::vector<Vertex>& GetVertices() const;
	const std::vector<uint32_t>& GetIndices() const;
	const Vertex& GetVertex(uint32_t index) const;
private:
	void CreateTriangleMeshData();
	void CreateQuadMeshData();
	void CreateCubeMeshData();
	void CreateSphereMeshData();
	void CreateCapsuleMeshData();

	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
};

