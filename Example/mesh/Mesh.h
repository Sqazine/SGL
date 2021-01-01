#pragma once
#include <vector>
#include "SGL.h"
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
	Mesh(INTERNAL_MESH_TYPE type,const std::vector<std::shared_ptr<Texture>>& textures);
	Mesh(const std::vector<SGLVertex>& verts, const std::vector<uint32_t>& inds, const std::vector<std::shared_ptr<Texture>>& texts = {});
	~Mesh();

	const std::vector<SGLVertex>& GetVertices() const;
	const std::vector<uint32_t>& GetIndices() const;
	const std::vector<std::shared_ptr<Texture>>& GetTextures() const;

	const SGLVertex& GetVertex(uint32_t index) const;
	const std::shared_ptr<Texture>& GetTexture(uint32_t index) const;
	const std::shared_ptr<Texture>& GetTexture(const std::string& name) const;
	const std::shared_ptr<Texture>& GetTexture(const aiTextureType& type) const;
private:
	void CreateTriangleMeshData();
	void CreateQuadMeshData();
	void CreateCubeMeshData();
	void CreateSphereMeshData();
	void CreateCapsuleMeshData();

	std::vector<SGLVertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
	std::vector<std::shared_ptr<Texture>> m_Textures;
};

