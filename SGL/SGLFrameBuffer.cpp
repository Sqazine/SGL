#include "SGLFramebuffer.h"
#include <memory>
#include <cstring>
#include "SGLMath.h"
SGLColorbuffer::SGLColorbuffer(const SGLVector2u32 &bufferExtent)
	: m_BufferExtent(bufferExtent), m_Buffer(new uint8_t[bufferExtent.x * bufferExtent.y * 4])
{
	memset(m_Buffer, 0, m_BufferExtent.x * m_BufferExtent.y * 4);
}

SGLColorbuffer::~SGLColorbuffer()
{
	delete[] m_Buffer;
}

void SGLColorbuffer::SetValue(uint32_t x, uint32_t y, const SGLVector4f &color)
{
	if (x >= m_BufferExtent.x || y >= m_BufferExtent.y)
		return;

	uint32_t bufferPos = y * m_BufferExtent.x + x;
	m_Buffer[bufferPos * 4 + 0] = static_cast<uint8_t>(SGLMath::Clamp(color.x, 0.0f, 1.0f) * 255.0f);
	m_Buffer[bufferPos * 4 + 1] = static_cast<uint8_t>(SGLMath::Clamp(color.y, 0.0f, 1.0f) * 255.0f);
	m_Buffer[bufferPos * 4 + 2] = static_cast<uint8_t>(SGLMath::Clamp(color.z, 0.0f, 1.0f) * 255.0f);
	m_Buffer[bufferPos * 4 + 3] = static_cast<uint8_t>(SGLMath::Clamp(color.w, 0.0f, 1.0f) * 255.0f);
}

void SGLColorbuffer::SetValue(const SGLVector2u32 &pos, const SGLVector4f &color)
{
	SetValue(pos.x, pos.y, color);
}

SGLVector4u8 SGLColorbuffer::GetValue(uint32_t x, uint32_t y) const
{
	uint32_t bufferPos = y * m_BufferExtent.x + x;
	return SGLVector4u8(m_Buffer[bufferPos * 4 + 0], m_Buffer[bufferPos * 4 + 1], m_Buffer[bufferPos * 4 + 2], m_Buffer[bufferPos * 4 + 3]);
}

SGLVector4u8 SGLColorbuffer::GetValue(const SGLVector2u32 &pos) const
{
	return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

uint8_t *SGLColorbuffer::GetBuffer() const
{

	return m_Buffer;
}

const SGLVector2u32 &SGLColorbuffer::GetBufferExtent() const
{
	return m_BufferExtent;
}

SGLDepthbuffer::SGLDepthbuffer(const SGLVector2u32 &bufferExtent)
	:m_BufferExtent(bufferExtent), m_Buffer(new float[bufferExtent.x * bufferExtent.y])
{
	memset(m_Buffer, 1, m_BufferExtent.x * m_BufferExtent.y);
}

SGLDepthbuffer::~SGLDepthbuffer()
{
	delete[] m_Buffer;
}

void SGLDepthbuffer::SetValue(int x, int y, float value)
{
	m_Buffer[y * m_BufferExtent.x + x] = value;
}

void SGLDepthbuffer::SetValue(const SGLVector2u32 &pos, float value)
{
	SetValue(static_cast<int>(pos.x), static_cast<int>(pos.y), value);
}

float SGLDepthbuffer::GetValue(int x, int y)
{
	return m_Buffer[y * m_BufferExtent.x + x];
}

float SGLDepthbuffer::GetValue(const SGLVector2u32 &pos)
{
	return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

const SGLVector2u32& SGLDepthbuffer::GetBufferExtent()
{
	return m_BufferExtent;
}

float *SGLDepthbuffer::GetBuffer() const
{
	return m_Buffer;
}

SGLFramebuffer::SGLFramebuffer(const SGLVector2u32 &bufferExtent)
	: m_Colorbuffer(std::make_shared<SGLColorbuffer>(bufferExtent)), m_Depthbuffer(std::make_shared<SGLDepthbuffer>(bufferExtent))
{
}

SGLFramebuffer::SGLFramebuffer(const std::shared_ptr<SGLColorbuffer> &colorBuffer, const std::shared_ptr<SGLDepthbuffer> &depthBuffer)
	: m_Colorbuffer(colorBuffer), m_Depthbuffer(depthBuffer)
{
}

SGLFramebuffer::~SGLFramebuffer()
{
}

const std::shared_ptr<SGLColorbuffer> &SGLFramebuffer::GetColorbuffer() const
{
	return m_Colorbuffer;
}

const std::shared_ptr<SGLDepthbuffer> &SGLFramebuffer::GetDepthbuffer() const
{
	return m_Depthbuffer;
}
