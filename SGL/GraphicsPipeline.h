#pragma once
#include <cstdint>
#include <vector>
#include "Buffer.h"
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
		STENCIL_BUFFER=0x0100,
	};


	enum class CullType
	{
		BACK,
		FRONT,
		FRONT_AND_BACK
	};

	enum class FrontFaceType
	{
		CW,
		CCW
	};

	enum class RenderType
	{
		POINT,

		LINE,
		LINE_STRIP,

		SOLID_TRIANGLE,
		SOLID_TRIANGLE_STRIP,

		WIRE_TRIANGLE,
		WIRE_TRIANGLE_STRIP
	};

	enum class BlendType
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

	struct GraphicsPipelineCreateInfo
	{
		Vector2u32 defaultBufferExtent=Vector2u32::ZERO;
		GraphicsShaderProgram* shaderProgram;
		Vector4f clearColor=Vector4f::ZERO;
		float clearDepth=1.0f;
		uint32_t pointSize=1;
		uint32_t lineWidth=1;
		BlendType blendType=BlendType::ZERO;
		RenderType renderType=RenderType::SOLID_TRIANGLE;
		CullType cullType=CullType::BACK;
		FrontFaceType frontFaceType=FrontFaceType::CCW;
		uint32_t clearBufferType=BufferType::COLOR_BUFFER|BufferType::DEPTH_BUFFER|BufferType::STENCIL_BUFFER;
	};

	class GraphicsPipeline
	{
	public:
		GraphicsPipeline(const GraphicsPipelineCreateInfo& info);
		~GraphicsPipeline();

		const std::shared_ptr<Framebuffer> &GetFramebuffer() const;

		void ClearBuffer();

		void DrawArrays( uint32_t startIndex, size_t vertexArraySize);
		void DrawElements( uint32_t startIndex, const std::vector<uint32_t> &indices);

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

		GraphicsPipelineCreateInfo m_Info;

		std::shared_ptr<Framebuffer> m_DefaultFramebuffer;
		Varyings varyings0;
		Varyings varyings1;
		Varyings varyings2;
		Varyings interpolatedVaryings;
	};

	template <typename T>
	inline T GraphicsPipeline::InterpolateVaryingBarycenteric(const T &v0, const T &v1, const T &v2, const Vector3f &barycenter,const Vector3f& recip_w)
	{

		T value= v0 * barycenter.x*recip_w.x + v1 * barycenter.y*recip_w.y + v2 * barycenter.z*recip_w.z;
		return value/(barycenter.x*recip_w.x + barycenter.y*recip_w.y + barycenter.z*recip_w.z);
	}

	template<typename T>
	inline 	T GraphicsPipeline::InterpolateBarycenteric(const T &v0, const T &v1, const T &v2, const Vector3f &barycenter)
	{
		return v0 * barycenter.x + v1 * barycenter.y + v2 * barycenter.z;
	}

}