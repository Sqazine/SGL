#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include "SGLVector4.h"
#include "SGLVector2.h"
#include "SGLVector3.h"
enum class TextureWrapMode
{
	REPEAT,
	MIRRORED_REPEAT,
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER
};

enum class TextureFilterMode
{
	NEARST,
	BILINEAR,
	TRILINEAR
};

class SGLTexture2D
{
public:
	SGLTexture2D();
	SGLTexture2D(const std::vector<uint8_t> &data, int width, int height, int channel);
	virtual ~SGLTexture2D();

	void SetData(const std::vector<uint8_t> &data, int width, int height, int channel);
	uint8_t *GetData();

	void SetWrapMode(const TextureWrapMode &mode);
	const TextureWrapMode &GetWrapMode() const;

	SGLVector4f GetTexel(float u, float v) const;
	SGLVector4f GetTexel(const SGLVector2f &pos) const;
	int GetWidth() const;
	int GetHeight() const;
	int GetChannel() const;

protected:
	std::vector<uint8_t> m_Data;
	int m_Width, m_Height, m_Channel;
	TextureWrapMode m_TextureWrapMode;
};

class SGLTextureCube
{
public:
	SGLTextureCube();
	SGLTextureCube(const std::vector<uint8_t> &posX, const std::vector<uint8_t> &negX, const std::vector<uint8_t> &posY, const std::vector<uint8_t> &negY, const std::vector<uint8_t> &posZ, const std::vector<uint8_t> &negZ, int width, int height, int channel);
	virtual ~SGLTextureCube();

	SGLVector4f GetTexel(float u, float v, float w) const;
	SGLVector4f GetTexel(const SGLVector3f &pos) const;

	const std::shared_ptr<SGLTexture2D> &GetTexture(uint8_t index) const;

protected:
	std::array<std::shared_ptr<SGLTexture2D>, 6> m_Data;
};
