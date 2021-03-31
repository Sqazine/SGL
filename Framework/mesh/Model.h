#pragma once
#include "SGL/SGL.h"
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

	void SetPosition(const SGL::Vector3f& pos);
	const SGL::Vector3f& GetPosition() const;

	void SetRotation(const SGL::Vector3f& rot);
	const SGL::Vector3f& GetRotation() const;

	void SetScale(const SGL::Vector3f& s);
	const SGL::Vector3f& GetScale() const;

	SGL::Matrix4f GetWorldMatrix() const;
private:
	SGL::Vector3f m_Position;
	SGL::Vector3f m_Rotation;
	SGL::Vector3f m_Scale;
	std::vector<std::shared_ptr<Mesh>> m_Meshes;

	std::vector<std::shared_ptr<Texture>> m_LoadedTextures;

	void LoadModel(const std::string& filePath);
	void ProcessNodes(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> ProcessMesh(aiMesh* aimesh, const aiScene* scene);

	std::string m_ModelDirectory;
};

