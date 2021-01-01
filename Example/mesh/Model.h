#pragma once
#include "SGL.h"
#include <vector>
#include "texture/Texture.h"
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
class Model
{
public:
	Model(const std::string& filePath);
	Model(const std::vector<std::shared_ptr<Mesh>>& meshes);
	Model(const std::shared_ptr<Mesh>& mesh);
	~Model();

	const std::vector<std::shared_ptr<Mesh>>& GetMeshes() const;

	void SetPosition(const SGLVector3f& pos);
	const SGLVector3f& GetPosition() const;

	void SetRotation(const SGLVector3f& rot);
	const SGLVector3f& GetRotation() const;

	void SetScale(const SGLVector3f& s);
	const SGLVector3f& GetScale() const;

	SGLMatrix4f GetWorldMatrix() const;
private:
	SGLVector3f m_Position;
	SGLVector3f m_Rotation;
	SGLVector3f m_Scale;
	std::vector<std::shared_ptr<Mesh>> m_Meshes;

	std::vector<std::shared_ptr<Texture>> m_LoadedTextures;

	void LoadModel(const std::string& filePath);
	void ProcessNodes(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> ProcessMesh(aiMesh* aimesh, const aiScene* scene);

	std::vector<std::shared_ptr<Texture>> LoadMeshTextures(aiMaterial* mat,aiTextureType type);

	std::string m_ModelDirectory;
};

