#include "Model.h"
#include <iostream>
#include "SGL.h"
Model::Model(const std::string& filePath)
	:m_Position(SGLVector3f::ZERO), m_Rotation(SGLVector3f::ZERO), m_Scale(SGLVector3f(1.0f))
{
	m_ModelDirectory = filePath.substr(0, filePath.find_last_of('/') + 1);
	LoadModel(filePath);
}
Model::Model(const std::vector<std::shared_ptr<Mesh>>& meshes)
	:m_Meshes(meshes)
{
}
Model::~Model()
{
}
const std::vector<std::shared_ptr<Mesh>>& Model::GetMeshes() const
{
	return m_Meshes;
}
void Model::SetPosition(const SGLVector3f& pos)
{
	m_Position = pos;
}
const SGLVector3f& Model::GetPosition() const
{

	return m_Position;
}
void Model::SetRotation(const SGLVector3f& rot)
{
	m_Rotation = rot;
}
const SGLVector3f& Model::GetRotation() const
{

	return m_Rotation;
}
void Model::SetScale(const SGLVector3f& s)
{
	m_Scale = s;
}
const SGLVector3f& Model::GetScale() const
{

	return m_Scale;
}
SGLMatrix4f Model::GetWorldMatrix() const
{
	SGLMatrix4f world = SGLMatrix4f::Translate(m_Position);

	world *= SGLMatrix4f::Rotate(SGLVector3f::UNIT_X, m_Rotation.x);
	world *= SGLMatrix4f::Rotate(SGLVector3f::UNIT_Y, m_Rotation.y);
	world *= SGLMatrix4f::Rotate(SGLVector3f::UNIT_Z, m_Rotation.z);

	world *= SGLMatrix4f::Scale(m_Scale);

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

std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* aimesh, const aiScene* scene)
{
	std::vector<SGLVertex> tmpVertices;
	std::vector<uint32_t> tmpIndices;
	std::vector<std::shared_ptr<Texture>> tmpTextures;
	std::vector<aiFace*> tmpFaces;
	//�������񶥵�
	for (uint32_t i = 0; i < aimesh->mNumVertices; ++i)
	{
		SGLVertex tmpVert;
		tmpVert.position = SGLVector4f(aimesh->mVertices[i].x, aimesh->mVertices[i].y, aimesh->mVertices[i].z, 1.0f);
		tmpVert.texcoord = SGLVector2f(SGLMath::MapNumToInterval01(aimesh->mTextureCoords[0][i].x), SGLMath::MapNumToInterval01(aimesh->mTextureCoords[0][i].y));
		tmpVert.normal = SGLVector3f(aimesh->mNormals[i].x, aimesh->mNormals[i].y, aimesh->mNormals[i].z);
		tmpVert.tangent = SGLVector3f(aimesh->mTangents[i].x, aimesh->mTangents[i].y, aimesh->mTangents[i].z);
		tmpVert.bitangent = SGLVector3f(aimesh->mBitangents[i].x, aimesh->mBitangents[i].y, aimesh->mBitangents[i].z);
		tmpVertices.emplace_back(tmpVert);
	}
	//�������񶥵�����
	for (uint32_t i = 0; i < aimesh->mNumFaces; ++i)
	{
		aiFace face = aimesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; ++j)
			tmpIndices.emplace_back(face.mIndices[j]);
	}

	//������������
	if (aimesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

		auto diffuseTextures = LoadMeshTextures(material, aiTextureType_DIFFUSE);
		tmpTextures.insert(tmpTextures.end(), diffuseTextures.begin(), diffuseTextures.end());

		auto specularTexture = LoadMeshTextures(material, aiTextureType_SPECULAR);
		tmpTextures.insert(tmpTextures.end(), specularTexture.begin(), specularTexture.end());

		auto normalTextures = LoadMeshTextures(material, aiTextureType_HEIGHT);
		tmpTextures.insert(tmpTextures.end(), normalTextures.begin(), normalTextures.end());

		auto reflectTextures = LoadMeshTextures(material, aiTextureType_REFLECTION);
		tmpTextures.insert(tmpTextures.end(), reflectTextures.begin(), reflectTextures.end());
	}

	return std::make_shared<Mesh>(tmpVertices, tmpIndices, tmpTextures);
}

std::vector<std::shared_ptr<Texture>> Model::LoadMeshTextures(aiMaterial* mat, aiTextureType type)
{
	std::vector<std::shared_ptr<Texture>> tmptexs;
	for (uint32_t i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString texName;
		mat->GetTexture(type, i, &texName);
		bool isLoaded = false;
		for (uint32_t j = 0; j < m_LoadedTextures.size(); ++j)
		{
			if (strcmp(m_LoadedTextures[j]->GetTextureName().c_str(), texName.C_Str()) == 0)
			{
				tmptexs.emplace_back(m_LoadedTextures[j]);
				isLoaded = true;
				break;
			}
		}
		if (!isLoaded)
		{
			auto tex = std::make_shared< Texture>(m_ModelDirectory + texName.C_Str(), type);
			tmptexs.emplace_back(tex);
			m_LoadedTextures.emplace_back(tex);
		}
	}
	return tmptexs;
}