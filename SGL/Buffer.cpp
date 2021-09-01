#include "Buffer.h"
#include <memory>
#include <cstring>

#include "Math.h"

namespace SGL
{

	ColorAttahment::ColorAttahment(const Vector2u32 &bufferExtent)
		:m_BufferExtent(bufferExtent), m_Buffer(Buffer<uint8_t>(bufferExtent.x* bufferExtent.y * 4))
	{
	}

	ColorAttahment::~ColorAttahment()
	{
	}

	void ColorAttahment::SetValue(uint32_t x, uint32_t y, const Vector4f &color)
	{
		if (x >= m_BufferExtent.x || y >= m_BufferExtent.y)
			return;

		uint32_t bufferPos = y * m_BufferExtent.x + x;
		m_Buffer[bufferPos * 4 + 0] = static_cast<uint8_t>(Math::Clamp(color.x, 0.0f, 1.0f) * 255.0f);
		m_Buffer[bufferPos * 4 + 1] = static_cast<uint8_t>(Math::Clamp(color.y, 0.0f, 1.0f) * 255.0f);
		m_Buffer[bufferPos * 4 + 2] = static_cast<uint8_t>(Math::Clamp(color.z, 0.0f, 1.0f) * 255.0f);
		m_Buffer[bufferPos * 4 + 3] = static_cast<uint8_t>(Math::Clamp(color.w, 0.0f, 1.0f) * 255.0f);
	}

	void ColorAttahment::SetValue(const Vector2u32 &pos, const Vector4f &color)
	{
		SetValue(pos.x, pos.y, color);
	}

	Vector4u8 ColorAttahment::GetValue(uint32_t x, uint32_t y) const
	{
		uint32_t bufferPos = y * m_BufferExtent.x + x;
		return Vector4u8(m_Buffer[bufferPos * 4 + 0], m_Buffer[bufferPos * 4 + 1], m_Buffer[bufferPos * 4 + 2], m_Buffer[bufferPos * 4 + 3]);
	}

	Vector4u8 ColorAttahment::GetValue(const Vector2u32 &pos) const
	{
		return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}

	const Buffer<uint8_t> &ColorAttahment::GetBuffer() const
	{

		return m_Buffer;
	}

	const Vector2u32 &ColorAttahment::GetBufferExtent() const
	{
		return m_BufferExtent;
	}

	DepthAttachment::DepthAttachment(const Vector2u32 &bufferExtent)
		: m_BufferExtent(bufferExtent),m_Buffer(bufferExtent.x*bufferExtent.y)
	{
	}

	DepthAttachment::~DepthAttachment()
	{
	}

	void DepthAttachment::SetValue(int x, int y, float value)
	{
		m_Buffer[y * m_BufferExtent.x + x] = value;
	}

	void DepthAttachment::SetValue(const Vector2u32 &pos, float value)
	{
		SetValue(static_cast<int>(pos.x), static_cast<int>(pos.y), value);
	}

	float DepthAttachment::GetValue(int x, int y)
	{
		return m_Buffer[y * m_BufferExtent.x + x];
	}

	float DepthAttachment::GetValue(const Vector2u32 &pos)
	{
		return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}

	const Vector2u32 &DepthAttachment::GetBufferExtent()
	{
		return m_BufferExtent;
	}

	const Buffer<float> &DepthAttachment::GetBuffer() const
	{
		return m_Buffer;
	}

	Framebuffer::Framebuffer(const Vector2u32 &bufferExtent)
		: m_ColorAttahment(std::make_shared<ColorAttahment>(bufferExtent)), m_DepthAttachment(std::make_shared<DepthAttachment>(bufferExtent))
	{
	}

	Framebuffer::Framebuffer(const std::shared_ptr<ColorAttahment> &colorBuffer, const std::shared_ptr<DepthAttachment> &depthBuffer)
		: m_ColorAttahment(colorBuffer), m_DepthAttachment(depthBuffer)
	{
	}

	Framebuffer::~Framebuffer()
	{
	}

	const std::shared_ptr<ColorAttahment> &Framebuffer::GetColorAttahment() const
	{
		return m_ColorAttahment;
	}

	const std::shared_ptr<DepthAttachment> &Framebuffer::GetDepthAttachment() const
	{
		return m_DepthAttachment;
	}
}