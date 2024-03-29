#include "GraphicsPipeline.h"
#include "Math.h"
#include "Macros.h"
#include <array>
#include <iostream>
#include <cassert>
namespace SGL
{

	GraphicsPipeline::GraphicsPipeline(const GraphicsPipelineCreateInfo &info)
		: m_DefaultFramebuffer(std::make_shared<Framebuffer>(info.defaultBufferExtent)), m_Info(info),
		  varyings0(Varyings()), varyings1(Varyings()), varyings2(Varyings()), interpolatedVaryings(Varyings())
	{
	}

	GraphicsPipeline::~GraphicsPipeline()
	{
	}

	const std::shared_ptr<Framebuffer> &GraphicsPipeline::GetFramebuffer() const
	{
		return m_DefaultFramebuffer;
	}

	void GraphicsPipeline::ClearBuffer()
	{
		if ((m_Info.clearBufferType & BufferType::COLOR_BUFFER) == BufferType::COLOR_BUFFER)
			ClearColorBuffer();

		if ((m_Info.clearBufferType & BufferType::DEPTH_BUFFER) == BufferType::DEPTH_BUFFER)
			ClearDepthBuffer();

		if ((m_Info.clearBufferType & BufferType::STENCIL_BUFFER) == BufferType::STENCIL_BUFFER)
			ClearStencilBuffer();
	}

	void GraphicsPipeline::ClearColorBuffer()
	{
		for (uint32_t i = 0; i < m_DefaultFramebuffer->GetColorAttahment()->GetBufferExtent().x; ++i)
			for (uint32_t j = 0; j < m_DefaultFramebuffer->GetColorAttahment()->GetBufferExtent().y; ++j)
				m_DefaultFramebuffer->GetColorAttahment()->SetValue(i, j, m_Info.clearColor);
	}

	void GraphicsPipeline::ClearDepthBuffer()
	{
		for (uint32_t i = 0; i < m_DefaultFramebuffer->GetColorAttahment()->GetBufferExtent().x; ++i)
			for (uint32_t j = 0; j < m_DefaultFramebuffer->GetColorAttahment()->GetBufferExtent().y; ++j)
				m_DefaultFramebuffer->GetDepthAttachment()->SetValue(i, j, m_Info.clearDepth);
	}

	void GraphicsPipeline::ClearStencilBuffer()
	{
	}

	void GraphicsPipeline::DrawArrays(uint32_t startIndex, size_t vertexArraySize)
	{
		switch (m_Info.renderType)
		{
		case RenderType::POINT:
			for (uint32_t i = startIndex; i < vertexArraySize; ++i)
				DrawPoint(i);
			break;
		case RenderType::LINE:
			for (uint32_t i = startIndex; i < vertexArraySize; i += 2)
				DrawLine(i, i + 1);
			break;
		case RenderType::LINE_STRIP:
			for (uint32_t i = startIndex; i < vertexArraySize; i++)
				DrawLine(i, i + 1);
			break;
		case RenderType::SOLID_TRIANGLE:
			for (uint32_t i = startIndex; i < vertexArraySize - 2; i += 3)
				DrawTriangle_Solid(i, i + 1, i + 2);
			break;
		case RenderType::SOLID_TRIANGLE_STRIP:
			for (uint32_t i = startIndex; i < vertexArraySize - 2; ++i)
				DrawTriangle_Solid(i, i + 1, i + 2);
			break;
		case RenderType::WIRE_TRIANGLE:
			for (uint32_t i = startIndex; i < vertexArraySize - 2; i += 3)
				DrawTriangle_WireFrame(i, i + 1, i + 2);
			break;
		case RenderType::WIRE_TRIANGLE_STRIP:
			for (uint32_t i = startIndex; i < vertexArraySize - 2; ++i)
				DrawTriangle_WireFrame(i, i + 1, i + 2);
			break;
		default:
			break;
		}
	}

