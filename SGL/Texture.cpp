#include "Texture.h"
namespace SGL
{

	Texture2D::Texture2D()
		: m_Width(0), m_Height(0), m_Channel(0), m_TextureWrapMode(TextureWrapMode::REPEAT)
	{
	}
	Texture2D::Texture2D(const std::vector<uint8_t> &data, int width, int height, int channel)
		: m_Data(std::move(data)), m_Width(width), m_Height(height), m_Channel(channel), m_TextureWrapMode(TextureWrapMode::REPEAT)
	{
	}

	Texture2D::~Texture2D()
	{
	}

	Vector4f Texture2D::GetTexel(float u, float v) const
	{
		std::array<float, 2> tmp = {u, v};
		for (auto &value : tmp)
		{
			switch (m_TextureWrapMode)
			{
			case TextureWrapMode::REPEAT:
				if (value < 0.0f)
					value += Math::Abs(Math::Floor(value));
				else if (value > 1.0f)
					value -= Math::Floor(value);
				break;
			case TextureWrapMode::MIRRORED_REPEAT:
				if (value < 0.0f)
					value = -value - Math::Floor(-value);
				else if (value > 1.0f)
					value = Math::Ceil(value) - value;
				break;
			case TextureWrapMode::CLAMP_TO_EDGE:
				if (value < 0.0f)
					value = 0.0f;
				else if (value > 1.0f)
					value = 1.0f;
				break;
			case TextureWrapMode::CLAMP_TO_BORDER:
				break;
			default:
				break;
			}
		}

		int texel_coord_u = static_cast<int>((tmp[0] * m_Width - 0.5f))%m_Width;
		int texel_coord_v = static_cast<int>((tmp[1] * m_Height - 0.5f))%m_Height;

		int texel_coord = texel_coord_u + texel_coord_v * m_Width;

		float r = m_Data[texel_coord * m_Channel + 0] / 255.0f;
		float g = m_Data[texel_coord * m_Channel + 1] / 255.0f;
		float b = m_Data[texel_coord * m_Channel + 2] / 255.0f;

		if (m_Channel == 4)
		{
			float a = m_Data[texel_coord * m_Channel + 3] / 255.0f;
			return Vector4f(r, g, b, a);
		}
		return Vector4f(r, g, b, 1.0f);
	}

	Vector4f Texture2D::GetTexel(const Vector2f &pos) const
	{
		return GetTexel(pos.x, pos.y);
	}

	int Texture2D::GetWidth() const
	{
		return m_Width;
	}

	int Texture2D::GetHeight() const
	{
		return m_Height;
	}

	int Texture2D::GetChannel() const
	{
		return m_Channel;
	}

	TextureCube::TextureCube()
	{
	}

	TextureCube::TextureCube(const std::vector<uint8_t> &posX, const std::vector<uint8_t> &negX, const std::vector<uint8_t> &posY, const std::vector<uint8_t> &negY, const std::vector<uint8_t> &posZ, const std::vector<uint8_t> &negZ, int width, int height, int channel)
	{
		m_Data[0] = std::make_shared<Texture2D>(posX, width, height, channel);
		m_Data[1] = std::make_shared<Texture2D>(negX, width, height, channel);
		m_Data[2] = std::make_shared<Texture2D>(posY, width, height, channel);
		m_Data[3] = std::make_shared<Texture2D>(negY, width, height, channel);
		m_Data[4] = std::make_shared<Texture2D>(posZ, width, height, channel);
		m_Data[5] = std::make_shared<Texture2D>(negZ, width, height, channel);
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
			if (u > 0)
				return m_Data[0]->GetTexel(1.0f - (v + 1.0f) / 2.0f, (w + 1.0f) / 2.0f);
			else if (u < 0)
				return m_Data[1]->GetTexel((v + 1.0f) / 2.0f, (w + 1.0f) / 2.0f);
		}
		else if (mag == abs_v)
		{
			if (v > 0)
				return m_Data[2]->GetTexel((u + 1.0f) / 2.0f, 1.0f - (w + 1.0f) / 2.0f);
			else if (v < 0)
				return m_Data[3]->GetTexel((u + 1.0f) / 2.0f, (w + 1.0f) / 2.0f);
		}
		else if (mag == abs_w)
		{
			if (w > 0)
				return m_Data[4]->GetTexel((u + 1.0f) / 2.0f, (v + 1.0f) / 2.0f);
			else if (w < 0)
				return m_Data[5]->GetTexel(1.0f - (u + 1.0f) / 2.0f, (v + 1.0f) / 2.0f);
		}
		return Vector4f(0.0);
	}

	Vector4f TextureCube::GetTexel(const Vector3f &pos) const
	{
		return GetTexel(pos.x, pos.y, pos.z);
	}

	const std::shared_ptr<Texture2D> &TextureCube::GetTexture(uint8_t index) const
	{
		if (0 < index && index < 6)
			return m_Data[index];
		return nullptr;
	}
}