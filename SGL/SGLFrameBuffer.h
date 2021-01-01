#pragma once
#include <vector>
#include <memory>
#include "SGLVector2.h"
#include "SGLVector4.h"
class SGLColorbuffer
{
public:
	SGLColorbuffer(const SGLVector2u32 &bufferExtent);
	~SGLColorbuffer();

	void SetValue(uint32_t x, uint32_t y, const SGLVector4f &color);
	void SetValue(const SGLVector2u32 &pos, const SGLVector4f &color);
	SGLVector4u8 GetValue(uint32_t x, uint32_t y) const;
	SGLVector4u8 GetValue(const SGLVector2u32 &pos) const;

	uint8_t *GetBuffer() const;
	const SGLVector2u32 & GetBufferExtent() const;

private:
	uint8_t *m_Buffer;
	SGLVector2u32 m_BufferExtent;
};

class SGLDepthbuffer
{
public:
	SGLDepthbuffer(const SGLVector2u32 &bufferExtent);
	~SGLDepthbuffer();

	void SetValue(int x, int y, float value);
	void SetValue(const SGLVector2u32 &pos, float value);

	float GetValue(int x, int y);
	float GetValue(const SGLVector2u32 &pos);

	const SGLVector2u32& GetBufferExtent();

	float *GetBuffer() const;

private:
	float *m_Buffer;
	SGLVector2u32 m_BufferExtent;
};

class SGLFramebuffer
{
public:
	SGLFramebuffer(const SGLVector2u32 &bufferExtent);
	SGLFramebuffer(const std::shared_ptr<SGLColorbuffer> &colorBuffer, const std::shared_ptr<SGLDepthbuffer> &depthBuffer);
	~SGLFramebuffer();

	const std::shared_ptr<SGLColorbuffer> &GetColorbuffer() const;
	const std::shared_ptr<SGLDepthbuffer> &GetDepthbuffer() const;

private:
	std::shared_ptr<SGLColorbuffer> m_Colorbuffer;
	std::shared_ptr<SGLDepthbuffer> m_Depthbuffer;
};