	void GraphicsPipeline::DrawElements(uint32_t startIndex, const std::vector<uint32_t> &indices)
	{
		switch (m_Info.renderType)
		{
		case RenderType::POINT:
			for (uint32_t i = startIndex; i < indices.size(); ++i)
				DrawPoint(indices.at(i));
			break;
		case RenderType::LINE:
			for (uint32_t i = startIndex; i < indices.size() - 1; i += 2)
				DrawLine(indices.at(i), indices.at(i + 1));
			break;
		case RenderType::LINE_STRIP:
			for (uint32_t i = startIndex; i < indices.size() - 1; ++i)
				DrawLine(indices.at(i), indices.at(i + 1));
			break;
		case RenderType::SOLID_TRIANGLE:
			for (uint32_t i = startIndex; i < indices.size() - 2; i += 3)
				DrawTriangle_Solid(indices.at(i), indices.at(i + 1), indices.at(i + 2));
			break;
		case RenderType::SOLID_TRIANGLE_STRIP:
			for (uint32_t i = startIndex; i < indices.size() - 2; ++i)
				DrawTriangle_Solid(indices.at(i), indices.at(i + 1), indices.at(i + 2));
			break;
		case RenderType::WIRE_TRIANGLE:
			for (uint32_t i = startIndex; i < indices.size() - 2; i += 3)
				DrawTriangle_WireFrame(indices.at(i), indices.at(i + 1), indices.at(i + 2));
			break;
		case RenderType::WIRE_TRIANGLE_STRIP:
			for (uint32_t i = startIndex; i < indices.size() - 2; ++i)
				DrawTriangle_WireFrame(indices.at(i), indices.at(i + 1), indices.at(i + 2));
			break;
		default:
			break;
		}
	}

	void GraphicsPipeline::DrawPoint(uint32_t vertexIndex)
	{
		CheckGraphicsShaderProgram();
		//模型空间->世界空间->观察空间->裁剪空间->NDC空间->屏幕空间
		Vector4f clip_position = m_Info.shaderProgram->VertexShader(vertexIndex, varyings0);
		Vector3f ndc_position = ToNDCSpace(clip_position);
		Vector2i32 screen_position = ToScreenSpace(ndc_position);

		if (0 <= screen_position.x && screen_position.x < m_Info.defaultBufferExtent.x && 0 <= screen_position.y && screen_position.y < m_Info.defaultBufferExtent.y)
		{
			//根据指定的顶点绘制像素
			for (uint32_t i = screen_position.x - m_Info.pointSize / 2; i <= screen_position.x + m_Info.pointSize / 2; ++i)
				for (uint32_t j = screen_position.y - m_Info.pointSize / 2; j <= screen_position.y + m_Info.pointSize / 2; ++j)
					if (i >= 0 && i < m_Info.defaultBufferExtent.x && j >= 0 && j < m_Info.defaultBufferExtent.y)
						if (m_DefaultFramebuffer->GetDepthAttachment()->GetValue(i, j) > ndc_position.z)
						{
							m_DefaultFramebuffer->GetDepthAttachment()->SetValue(i, j, ndc_position.z);
							m_DefaultFramebuffer->GetColorAttahment()->SetValue(i, j, m_Info.shaderProgram->FragmentShader(varyings0));
						}
		}
	}

