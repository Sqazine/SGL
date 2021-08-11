#pragma once
#include <cstdint>
#include <memory>
#include <array>
#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"

namespace SGL
{

	enum class TextureChannelMode
	{
		R8,
		RG8,
		RGB8,
		RGBA8,
		
		R32F,
		RG32F,
		RGB32F,
		RGBA32F,
	};

	enum class TextureWrapMode
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum class TextureFilterMode
	{
		NEARST,
		BILINEAR,
		TRILINEAR
	};

	struct Texture2DCreateInfo
	{
		TextureChannelMode channelMode=TextureChannelMode::RGB8;
		uint32_t width=0,height=0;
		TextureWrapMode wrapModeS=TextureWrapMode::REPEAT,wrapModeT=TextureWrapMode::REPEAT;
		void* data=nullptr;
	};

	class Texture2D
	{
	public:
		Texture2D(const Texture2DCreateInfo& createInfo={});
		virtual ~Texture2D();

		Vector4f GetTexel(float u, float v) const;
		Vector4f GetTexel(const Vector2f &pos) const;
		
		const Texture2DCreateInfo& GetCreateInfo() const;
	protected:
		Texture2DCreateInfo m_CreateInfo;
	};

	struct TextureCubeCreateInfo
	{
		TextureChannelMode channelMode=TextureChannelMode::RGB8;
		uint32_t width=0,height=0;
		TextureWrapMode wrapModeS=TextureWrapMode::REPEAT,wrapModeT=TextureWrapMode::REPEAT,wrapModeR=TextureWrapMode::REPEAT;
		std::array<void*,6> data;
	};

	class TextureCube
	{
	public:
		TextureCube(const TextureCubeCreateInfo& createInfo={});
		virtual ~TextureCube();

		Vector4f GetTexel(float u, float v, float w) const;
		Vector4f GetTexel(const Vector3f &pos) const;

		const TextureCubeCreateInfo& GetCreateInfo() const;

	protected:
		TextureCubeCreateInfo m_CreateInfo;
	};
}