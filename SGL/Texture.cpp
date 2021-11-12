#include "Texture.h"

#define GET_TEXEL(u, v, wrapS, wrapT, channelMode, width, height, data)

namespace SGL
{

	Vector4f GetTexelCommon(float u, float v, TextureWrapMode wrapS, TextureWrapMode wrapT, TextureChannelMode channelMode, uint32_t width, uint32_t height, void *texData)
	{
		std::array<float, 2> tmpUV = {u, v};
		std::array<TextureWrapMode, 2> tmpWrapMode = {wrapS, wrapT};
		for (size_t i = 0; i < 2; ++i)
		{
			switch (tmpWrapMode[i])
			{
			case TextureWrapMode::REPEAT:
				if (tmpUV[i] < 0.0f)
					tmpUV[i] += Math::Abs(Math::Floor(tmpUV[i]));
				else if (tmpUV[i] > 1.0f)
					tmpUV[i] -= Math::Floor(tmpUV[i]);
				break;
			case TextureWrapMode::MIRRORED_REPEAT:
				if (tmpUV[i] < 0.0f)
					tmpUV[i] = -tmpUV[i] - Math::Floor(-tmpUV[i]);
				else if (tmpUV[i] > 1.0f)
					tmpUV[i] = Math::Ceil(tmpUV[i]) - tmpUV[i];
				break;
			case TextureWrapMode::CLAMP_TO_EDGE:
				if (tmpUV[i] < 0.0f)
					tmpUV[i] = 0.0f;
				else if (tmpUV[i] > 1.0f)
					tmpUV[i] = 1.0f;
				break;
			case TextureWrapMode::CLAMP_TO_BORDER:
				break;
			default:
				break;
			}
		}

		int32_t texel_coord_u = static_cast<int32_t>((tmpUV[0] * width - 0.5f)) % width;
		int32_t texel_coord_v = static_cast<int32_t>((tmpUV[1] * height - 0.5f)) % height;

		int32_t texel_coord = texel_coord_u + texel_coord_v * width;

		if (channelMode == TextureChannelMode::RGB8)
		{
			uint8_t *data = static_cast<uint8_t *>(texData);
			float r = data[texel_coord * 3 + 0] / 255.0f;
			float g = data[texel_coord * 3 + 1] / 255.0f;
			float b = data[texel_coord * 3 + 2] / 255.0f;
			return Vector4f(r, g, b, 1.0f);
		}
		else if (channelMode == TextureChannelMode::RGBA8)
		{
			uint8_t *data = static_cast<uint8_t *>(texData);
			float r = data[texel_coord * 4 + 0] / 255.0f;
			float g = data[texel_coord * 4 + 1] / 255.0f;
			float b = data[texel_coord * 4 + 2] / 255.0f;
			float a = data[texel_coord * 4 + 3] / 255.0f;
			return Vector4f(r, g, b, a);
		}
		else if (channelMode == TextureChannelMode::RGB32F)
		{
			float *data = static_cast<float *>(texData);
			float r = data[texel_coord * 3 + 0];
			float g = data[texel_coord * 3 + 1];
			float b = data[texel_coord * 3 + 2];
			return Vector4f(r, g, b, 1.0f);
		}
		else if (channelMode == TextureChannelMode::RGBA32F)
		{
			float *data = static_cast<float *>(texData);
			float r = data[texel_coord * 4 + 0];
			float g = data[texel_coord * 4 + 1];
			float b = data[texel_coord * 4 + 2];
			float a = data[texel_coord * 4 + 3];
			return Vector4f(r, g, b, a);
		}

		return Vector4f::ZERO;
	}

	Texture2D::Texture2D(const Texture2DCreateInfo &createInfo)
		: m_CreateInfo(createInfo)
	{
	}

	Texture2D::~Texture2D()
	{
	}

	Vector4f Texture2D::GetTexel(float u, float v) const
	{
		return GetTexelCommon(u, v, m_CreateInfo.wrapModeS, m_CreateInfo.wrapModeT, m_CreateInfo.channelMode, m_CreateInfo.width, m_CreateInfo.height, m_CreateInfo.data);
	}

	Vector4f Texture2D::GetTexel(const Vector2f &pos) const
	{
		return GetTexel(pos.x, pos.y);
	}

	const Texture2DCreateInfo &Texture2D::GetCreateInfo() const
	{
		return m_CreateInfo;
	}

	TextureCube::TextureCube(const TextureCubeCreateInfo &createInfo)
		: m_CreateInfo(createInfo)
	{
	}

	TextureCube::~TextureCube()
	{
	}

	Vector4f TextureCube::GetTexel(float u, float v, float w) const
	{
		float abs_u = Math::Abs(u);
		float abs_v = Math::Abs(v);
		float abs_w = Math::Abs(w);
		float mag = Math::Max(abs_u, Math::Max(abs_v, abs_w));
		if (mag == abs_u)
		{
			if (u > 0) //+x
				return GetTexelCommon(1.0f - (w + 1.0f) / 2.0f, (v + 1.0f) / 2.0f, m_CreateInfo.wrapModeR, m_CreateInfo.wrapModeT, m_CreateInfo.channelMode, m_CreateInfo.width, m_CreateInfo.height, m_CreateInfo.data[0]);
			else if (u < 0) //-x
				return GetTexelCommon((w + 1.0f) / 2.0f, (v + 1.0f) / 2.0f, m_CreateInfo.wrapModeR, m_CreateInfo.wrapModeT, m_CreateInfo.channelMode, m_CreateInfo.width, m_CreateInfo.height, m_CreateInfo.data[1]);
		}
		else if (mag == abs_v)
		{
			if (v > 0) //+y
				return GetTexelCommon((u + 1.0f) / 2.0f, 1.0f - (w + 1.0f) / 2.0f, m_CreateInfo.wrapModeS, m_CreateInfo.wrapModeR, m_CreateInfo.channelMode, m_CreateInfo.width, m_CreateInfo.height, m_CreateInfo.data[2]);
			else if (v < 0) //-y
				return GetTexelCommon((u + 1.0f) / 2.0f, (w + 1.0f) / 2.0f, m_CreateInfo.wrapModeS, m_CreateInfo.wrapModeR, m_CreateInfo.channelMode, m_CreateInfo.width, m_CreateInfo.height, m_CreateInfo.data[3]);
		}
		else if (mag == abs_w)
		{
			if (w > 0)//+z
				return GetTexelCommon((u + 1.0f) / 2.0f, (v + 1.0f) / 2.0f, m_CreateInfo.wrapModeS, m_CreateInfo.wrapModeT, m_CreateInfo.channelMode, m_CreateInfo.width, m_CreateInfo.height, m_CreateInfo.data[4]);
			else if (w < 0)//-z
				return GetTexelCommon(1.0f - (u + 1.0f) / 2.0f, (v + 1.0f) / 2.0f, m_CreateInfo.wrapModeS, m_CreateInfo.wrapModeT, m_CreateInfo.channelMode, m_CreateInfo.width, m_CreateInfo.height, m_CreateInfo.data[5]);
		}
		return Vector4f::ZERO;
	}

	Vector4f TextureCube::GetTexel(const Vector3f &pos) const
	{
		return GetTexel(pos.x, pos.y, pos.z);
	}

	const TextureCubeCreateInfo &TextureCube::GetCreateInfo() const
	{
		return m_CreateInfo;
	}
}