	void GraphicsPipeline::DrawLine(uint32_t vertexIndex0, uint32_t vertexIndex1)
	{
		// CheckGraphicsShaderProgram();
		// //模型空间->世界空间->观察空间->裁剪空间->NDC空间->屏幕空间
		// Varyings varyings0;
		// Vector4f clip_position0 = m_Info.shaderProgram->VertexShader(model_p0, varyings0);
		// Vector3f ndc_position_p0 = ToNDCSpace(clip_position0);
		// Vector2i32 screen_position_p0 = ToScreenSpace(ndc_position_p0);

		// Varyings varyings1;
		// Vector4f clip_position1 = m_Info.shaderProgram->VertexShader(model_p1, varyings1);
		// Vector3f ndc_position_p1 = ToNDCSpace(clip_position1);
		// Vector2i32 screen_position_p1 = ToScreenSpace(ndc_position_p1);

		// //Bresenham画线算法
		// bool reverse = false;
		// if (Math::Abs(static_cast<int>(screen_position_p1.x - screen_position_p0.x)) < Math::Abs(static_cast<int>(screen_position_p1.y - screen_position_p0.y)))
		// {
		// 	std::swap(screen_position_p0.x, screen_position_p0.y);
		// 	std::swap(screen_position_p1.x, screen_position_p1.y);
		// 	reverse = true;
		// }
		// if (screen_position_p0.x > screen_position_p1.x)
		// {
		// 	std::swap(screen_position_p0.x, screen_position_p1.x);
		// 	std::swap(screen_position_p0.y, screen_position_p1.y);
		// }

		// int dx = static_cast<int>(screen_position_p1.x - screen_position_p0.x);
		// int dy = static_cast<int>(screen_position_p1.y - screen_position_p0.y);

		// int pk0 = std::abs(dy) * 2;
		// int pk = 0;
		// uint32_t y = screen_position_p0.y;

		// float screen_pos_len = (screen_position_p1 - screen_position_p0).Length();
		// Vector3f ndc_dir = ndc_position_p1 - ndc_position_p0;
		// for (uint32_t x = screen_position_p0.x; x <= screen_position_p1.x; ++x)
		// {
		// 	if (0 <= x && x < m_Info.defaultBufferExtent.x && 0 <= y && y < m_Info.defaultBufferExtent.y)
		// 	{
		// 		////将直线映射回原来的区域
		// 		if (reverse)
		// 			std::swap(x, y);

		// 		//对每个像素进行着色
		// 		float factor = Vector2f(x - screen_position_p0.x, y - screen_position_p0.y).Length() / screen_pos_len;

		// 		Vertex screen_vertex;
		// 		screen_vertex.position = Vector3f(x, y, ndc_position_p0.z * (1 - factor) + ndc_position_p1.z * factor);
		// 		screen_vertex.texcoord = model_p0.texcoord * (1 - factor) + model_p1.texcoord * factor;

		// 		//进行深度测试
		// 		if (m_DefaultFramebuffer->GetDepthAttachment()->GetValue(x, y) >= screen_vertex.position.z)
		// 		{
		// 			m_DefaultFramebuffer->GetDepthAttachment()->SetValue(x, y, screen_vertex.position.z);
		// 			m_DefaultFramebuffer->GetColorAttahment()->SetValue(x, y, m_Info.shaderProgram->FragmentShader(screen_vertex, m_Info.defaultBufferExtent));
		// 		}

		// 		//继续下一步的计算
		// 		if (reverse)
		// 			std::swap(x, y);

		// 		pk += pk0;
		// 		if (pk > dx)
		// 		{
		// 			y += (screen_position_p1.y > screen_position_p0.y ? 1 : -1);
		// 			pk -= dx * 2;
		// 		}
		// 	}
		// }
	}

	void GraphicsPipeline::DrawTriangle_WireFrame(uint32_t vertexIndex0, uint32_t vertexIndex1, uint32_t vertexIndex2)
	{
		CheckGraphicsShaderProgram();
		// DrawLine(model_p0, model_p1);
		// DrawLine(model_p1, model_p2);
		// DrawLine(model_p2, model_p0);
	}

