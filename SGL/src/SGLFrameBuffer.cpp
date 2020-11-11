#include "SGLFramebuffer.h"
#include <memory>
#include "SGLMath.h"
SGLColorbuffer::SGLColorbuffer(uint32_t width, uint32_t height)
	:m_Width(width), m_Height(height), m_Buffer(new uint8_t[width * height * 4])
{
	memset(m_Buffer, 0, width * height * 4);
}

SGLColorbuffer::~SGLColorbuffer()
{
	delete[] m_Buffer;
}

void SGLColorbuffer::SetValue(uint32_t x, uint32_t y, const SGLVector4f& color)
{
	//在屏幕外的像素则丢弃
	if (x >= m_Width || y >= m_Height)
		return;

	uint32_t bufferPos = y * m_Width + x;
	m_Buffer[bufferPos * 4 + 0] = static_cast<uint8_t>(SGLMath::Clamp(color.x, 0.0f, 1.0f) * 255.0f);
	m_Buffer[bufferPos * 4 + 1] = static_cast<uint8_t>(SGLMath::Clamp(color.y, 0.0f, 1.0f) * 255.0f);
	m_Buffer[bufferPos * 4 + 2] = static_cast<uint8_t>(SGLMath::Clamp(color.z, 0.0f, 1.0f) * 255.0f);
	m_Buffer[bufferPos * 4 + 3] = static_cast<uint8_t>(SGLMath::Clamp(color.w, 0.0f, 1.0f) * 255.0f);

}

void SGLColorbuffer::SetValue(const SGLVector2u32& pos, const SGLVector4f& color)
{
	SetValue(pos.x, pos.y, color);
}

SGLVector4u8 SGLColorbuffer::GetValue(uint32_t x, uint32_t y) const
{
	uint32_t bufferPos = y * m_Width + x;
	return SGLVector4u8(m_Buffer[bufferPos * 4 + 0], m_Buffer[bufferPos * 4 + 1], m_Buffer[bufferPos * 4 + 2], m_Buffer[bufferPos * 4 + 3]);
}

SGLVector4u8 SGLColorbuffer::GetValue(const SGLVector2u32& pos) const
{
	return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

uint8_t* SGLColorbuffer::GetBuffer() const
{

	return m_Buffer;
}

uint32_t SGLColorbuffer::GetBufferWidth() const
{
	return m_Width;
}

uint32_t SGLColorbuffer::GetBufferHeight() const
{
	return m_Height;
}




SGLDepthbuffer::SGLDepthbuffer(uint32_t width, uint32_t height)
	:m_Width(width), m_Height(height), m_Buffer(new float[width * height])
{
	memset(m_Buffer, 1, width * height);
}

SGLDepthbuffer::~SGLDepthbuffer()
{
	delete[] m_Buffer;
}

void SGLDepthbuffer::SetValue(int x, int y, float value)
{
	m_Buffer[y * m_Width + x] = value;
}

void SGLDepthbuffer::SetValue(const SGLVector2u32& pos, float value)
{
	SetValue(static_cast<int>(pos.x), static_cast<int>(pos.y), value);
}

float SGLDepthbuffer::GetValue(int x, int y)
{
	return m_Buffer[y * m_Width + x];
}

float SGLDepthbuffer::GetValue(const SGLVector2u32& pos)
{
	return GetValue(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

uint32_t SGLDepthbuffer::GetBufferWidth()
{
	return m_Width;
}

uint32_t SGLDepthbuffer::GetBufferHeight()
{
	return m_Height;
}

float* SGLDepthbuffer::GetBuffer() const
{
	return m_Buffer;
}

SGLFramebuffer::SGLFramebuffer(uint32_t width, uint32_t height)
	:m_Colorbuffer(std::make_shared<SGLColorbuffer>(width,height)),m_Depthbuffer(std::make_shared<SGLDepthbuffer>(width,height))
{
}

SGLFramebuffer::SGLFramebuffer(const std::shared_ptr<SGLColorbuffer>& colorBuffer, const std::shared_ptr<SGLDepthbuffer>& depthBuffer)
	:m_Colorbuffer(colorBuffer),m_Depthbuffer(depthBuffer)
{
}

SGLFramebuffer::~SGLFramebuffer()
{
}

const std::shared_ptr<SGLColorbuffer>& SGLFramebuffer::GetColorbuffer() const
{
	return m_Colorbuffer;
}

const std::shared_ptr<SGLDepthbuffer>& SGLFramebuffer::GetDepthbuffer() const
{
	return m_Depthbuffer;
}
