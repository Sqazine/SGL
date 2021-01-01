#pragma once
#include <cstdint>
#include <string>
#include "SGL.h"
#include <assimp/material.h>

class Texture:public SGLTexture2D
{
public:
	Texture(const std::string& filePath,aiTextureType type);

	const std::string& GetTextureName() const;
	const aiTextureType& GetTextureType() const;
private:
	std::string m_TextureName;
	aiTextureType m_TextureType;
};