	void GraphicsPipeline::DrawTriangle_Solid(uint32_t vertexIndex0, uint32_t vertexIndex1, uint32_t vertexIndex2)
	{
		CheckGraphicsShaderProgram();
		//模型空间->世界空间->观察空间->裁剪空间->NDC空间->屏幕空间
		Vector4f clip_position0 = m_Info.shaderProgram->VertexShader(vertexIndex0, varyings0);
		Vector3f ndc_position_p0 = ToNDCSpace(clip_position0);
		Vector2i32 screen_position_p0 = ToScreenSpace(ndc_position_p0);
		float recip_p0_w = 1.0f / clip_position0.w;

		Vector4f clip_position1 = m_Info.shaderProgram->VertexShader(vertexIndex1, varyings1);
		Vector3f ndc_position_p1 = ToNDCSpace(clip_position1);
		Vector2i32 screen_position_p1 = ToScreenSpace(ndc_position_p1);
		float recip_p1_w = 1.0f / clip_position1.w;

		Vector4f clip_position2 = m_Info.shaderProgram->VertexShader(vertexIndex2, varyings2);
		Vector3f ndc_position_p2 = ToNDCSpace(clip_position2);
		Vector2i32 screen_position_p2 = ToScreenSpace(ndc_position_p2);
		float recip_p2_w = 1.0f / clip_position2.w;

		Vector3f recip_w = Vector3f(recip_p0_w, recip_p1_w, recip_p2_w);

		//三角形光栅化部分

		//取三角形的AABB
		int32_t xMin = Math::Min(screen_position_p0.x, Math::Min(screen_position_p1.x, screen_position_p2.x));
		int32_t yMin = Math::Min(screen_position_p0.y, Math::Min(screen_position_p1.y, screen_position_p2.y));
		int32_t xMax = Math::Max(screen_position_p0.x, Math::Max(screen_position_p1.x, screen_position_p2.x));
		int32_t yMax = Math::Max(screen_position_p0.y, Math::Max(screen_position_p1.y, screen_position_p2.y));

		//将AABB范围截断为屏幕大小，在屏幕外的像素则丢弃
		xMin = Math::Clamp(xMin, 0, static_cast<int32_t>(m_Info.defaultBufferExtent.x - 1));
		yMin = Math::Clamp(yMin, 0, static_cast<int32_t>(m_Info.defaultBufferExtent.y - 1));
		xMax = Math::Clamp(xMax, 0, static_cast<int32_t>(m_Info.defaultBufferExtent.x - 1));
		yMax = Math::Clamp(yMax, 0, static_cast<int32_t>(m_Info.defaultBufferExtent.y - 1));

		//重心坐标判断AABB内的当前顶点是否在三角形内部
		for (uint32_t x = xMin; x <= xMax; ++x)
		{
			for (uint32_t y = yMin; y <= yMax; ++y)
			{
				Vector3f screen_bc_coord = BaryCenteric(screen_position_p0, screen_position_p1, screen_position_p2, Vector2i32(x, y));

#define VARYING_INTERPOLATION(container)                                                                                                                                   \
	for (const auto &v : varyings0.container)                                                                                                                              \
		interpolatedVaryings.container[v.first] = InterpolateVaryingBarycenteric(varyings0.container[v.first], varyings1.container[v.first], varyings2.container[v.first], \
																				 screen_bc_coord,                                                                          \
																				 recip_w);

				//varyings0 varyings1,varyings2中对应容器的个数一样
				VARYING_INTERPOLATION(m_DVaryings);
				VARYING_INTERPOLATION(m_FVaryings);
				VARYING_INTERPOLATION(m_I64Varyings);
				VARYING_INTERPOLATION(m_U64Varyings);
				VARYING_INTERPOLATION(m_I32Varyings);
				VARYING_INTERPOLATION(m_U32Varyings);
				VARYING_INTERPOLATION(m_I16Varyings);
				VARYING_INTERPOLATION(m_U16Varyings);
				VARYING_INTERPOLATION(m_I8Varyings);
				VARYING_INTERPOLATION(m_U8Varyings);
				VARYING_INTERPOLATION(m_Vector2fVaryings);
				VARYING_INTERPOLATION(m_Vector2dVaryings);
				VARYING_INTERPOLATION(m_Vector2i64Varyings);
				VARYING_INTERPOLATION(m_Vector2u64Varyings);
				VARYING_INTERPOLATION(m_Vector2i32Varyings);
				VARYING_INTERPOLATION(m_Vector2u32Varyings);
				VARYING_INTERPOLATION(m_Vector2i16Varyings);
				VARYING_INTERPOLATION(m_Vector2u16Varyings);
				VARYING_INTERPOLATION(m_Vector2i8Varyings);
				VARYING_INTERPOLATION(m_Vector2u8Varyings);
				VARYING_INTERPOLATION(m_Vector3fVaryings);
				VARYING_INTERPOLATION(m_Vector3dVaryings);
				VARYING_INTERPOLATION(m_Vector3i64Varyings);
				VARYING_INTERPOLATION(m_Vector3u64Varyings);
				VARYING_INTERPOLATION(m_Vector3i32Varyings);
				VARYING_INTERPOLATION(m_Vector3u32Varyings);
				VARYING_INTERPOLATION(m_Vector3i16Varyings);
				VARYING_INTERPOLATION(m_Vector3u16Varyings);
				VARYING_INTERPOLATION(m_Vector3i8Varyings);
				VARYING_INTERPOLATION(m_Vector3u8Varyings);

				VARYING_INTERPOLATION(m_Vector4fVaryings);
				VARYING_INTERPOLATION(m_Vector4dVaryings);
				VARYING_INTERPOLATION(m_Vector4i64Varyings);
				VARYING_INTERPOLATION(m_Vector4u64Varyings);
				VARYING_INTERPOLATION(m_Vector4i32Varyings);
				VARYING_INTERPOLATION(m_Vector4u32Varyings);
				VARYING_INTERPOLATION(m_Vector4i16Varyings);
				VARYING_INTERPOLATION(m_Vector4u16Varyings);
				VARYING_INTERPOLATION(m_Vector4i8Varyings);
				VARYING_INTERPOLATION(m_Vector4u8Varyings);

				VARYING_INTERPOLATION(m_Matrix2fVaryings);
				VARYING_INTERPOLATION(m_Matrix3fVaryings);
				VARYING_INTERPOLATION(m_Matrix4fVaryings);

#undef VARYING_INTERPOLATION

				Vector4f screen_position = Vector4f(x, y, InterpolateBarycenteric(ndc_position_p0.z, ndc_position_p1.z, ndc_position_p2.z, screen_bc_coord), InterpolateBarycenteric(clip_position0.w, clip_position1.w, clip_position2.w, screen_bc_coord));
				//如果当前片元在三角形内且通过深度测试则渲染到颜色缓存中，否则丢弃该片元(这里使用提前深度测试)
				if (screen_bc_coord.x >= 0.0f && screen_bc_coord.y >= 0.0f && screen_bc_coord.z >= 0.0f &&
					m_DefaultFramebuffer->GetDepthAttachment()->GetValue(x, y) >= screen_position.z && screen_position.z >= -1.0f)
				{
					m_DefaultFramebuffer->GetDepthAttachment()->SetValue(x, y, screen_position.z);
					m_DefaultFramebuffer->GetColorAttahment()->SetValue(x, y, m_Info.shaderProgram->FragmentShader(interpolatedVaryings));
				}
			}
		}
	}

