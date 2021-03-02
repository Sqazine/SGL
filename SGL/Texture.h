#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"

namespace SGL
{

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

	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(const std::vector<uint8_t> &data, int width, int height, int channel);
		virtual ~Texture2D();

		void SetData(const std::vector<uint8_t> &data, int width, int height, int channel);
		uint8_t *GetData();

		void SetWrapMode(const TextureWrapMode &mode);
		const TextureWrapMode &GetWrapMode() const;

		Vector4f GetTexel(float u, float v) const;
		Vector4f GetTexel(const Vector2f &pos) const;
		int GetWidth() const;
		int GetHeight() const;
		int GetChannel() const;

	protected:
		std::vector<uint8_t> m_Data;
		int m_Width, m_Height, m_Channel;
		TextureWrapMode m_TextureWrapMode;
	};

	class TextureCube
	{
	public:
		TextureCube();
		TextureCube(const std::vector<uint8_t> &posX, const std::vector<uint8_t> &negX, const std::vector<uint8_t> &posY, const std::vector<uint8_t> &negY, const std::vector<uint8_t> &posZ, const std::vector<uint8_t> &negZ, int width, int height, int channel);
		virtual ~TextureCube();

		Vector4f GetTexel(float u, float v, float w) const;
		Vector4f GetTexel(const Vector3f &pos) const;

		const std::shared_ptr<Texture2D> &GetTexture(uint8_t index) const;

	protected:
		std::array<std::shared_ptr<Texture2D>, 6> m_Data;
	};
}