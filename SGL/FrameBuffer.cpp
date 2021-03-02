#include "FrameBuffer.h"
#include <memory>
#include <cstring>
#include "Math.h"

namespace SGL
{

	Colorbuffer::Colorbuffer(const Vector2u32 &bufferExtent)
		: m_BufferExtent(bufferExtent), m_Buffer(new uint8_t[bufferExtent.x * bufferExtent.y * 4])
	{
		memset(m_Buffer, 0, m_BufferExtent.x * m_BufferExtent.y * 4);
	}

	Colorbuffer::~Colorbuffer()
	{
		delete[] m_Buffer;
	}

	void Colorbuffer::SetValue(uint32_t x, uint32_t y, const Vector4f &color)
	{
		if (x >= m_BufferExtent.x || y >= m_BufferExtent.y)
			return;

		uint32_t bufferPos = y * m_BufferExtent.x + x;
		m_Buffer[bufferPos * 4 + 0] = static_cast<uint8_t>(Math::Clamp(color.x, 0.0f, 1.0f) * 255.0f);
		m_Buffer[bufferPos * 4 + 1] = static_cast<uint8_t>(Math::Clamp(color.y, 0.0f, 1.0f) * 255.0f);
		m_Buffer[bufferPos * 4 + 2] = static_cast<uint8_t>(Math::Clamp(color.z, 0.0f, 1.0f) * 255.0f);
		m_Buffer[bufferPos * 4 + 3] = static_cast<uint8_t>(Math::Clamp(color.w, 0.0f, 1.0f) * 255.0f);
	}

	void Colorbuffer::SetValue(const Vector2u32 &pos, const Vector4f &color)
	{
		SetValue(pos.x, pos.y, color);
	}

	Vector4u8 Colorbuffer::GetValue(uint32_t x, uint32_t y) const
	{
		uint32_t bufferPos = y * m_BufferExtent.x + x;
		return Vector4u8(m_Buffer[bufferPos * 4 + 0], m_Buffer[bufferPos * 4 + 1], m_Buffer[bufferPos * 4 + 2], m_Buffer[bufferPos * 4 + 3]);
	}

	Vector4u8 Colorbuffer::GetValue(const Vector2u32 &pos) const
	{
		return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}

	uint8_t *Colorbuffer::GetBuffer() const
	{

		return m_Buffer;
	}

	const Vector2u32 &Colorbuffer::GetBufferExtent() const
	{
		return m_BufferExtent;
	}

	Depthbuffer::Depthbuffer(const Vector2u32 &bufferExtent)
		: m_BufferExtent(bufferExtent), m_Buffer(new float[bufferExtent.x * bufferExtent.y])
	{
		memset(m_Buffer, 1, m_BufferExtent.x * m_BufferExtent.y);
	}

	Depthbuffer::~Depthbuffer()
	{
		delete[] m_Buffer;
	}

	void Depthbuffer::SetValue(int x, int y, float value)
	{
		m_Buffer[y * m_BufferExtent.x + x] = value;
	}

	void Depthbuffer::SetValue(const Vector2u32 &pos, float value)
	{
		SetValue(static_cast<int>(pos.x), static_cast<int>(pos.y), value);
	}

	float Depthbuffer::GetValue(int x, int y)
	{
		return m_Buffer[y * m_BufferExtent.x + x];
	}

	float Depthbuffer::GetValue(const Vector2u32 &pos)
	{
		return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}

	const Vector2u32 &Depthbuffer::GetBufferExtent()
	{
		return m_BufferExtent;
	}

	float *Depthbuffer::GetBuffer() const
	{
		return m_Buffer;
	}

	Framebuffer::Framebuffer(const Vector2u32 &bufferExtent)
		: m_Colorbuffer(std::make_shared<Colorbuffer>(bufferExtent)), m_Depthbuffer(std::make_shared<Depthbuffer>(bufferExtent))
	{
	}

	Framebuffer::Framebuffer(const std::shared_ptr<Colorbuffer> &colorBuffer, const std::shared_ptr<Depthbuffer> &depthBuffer)
		: m_Colorbuffer(colorBuffer), m_Depthbuffer(depthBuffer)
	{
	}

	Framebuffer::~Framebuffer()
	{
	}

	const std::shared_ptr<Colorbuffer> &Framebuffer::GetColorbuffer() const
	{
		return m_Colorbuffer;
	}

	const std::shared_ptr<Depthbuffer> &Framebuffer::GetDepthbuffer() const
	{
		return m_Depthbuffer;
	}
}