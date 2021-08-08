#include "Model.h"
#include <iostream>
#include "SGL/SGL.h"
Model::Model(const std::string& filePath)
	:m_Position(SGL::Vector3f::ZERO), m_Rotation(SGL::Vector3f::ZERO), m_Scale(SGL::Vector3f(1.0f))
{
	LoadModel(filePath);
}
Model::Model(const std::vector<Mesh>& meshes)
	:m_Meshes(meshes)
{
}
Model::~Model()
{
}
const std::vector<Mesh>& Model::GetMeshes() const
{
	return m_Meshes;
}
void Model::SetPosition(const SGL::Vector3f& pos)
{
	m_Position = pos;
}
const SGL::Vector3f& Model::GetPosition() const
{

	return m_Position;
}
void Model::SetRotation(const SGL::Vector3f& rot)
{
	m_Rotation = rot;
}
const SGL::Vector3f& Model::GetRotation() const
{

	return m_Rotation;
}
void Model::SetScale(const SGL::Vector3f& s)
{
	m_Scale = s;
}
const SGL::Vector3f& Model::GetScale() const
{

	return m_Scale;
}
SGL::Matrix4f Model::GetWorldMatrix() const
{
	SGL::Matrix4f world = SGL::Matrix4f::Translate(m_Position);

	world *= SGL::Matrix4f::Rotate(SGL::Vector3f::UNIT_X, m_Rotation.x);
	world *= SGL::Matrix4f::Rotate(SGL::Vector3f::UNIT_Y, m_Rotation.y);
	world *= SGL::Matrix4f::Rotate(SGL::Vector3f::UNIT_Z, m_Rotation.z);

	world *= SGL::Matrix4f::Scale(m_Scale);

	return world;
}
void Model::LoadModel(const std::string& filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		std::cout << importer.GetErrorString() << std::endl;

	ProcessNodes(scene->mRootNode, scene);
}

void Model::ProcessNodes(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.emplace_back(ProcessMesh(aimesh, scene));
	}

	for (uint32_t i = 0; i < node->mNumChildren; ++i)
		ProcessNodes(node->mChildren[i], scene);
}

Mesh Model::ProcessMesh(aiMesh* aimesh, const aiScene* scene)
{
	std::vector<SGL::Vector3f> positions;
	std::vector<SGL::Vector3f> normals;
	std::vector<SGL::Vector2f> texcoords;
	std::vector<SGL::Vector3f> tangents;
	std::vector<SGL::Vector3f> binormals;
	std::vector<SGL::Vector4f> vertexColors;
	std::vector<uint32_t> indices;

	std::vector<aiFace*> tmpFaces;

	for (uint32_t i = 0; i < aimesh->mNumVertices; ++i)
	{
		positions.emplace_back(SGL::Vector3f(aimesh->mVertices[i].x, aimesh->mVertices[i].y, aimesh->mVertices[i].z));
		texcoords.emplace_back(SGL::Vector2f(aimesh->mTextureCoords[0][i].x, aimesh->mTextureCoords[0][i].y));
		normals.emplace_back(SGL::Vector3f(aimesh->mNormals[i].x, aimesh->mNormals[i].y, aimesh->mNormals[i].z));
		tangents.emplace_back(SGL::Vector3f(aimesh->mTangents[i].x, aimesh->mTangents[i].y, aimesh->mTangents[i].z));
		binormals.emplace_back(SGL::Vector3f(aimesh->mBitangents[i].x, aimesh->mBitangents[i].y, aimesh->mBitangents[i].z));
		vertexColors.emplace_back(SGL::Vector4f(aimesh->mColors[i]->r,aimesh->mColors[i]->g,aimesh->mColors[i]->b,aimesh->mColors[i]->a));

	}
	
	for (uint32_t i = 0; i < aimesh->mNumFaces; ++i)
	{
		aiFace face = aimesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; ++j)
			indices.emplace_back(face.mIndices[j]);
	}

	return Mesh(positions,normals,texcoords,tangents,binormals,vertexColors,indices);
}