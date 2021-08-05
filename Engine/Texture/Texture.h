#pragma once
#include <cstdint>
#include <string>
#include "SGL/SGL.h"
#include <assimp/material.h>

class Texture:public SGL::Texture2D
{
public:
	Texture(const std::string& filePath);

	const std::string& GetTextureName() const;
private:
	std::string m_TextureName;
};