	Vector3f GraphicsPipeline::BaryCenteric(const Vector2i32 &p0, const Vector2i32 &p1, const Vector2i32 &p2, const Vector2i32 &p)
	{
		Vector2i32 p1p0 = p1 - p0;
		Vector2i32 p2p0 = p2 - p0;
		Vector2i32 p0p = p0 - p;

		Vector3f factor = Vector3f::Cross(Vector3f(p2p0.x, p1p0.x, p0p.x), Vector3f(p2p0.y, p1p0.y, p0p.y));
		if (Math::Abs(factor.z) > 1e-2)
			return Vector3f(1.0f - (factor.x + factor.y) / factor.z, factor.y / factor.z, factor.x / factor.z);
		return Vector3f(-1.0f, -1.0f, -1.0f);
	}

	Vector3f GraphicsPipeline::ToNDCSpace(const Vector4f &v)
	{
		return Vector4f::ToVector3(Vector4f::DivideByW(v));
	}

	Vector2i32 GraphicsPipeline::ToScreenSpace(const Vector3f &v)
	{
		int32_t screen_x = (m_Info.defaultBufferExtent.x - 1) * ((v.x + 1.0f) / 2.0f);
		int32_t screen_y = (m_Info.defaultBufferExtent.y - 1) * ((v.y + 1.0f) / 2.0f);
		return Vector2i32(screen_x, screen_y);
	}

	void GraphicsPipeline::CheckGraphicsShaderProgram()
	{
		if (m_Info.shaderProgram != nullptr)
			return;
		ERROR_OUTPUT_LN("Current binding shader is null!");
		assert(m_Info.shaderProgram != nullptr);
	}
}
