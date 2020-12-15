#pragma once
#include <vector>
#include <memory>
#include "SGLVector2.h"
#include "SGLVector4.h"
class  SGLColorbuffer
{
public:
	SGLColorbuffer(uint32_t width, uint32_t height);
	~SGLColorbuffer();

	void SetValue(uint32_t x, uint32_t y, const  SGLVector4f& color);
	void SetValue(const SGLVector2u32& pos, const  SGLVector4f& color);
	SGLVector4u8 GetValue(uint32_t x, uint32_t y) const;
	SGLVector4u8 GetValue(const  SGLVector2u32& pos) const;

	uint8_t* GetBuffer() const;
	uint32_t GetBufferWidth() const;
	uint32_t GetBufferHeight() const;
private:
	uint8_t* m_Buffer;
	uint32_t m_Width, m_Height;
};



class  SGLDepthbuffer
{
public:
	SGLDepthbuffer(uint32_t width, uint32_t height);
	~SGLDepthbuffer();

	void SetValue(int x, int y, float value);
	void SetValue(const  SGLVector2u32& pos, float value);

	float GetValue(int x, int y);
	float GetValue(const  SGLVector2u32& pos);

	uint32_t GetBufferWidth();
	uint32_t GetBufferHeight();

	float* GetBuffer() const;
private:
	float* m_Buffer;
	uint32_t m_Width, m_Height;
};


class SGLFramebuffer
{
public:
	SGLFramebuffer(uint32_t width,uint32_t height);
	SGLFramebuffer(const std::shared_ptr<SGLColorbuffer>& colorBuffer, const std::shared_ptr<SGLDepthbuffer>& depthBuffer);
	~SGLFramebuffer();

	const std::shared_ptr<SGLColorbuffer>& GetColorbuffer() const;
	const std::shared_ptr<SGLDepthbuffer>& GetDepthbuffer() const;
private:
	std::shared_ptr<SGLColorbuffer> m_Colorbuffer;
	std::shared_ptr<SGLDepthbuffer> m_Depthbuffer;
};

