#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
Texture::Texture(const std::string& filePath, aiTextureType type)
	: m_TextureName(filePath.substr(filePath.find_last_of('/') + 1)), m_TextureType(type)
{
	int width, height, channel;
	uint8_t* raw_pixel = stbi_load(filePath.c_str(), &width, &height, &channel, 0);
	for (uint32_t i=0;i<width*height*channel;++i)
		m_Data.emplace_back(raw_pixel[i]);
	raw_pixel = nullptr;
	delete raw_pixel;

	m_Width = width;
	m_Height = height;
	m_Channel = channel;
}


const std::string& Texture::GetTextureName() const
{
	return m_TextureName;
}

const aiTextureType& Texture::GetTextureType() const
{
	return m_TextureType;
}
