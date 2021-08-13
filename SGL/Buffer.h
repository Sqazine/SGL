#pragma once
#include <vector>
#include <memory>
#include "Vector2.h"
#include "Vector4.h"
namespace SGL
{
	template <typename T>
	class Buffer2D
	{
	public:
		Buffer2D();
		~Buffer2D();

		void SetValue(uint32_t x, uint32_t y, const T &data);
		void SetValue(const Vector2u32 &pos, const T &data);
		T GetValue(uint32_t x, uint32_t y) const;
		T GetValue(const Vector2u32 &pos) const;

		const std::vector<T> &GetBufferData() const;
		const Vector2u32 &GetBufferExtent() const;

	private:
		std::vector<T> m_BufferData;
		Vector2u32 m_Extent;
	};

	template <typename T>
	class Buffer1D
	{
	public:
		Buffer1D();
		~Buffer1D();

		void SetValue(uint32_t pos, const T &data);
		T GetValue(uint32_t pos) const;

		const std::vector<T> &GetBufferData() const;
		const uint32_t &GetBufferExtent() const;

	private:
		std::vector<T> m_BufferData;
		uint32_t m_Extent;
	};

	class Colorbuffer
	{
	public:
		Colorbuffer(const Vector2u32 &bufferExtent);
		~Colorbuffer();

		void SetValue(uint32_t x, uint32_t y, const Vector4f &color);
		void SetValue(const Vector2u32 &pos, const Vector4f &color);
		Vector4u8 GetValue(uint32_t x, uint32_t y) const;
		Vector4u8 GetValue(const Vector2u32 &pos) const;

		const std::vector<uint8_t> &GetBuffer() const;
		const Vector2u32 &GetBufferExtent() const;

	private:
		std::vector<uint8_t> m_Buffer;
		Vector2u32 m_BufferExtent;
	};

	class Depthbuffer
	{
	public:
		Depthbuffer(const Vector2u32 &bufferExtent);
		~Depthbuffer();

		void SetValue(int x, int y, float value);
		void SetValue(const Vector2u32 &pos, float value);

		float GetValue(int x, int y);
		float GetValue(const Vector2u32 &pos);

		const Vector2u32 &GetBufferExtent();

		const std::vector<float> &GetBuffer() const;

	private:
		std::vector<float> m_Buffer;
		Vector2u32 m_BufferExtent;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const Vector2u32 &bufferExtent);
		Framebuffer(const std::shared_ptr<Colorbuffer> &colorBuffer, const std::shared_ptr<Depthbuffer> &depthBuffer);
		~Framebuffer();

		const std::shared_ptr<Colorbuffer> &GetColorbuffer() const;
		const std::shared_ptr<Depthbuffer> &GetDepthbuffer() const;

	private:
		std::shared_ptr<Colorbuffer> m_Colorbuffer;
		std::shared_ptr<Depthbuffer> m_Depthbuffer;
	};
}