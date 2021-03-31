#pragma once
#include <cstdint>
#include <vector>
#include "FrameBuffer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vertex.h"

namespace SGL
{

	enum class RENDER_MODE
	{
		POINT,

		LINE,
		LINE_STRIP,

		SOLID_TRIANGLE,
		SOLID_TRIANGLE_STRIP,

		WIRE_TRIANGLE,
		WIRE_TRIANGLE_STRIP
	};

	enum class BLEND_MODE
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

		void SetShader(const std::shared_ptr<class Shader> &s);
		const std::shared_ptr<class Shader> &GetShader() const;

		void SetPointSize(uint32_t size);
		uint32_t GetPointSize() const;

		void SetLineWidth(uint32_t size);
		uint32_t GetLineWidth() const;

		void ClearColor(const Vector4f &color);
		void ClearColor(float r, float g, float b, float a);
		void ClearDepth();
		void ClearStencil();

		void SetBlendMode(BLEND_MODE mode);
		const BLEND_MODE &GetBlendMode() const;

		void DrawArrays(RENDER_MODE mode, uint32_t index, const std::vector<struct Vertex> &vertices);
		void DrawElements(RENDER_MODE mode, uint32_t index, const std::vector<struct Vertex> &vertices, const std::vector<uint32_t> &indices);

	private:
		void CheckShader();

		Vector3f BaryCenteric(const Vector2i32 &p0, const Vector2i32 &p1, const Vector2i32 &p2, const Vector2i32 &p);

		Vector3f ToNDCSpace(const Vector4f &v);
		Vector2i32 ToScreenSpace(const Vector3f &v);

		void DrawPoint(const Vertex &model_p);
		void DrawLine(const Vertex &model_p0, const Vertex &model_p1);
		void DrawTriangle_WireFrame(const Vertex &model_p0, const Vertex &model_p1, const struct Vertex &model_p2);
		void DrawTriangle_Solid(const Vertex &model_p0, const Vertex &model_p1, const struct Vertex &model_p2);

		std::shared_ptr<Framebuffer> m_Framebuffer;

		Vector2u32 m_BufferExtent;

		bool m_IsDepthTest;

		std::shared_ptr<class Shader> m_Shader;
		uint32_t m_PointSize;
		uint32_t m_LineWidth;
		BLEND_MODE m_BlendMode;
	};
}