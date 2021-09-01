#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include "Vector2.h"
#include "Vector4.h"
namespace SGL
{
	template <typename T>
	class Buffer
	{
	public:
		Buffer(uint32_t size);
		~Buffer();

		void SetValue(uint32_t pos, const T& data);
		T GetValue(uint32_t pos) const;

		const std::vector<T>& GetBufferData() const;
		size_t GetBufferSize() const;

		T& operator[](uint32_t pos);
		const T& operator[](uint32_t pos) const;
	private:
		std::vector<T> m_BufferData;
	};

	class ColorAttahment
	{
	public:
		ColorAttahment(const Vector2u32& bufferExtent);
		~ColorAttahment();

		void SetValue(uint32_t x, uint32_t y, const Vector4f& color);
		void SetValue(const Vector2u32& pos, const Vector4f& color);
		Vector4u8 GetValue(uint32_t x, uint32_t y) const;
		Vector4u8 GetValue(const Vector2u32& pos) const;

		const Buffer<uint8_t>& GetBuffer() const;
		const Vector2u32& GetBufferExtent() const;

	private:
		Buffer<uint8_t> m_Buffer;
		Vector2u32 m_BufferExtent;
	};

	class DepthAttachment
	{
	public:
		DepthAttachment(const Vector2u32& bufferExtent);
		~DepthAttachment();

		void SetValue(int x, int y, float value);
		void SetValue(const Vector2u32& pos, float value);

		float GetValue(int x, int y);
		float GetValue(const Vector2u32& pos);

		const Vector2u32& GetBufferExtent();

		const Buffer<float>& GetBuffer() const;

	private:
		Buffer<float> m_Buffer;
		Vector2u32 m_BufferExtent;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const Vector2u32& bufferExtent);
		Framebuffer(const std::shared_ptr<ColorAttahment>& colorBuffer, const std::shared_ptr<DepthAttachment>& depthBuffer);
		~Framebuffer();

		const std::shared_ptr<ColorAttahment>& GetColorAttahment() const;
		const std::shared_ptr<DepthAttachment>& GetDepthAttachment() const;

	private:
		std::shared_ptr<ColorAttahment> m_ColorAttahment;
		std::shared_ptr<DepthAttachment> m_DepthAttachment;
	};
	template<typename T>
	inline Buffer<T>::Buffer(uint32_t size)
	{
		m_BufferData.resize(size);
	}
	template<typename T>
	inline Buffer<T>::~Buffer()
	{
	}
	template<typename T>
	inline void Buffer<T>::SetValue(uint32_t pos, const T& data)
	{
		if (pos > m_BufferData.size() || pos < 0)
			std::cout << "Out of buffer size:max size is" << m_BufferData.size() << ",wanted pos is" << pos << std::endl;
		assert(pos <= m_BufferData.size());
		m_BufferData[pos] = data;
	}

	template<typename T>
	inline T Buffer<T>::GetValue(uint32_t pos) const
	{
		if (pos > m_BufferData.size() || pos < 0)
			std::cout << "Out of buffer size:max size is" << m_BufferData.size() << ",wanted pos is" << pos << std::endl;
		assert(pos <= m_BufferData.size());
		return m_BufferData[pos];
	}

	template<typename T>
	inline const std::vector<T>& Buffer<T>::GetBufferData() const
	{
		return m_BufferData;
	}
	template<typename T>
	inline size_t Buffer<T>::GetBufferSize() const
	{
		return m_BufferData.size();
	}
	template<typename T>
	inline T& Buffer<T>::operator[](uint32_t pos)
	{
		if (pos > m_BufferData.size()||pos<0)
			std::cout << "Out of buffer size:max size is" << m_BufferData.size() << ",wanted pos is" << pos << std::endl;
		assert(pos <= m_BufferData.size());
		return m_BufferData[pos];
	}
	template<typename T>
	inline const T& Buffer<T>::operator[](uint32_t pos) const
	{
		if (pos > m_BufferData.size() || pos < 0)
			std::cout << "Out of buffer size:max size is" << m_BufferData.size() << ",wanted pos is" << pos << std::endl;
		assert(pos <= m_BufferData.size());
		return m_BufferData[pos];
	}
}