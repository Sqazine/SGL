#pragma once
#include <cstdint>
#include <vector>
#include "FrameBuffer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Shader.h"

namespace SGL
{
	enum BufferType
	{
		COLOR_BUFFER=0x0001,
		DEPTH_BUFFER=0x0010,
		STENCIL_BUFFER=0x0100
	};


	enum class RenderMode
	{
		POINT,

		LINE,
		LINE_STRIP,

		SOLID_TRIANGLE,
		SOLID_TRIANGLE_STRIP,

		WIRE_TRIANGLE,
		WIRE_TRIANGLE_STRIP
	};

	enum class BlendMode
	{
		ZERO,
		ONE,

		SRC_COLOR,
		ONE_MINUS_SRC_COLOR,

		DST_COLOR,
		ONE_MINUS_DST_COLOR,

		SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA,

		DST_ALPHA,
		ONE_MINUS_DST_ALPHA,

		CONSTANT_COLOR,
		ONE_MINUS_CONSTANT_COLOR,

		CONSTANT_ALPHA,
		ONE_MINUS_CONSTANT_ALPHA
	};

	class Rasterizer
	{
	public:
		Rasterizer(const Vector2u32 bufferExtent);
		~Rasterizer();

		const std::shared_ptr<Framebuffer> &GetFramebuffer() const;

		void SetGraphicsShaderProgram(const std::shared_ptr<GraphicsShaderProgram> &s);
		const std::shared_ptr<GraphicsShaderProgram> &GetGraphicsShaderProgram() const;

		void SetPointSize(uint32_t size);
		uint32_t GetPointSize() const;

		void SetLineWidth(uint32_t size);
		uint32_t GetLineWidth() const;

		void SetClearColor(const Vector4f &color);
		void SetClearColor(float r, float g, float b, float a);

		void Clear(uint32_t type);

		void SetBlendMode(BlendMode mode);
		const BlendMode &GetBlendMode() const;

		void DrawArrays(RenderMode mode, uint32_t startIndex, size_t vertexArraySize);
		void DrawElements(RenderMode mode, uint32_t startIndex, const std::vector<uint32_t> &indices);

	private:
		void ClearColorBuffer();
		void ClearDepthBuffer();
		void ClearStencilBuffer();

		void CheckGraphicsShaderProgram();

		template <typename T>
		T InterpolateVaryingBarycenteric(const T &v0, const T &v1, const T &v2, const Vector3f &barycenter,const Vector3f& recip_w);

		template<typename T>
		T InterpolateBarycenteric(const T &v0, const T &v1, const T &v2, const Vector3f &barycenter);

		Vector3f BaryCenteric(const Vector2i32 &p0, const Vector2i32 &p1, const Vector2i32 &p2, const Vector2i32 &p);

		Vector3f ToNDCSpace(const Vector4f &v);
		Vector2i32 ToScreenSpace(const Vector3f &v);

		void DrawPoint(uint32_t vertexIndex);
		void DrawLine(uint32_t vertexIndex0,uint32_t vertexIndex1);
		void DrawTriangle_WireFrame(uint32_t vertexIndex0, uint32_t vertexIndex1, uint32_t vertexIndex2);
		void DrawTriangle_Solid(uint32_t vertexIndex0, uint32_t vertexIndex1, uint32_t vertexIndex2);

		Vector4f m_ClearColor;

		std::shared_ptr<Framebuffer> m_Framebuffer;

		Vector2u32 m_BufferExtent;

		bool m_IsDepthTest;

		std::shared_ptr<GraphicsShaderProgram> m_GraphicsShaderProgram;
		uint32_t m_PointSize;
		uint32_t m_LineWidth;
		BlendMode m_BlendMode;

		Varyings varyings0;
		Varyings varyings1;
		Varyings varyings2;
		Varyings interpolatedVaryings;
	};

	template <typename T>
	inline T Rasterizer::InterpolateVaryingBarycenteric(const T &v0, const T &v1, const T &v2, const Vector3f &barycenter,const Vector3f& recip_w)
	{

		T value= v0 * barycenter.x*recip_w.x + v1 * barycenter.y*recip_w.y + v2 * barycenter.z*recip_w.z;
		return value/(barycenter.x*recip_w.x + barycenter.y*recip_w.y + barycenter.z*recip_w.z);
	}

	template<typename T>
	inline 	T Rasterizer::InterpolateBarycenteric(const T &v0, const T &v1, const T &v2, const Vector3f &barycenter)
	{
		return v0 * barycenter.x + v1 * barycenter.y + v2 * barycenter.z;
	}

}