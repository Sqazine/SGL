#pragma once
#include <cstdint>
#include <vector>
#include "SGLFramebuffer.h"
#include "SGLVector2.h"
#include "SGLVector3.h"
#include "SGLVector4.h"
#include "SGLVertex.h"
enum class  RENDER_MODE
{
	POINT,

	LINE,
	LINE_STRIP,

	SOLID_TRIANGLE,
	SOLID_TRIANGLE_STRIP,

	WIRE_TRIANGLE,
	WIRE_TRIANGLE_STRIP
};


enum class  BLEND_MODE
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


class  SGLRasterizer
{
public:
	SGLRasterizer(const SGLVector2u32 bufferExtent);
	~SGLRasterizer();

	const std::shared_ptr<SGLFramebuffer>& GetFramebuffer() const;

	void SetShader(const std::shared_ptr<class SGLShader>& s);
	const std::shared_ptr<class SGLShader>& GetShader() const;

	void SetPointSize(uint32_t size);
	uint32_t GetPointSize() const;

	void SetLineWidth(uint32_t size);
	uint32_t GetLineWidth() const;

	void ClearColor(const  SGLVector4f& color);
	void ClearColor(float r, float g, float b, float a);
	void ClearDepth();
	void ClearStencil();

	void SetBlendMode(BLEND_MODE mode);
	const BLEND_MODE& GetBlendMode() const;


	void DrawArrays(RENDER_MODE mode, uint32_t index, const std::vector<struct SGLVertex>& vertices);
	void DrawElements(RENDER_MODE mode, uint32_t index, const std::vector<struct SGLVertex>& vertices, const std::vector<uint32_t>& indices);

private:
	SGLVector3f BaryCenteric(const SGLVector2i32& p0, const  SGLVector2i32& p1, const  SGLVector2i32& p2, const  SGLVector2i32& p);

	SGLVector3f ToNDCSpace(const   SGLVector4f& v);
	SGLVector2i32 ToScreenSpace(const  SGLVector3f& v);

	void DrawPoint(const  SGLVertex& model_p);
	void DrawLine(const  SGLVertex& model_p0, const  SGLVertex& model_p1);
	void DrawTriangle_WireFrame(const  SGLVertex& model_p0, const  SGLVertex& model_p1, const struct SGLVertex& model_p2);
	void DrawTriangle_Solid(const  SGLVertex& model_p0, const  SGLVertex& model_p1, const struct SGLVertex& model_p2);

	std::shared_ptr<SGLFramebuffer> m_Framebuffer;

	SGLVector2u32 m_BufferExtent;

	bool m_IsDepthTest;

	std::shared_ptr<class SGLShader> m_Shader;
	uint32_t m_PointSize;
	uint32_t m_LineWidth;
	BLEND_MODE m_BlendMode;
};