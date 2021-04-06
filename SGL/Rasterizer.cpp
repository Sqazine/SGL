#include "Rasterizer.h"
#include "Vertex.h"
#include "Math.h"
#include "Shader.h"
#include <array>
#include <iostream>
#include "Error.h"
#include <cassert>
namespace SGL
{

	Rasterizer::Rasterizer(const Vector2u32 bufferExtent)
		: m_Framebuffer(std::make_shared<Framebuffer>(bufferExtent)), m_BufferExtent(bufferExtent), m_Shader(nullptr),
		  m_PointSize(1), m_LineWidth(1), m_BlendMode(BLEND_MODE::ONE)
	{
	}

	Rasterizer::~Rasterizer()
	{
	}

	const std::shared_ptr<Framebuffer> &Rasterizer::GetFramebuffer() const
	{
		return m_Framebuffer;
	}

	void Rasterizer::ClearColor(const Vector4f &color)
	{
		for (uint32_t i = 0; i < m_Framebuffer->GetColorbuffer()->GetBufferExtent().x; ++i)
			for (uint32_t j = 0; j < m_Framebuffer->GetColorbuffer()->GetBufferExtent().y; ++j)
				m_Framebuffer->GetColorbuffer()->SetValue(i, j, color);
	}

	void Rasterizer::ClearColor(float r, float g, float b, float a)
	{
		ClearColor(Vector4f(r, g, b, a));
	}

	void Rasterizer::ClearDepth()
	{
		for (uint32_t i = 0; i < m_Framebuffer->GetColorbuffer()->GetBufferExtent().x; ++i)
			for (uint32_t j = 0; j < m_Framebuffer->GetColorbuffer()->GetBufferExtent().y; ++j)
				m_Framebuffer->GetDepthbuffer()->SetValue(i, j, 1.0f);
	}

	void Rasterizer::SetBlendMode(BLEND_MODE mode)
	{
		m_BlendMode = mode;
	}

	const BLEND_MODE &Rasterizer::GetBlendMode() const
	{
		return m_BlendMode;
	}

	void Rasterizer::SetPointSize(uint32_t size)
	{
		m_PointSize = size;
	}

	uint32_t Rasterizer::GetPointSize() const
	{
		return m_PointSize;
	}

	void Rasterizer::SetLineWidth(uint32_t size)
	{
		m_LineWidth = size;
	}

	uint32_t Rasterizer::GetLineWidth() const
	{
		return m_LineWidth;
	}

	void Rasterizer::DrawArrays(RENDER_MODE mode, uint32_t index, const std::vector<Vertex> &vertices)
	{
		switch (mode)
		{
		case RENDER_MODE::POINT:
			for (uint32_t i = index; i < vertices.size(); ++i)
				DrawPoint(vertices.at(i));
			break;
		case RENDER_MODE::LINE:
			for (uint32_t i = index; i < vertices.size() - 1; i += 2)
				DrawLine(vertices.at(i), vertices.at(i + 1));
			break;
		case RENDER_MODE::LINE_STRIP:
			for (uint32_t i = index; i < vertices.size() - 1; i++)
				DrawLine(vertices.at(i), vertices.at(i + 1));
			break;
		case RENDER_MODE::SOLID_TRIANGLE:
			for (uint32_t i = index; i < vertices.size() - 2; i += 3)
				DrawTriangle_Solid(vertices.at(i), vertices.at(i + 1), vertices.at(i + 2));
			break;
		case RENDER_MODE::SOLID_TRIANGLE_STRIP:
			for (uint32_t i = index; i < vertices.size() - 2; ++i)
				DrawTriangle_Solid(vertices.at(i), vertices.at(i + 1), vertices.at(i + 2));
			break;
		case RENDER_MODE::WIRE_TRIANGLE:
			for (uint32_t i = index; i < vertices.size() - 2; i += 3)
				DrawTriangle_WireFrame(vertices.at(i), vertices.at(i + 1), vertices.at(i + 2));
			break;
		case RENDER_MODE::WIRE_TRIANGLE_STRIP:
			for (uint32_t i = index; i < vertices.size() - 2; ++i)
				DrawTriangle_WireFrame(vertices.at(i), vertices.at(i + 1), vertices.at(i + 2));
			break;
		default:
			break;
		}
	}

	void Rasterizer::DrawElements(RENDER_MODE mode, uint32_t index, const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices)
	{
		switch (mode)
		{
		case RENDER_MODE::POINT:
			for (uint32_t i = index; i < indices.size(); ++i)
				DrawPoint(vertices.at(indices.at(i)));
			break;
		case RENDER_MODE::LINE:
			for (uint32_t i = index; i < indices.size() - 1; i += 2)
				DrawLine(vertices.at(indices.at(i)), vertices.at(indices.at(i + 1)));
			break;
		case RENDER_MODE::LINE_STRIP:
			for (uint32_t i = index; i < indices.size() - 1; ++i)
				DrawLine(vertices.at(indices.at(i)), vertices.at(indices.at(i + 1)));
			break;
		case RENDER_MODE::SOLID_TRIANGLE:
			for (uint32_t i = index; i < indices.size() - 2; i += 3)
				DrawTriangle_Solid(vertices.at(indices.at(i)), vertices.at(indices.at(i + 1)), vertices.at(indices.at(i + 2)));
			break;
		case RENDER_MODE::SOLID_TRIANGLE_STRIP:
			for (uint32_t i = index; i < indices.size() - 2; ++i)
				DrawTriangle_Solid(vertices.at(indices.at(i)), vertices.at(indices.at(i + 1)), vertices.at(indices.at(i + 2)));
			break;
		case RENDER_MODE::WIRE_TRIANGLE:
			for (uint32_t i = index; i < indices.size() - 2; i += 3)
				DrawTriangle_WireFrame(vertices.at(indices.at(i)), vertices.at(indices.at(i + 1)), vertices.at(indices.at(i + 2)));
			break;
		case RENDER_MODE::WIRE_TRIANGLE_STRIP:
			for (uint32_t i = index; i < indices.size() - 2; ++i)
				DrawTriangle_WireFrame(vertices.at(indices.at(i)), vertices.at(indices.at(i + 1)), vertices.at(indices.at(i + 2)));
			break;
		default:
			break;
		}
	}

	void Rasterizer::DrawPoint(const Vertex &model_p)
	{
		CheckShader();
		//模型空间->世界空间->观察空间->裁剪空间->NDC空间->屏幕空间
		Vertex clip_p = m_Shader->VertexShader(model_p);
		Vector3f ndc_position = ToNDCSpace(clip_p.position);
		Vector2i32 screen_position = ToScreenSpace(ndc_position);

		if (0 <= screen_position.x && screen_position.x < m_BufferExtent.x && 0 <= screen_position.y && screen_position.y < m_BufferExtent.y)
		{
			Vertex screen_vertex;
			screen_vertex.position = Vector4f(Vector3f(screen_position.x, screen_position.y, ndc_position.z), clip_p.position.w);
			screen_vertex.texcoord = model_p.texcoord;
			screen_vertex.normal = model_p.normal;
			screen_vertex.tangent = model_p.tangent;
			screen_vertex.bitangent = model_p.bitangent;

			//根据指定的顶点绘制像素
			for (uint32_t i = screen_position.x - m_PointSize / 2; i <= screen_position.x + m_PointSize / 2; ++i)
				for (uint32_t j = screen_position.y - m_PointSize / 2; j <= screen_position.y + m_PointSize / 2; ++j)
					if (i >= 0 && i < m_BufferExtent.x && j >= 0 && j < m_BufferExtent.y)
						if (m_Framebuffer->GetDepthbuffer()->GetValue(i, j) > screen_vertex.position.z)
						{
							m_Framebuffer->GetDepthbuffer()->SetValue(i, j, screen_vertex.position.z);
							m_Framebuffer->GetColorbuffer()->SetValue(i, j, m_Shader->FragmentShader(screen_vertex, m_BufferExtent));
						}
		}
	}

	void Rasterizer::DrawLine(const Vertex &model_p0, const Vertex &model_p1)
	{
		CheckShader();
		//模型空间->世界空间->观察空间->裁剪空间->NDC空间->屏幕空间
		Vertex clip_p0 = m_Shader->VertexShader(model_p0);
		Vector3f ndc_position_p0 = ToNDCSpace(clip_p0.position);
		Vector2i32 screen_position_p0 = ToScreenSpace(ndc_position_p0);

		Vertex clip_p1 = m_Shader->VertexShader(model_p1);
		Vector3f ndc_position_p1 = ToNDCSpace(clip_p1.position);
		Vector2i32 screen_position_p1 = ToScreenSpace(ndc_position_p1);

		//Bresenham画线算法
		bool reverse = false;
		if (Math::Abs(static_cast<int>(screen_position_p1.x - screen_position_p0.x)) < Math::Abs(static_cast<int>(screen_position_p1.y - screen_position_p0.y)))
		{
			std::swap(screen_position_p0.x, screen_position_p0.y);
			std::swap(screen_position_p1.x, screen_position_p1.y);
			reverse = true;
		}
		if (screen_position_p0.x > screen_position_p1.x)
		{
			std::swap(screen_position_p0.x, screen_position_p1.x);
			std::swap(screen_position_p0.y, screen_position_p1.y);
		}

		int dx = static_cast<int>(screen_position_p1.x - screen_position_p0.x);
		int dy = static_cast<int>(screen_position_p1.y - screen_position_p0.y);

		int pk0 = std::abs(dy) * 2;
		int pk = 0;
		uint32_t y = screen_position_p0.y;

		float screen_pos_len = (screen_position_p1 - screen_position_p0).Length();
		Vector3f ndc_dir = ndc_position_p1 - ndc_position_p0;
		for (uint32_t x = screen_position_p0.x; x <= screen_position_p1.x; ++x)
		{
			if (0 <= x && x < m_BufferExtent.x && 0 <= y && y < m_BufferExtent.y)
			{
				////将直线映射回原来的区域
				if (reverse)
					std::swap(x, y);

				//对每个像素进行着色
				float factor = Vector2f(x - screen_position_p0.x, y - screen_position_p0.y).Length() / screen_pos_len;

				Vertex screen_vertex;
				screen_vertex.position = Vector3f(x, y, ndc_position_p0.z * (1 - factor) + ndc_position_p1.z * factor);
				screen_vertex.texcoord = model_p0.texcoord * (1 - factor) + model_p1.texcoord * factor;

				//进行深度测试
				if (m_Framebuffer->GetDepthbuffer()->GetValue(x, y) >= screen_vertex.position.z)
				{
					m_Framebuffer->GetDepthbuffer()->SetValue(x, y, screen_vertex.position.z);
					m_Framebuffer->GetColorbuffer()->SetValue(x, y, m_Shader->FragmentShader(screen_vertex, m_BufferExtent));
				}

				//继续下一步的计算
				if (reverse)
					std::swap(x, y);

				pk += pk0;
				if (pk > dx)
				{
					y += (screen_position_p1.y > screen_position_p0.y ? 1 : -1);
					pk -= dx * 2;
				}
			}
		}
	}

	void Rasterizer::DrawTriangle_WireFrame(const Vertex &model_p0, const Vertex &model_p1, const Vertex &model_p2)
	{
		CheckShader();
		DrawLine(model_p0, model_p1);
		DrawLine(model_p1, model_p2);
		DrawLine(model_p2, model_p0);
	}

	void Rasterizer::DrawTriangle_Solid(const Vertex &model_p0, const Vertex &model_p1, const Vertex &model_p2)
	{
		CheckShader();
		//模型空间->世界空间->观察空间->裁剪空间->NDC空间->屏幕空间
		Vertex clip_p0 = m_Shader->VertexShader(model_p0);
		Vector3f ndc_position_p0 = ToNDCSpace(clip_p0.position);
		Vector2i32 screen_position_p0 = ToScreenSpace(ndc_position_p0);

		Vertex clip_p1 = m_Shader->VertexShader(model_p1);
		Vector3f ndc_position_p1 = ToNDCSpace(clip_p1.position);
		Vector2i32 screen_position_p1 = ToScreenSpace(ndc_position_p1);

		Vertex clip_p2 = m_Shader->VertexShader(model_p2);
		Vector3f ndc_position_p2 = ToNDCSpace(clip_p2.position);
		Vector2i32 screen_position_p2 = ToScreenSpace(ndc_position_p2);

		//三角形光栅化部分

		//取三角形的AABB
		int32_t xMin = Math::Min(screen_position_p0.x, Math::Min(screen_position_p1.x, screen_position_p2.x));
		int32_t yMin = Math::Min(screen_position_p0.y, Math::Min(screen_position_p1.y, screen_position_p2.y));
		int32_t xMax = Math::Max(screen_position_p0.x, Math::Max(screen_position_p1.x, screen_position_p2.x));
		int32_t yMax = Math::Max(screen_position_p0.y, Math::Max(screen_position_p1.y, screen_position_p2.y));

		//将AABB范围截断为屏幕大小，在屏幕外的像素则丢弃
		xMin = Math::Clamp(xMin, 0, static_cast<int32_t>(m_BufferExtent.x - 1));
		yMin = Math::Clamp(yMin, 0, static_cast<int32_t>(m_BufferExtent.y - 1));
		xMax = Math::Clamp(xMax, 0, static_cast<int32_t>(m_BufferExtent.x - 1));
		yMax = Math::Clamp(yMax, 0, static_cast<int32_t>(m_BufferExtent.y - 1));

		//重心坐标判断AABB内的当前顶点是否在三角形内部
		for (uint32_t x = xMin; x <= xMax; ++x)
		{
			for (uint32_t y = yMin; y <= yMax; ++y)
			{
				Vector3f screen_bc_coord = BaryCenteric(screen_position_p0, screen_position_p1, screen_position_p2, Vector2i32(x, y));

				Vertex screen_vertex;
				screen_vertex.position = Vector4f(x, y, ndc_position_p0.z * screen_bc_coord.x + ndc_position_p1.z * screen_bc_coord.y + ndc_position_p2.z * screen_bc_coord.z, clip_p0.position.w * screen_bc_coord.x + clip_p1.position.w * screen_bc_coord.y + clip_p2.position.w * screen_bc_coord.z);
				screen_vertex.texcoord = model_p0.texcoord * screen_bc_coord.x + model_p1.texcoord * screen_bc_coord.y + model_p2.texcoord * screen_bc_coord.z;
				screen_vertex.normal = model_p0.normal * screen_bc_coord.x + model_p1.normal * screen_bc_coord.y + model_p2.normal * screen_bc_coord.z;
				screen_vertex.tangent = model_p0.tangent.x * screen_bc_coord.x + model_p1.tangent.x * screen_bc_coord.y + model_p2.tangent.x * screen_bc_coord.z;
				screen_vertex.bitangent = model_p0.bitangent.x * screen_bc_coord.x + model_p1.bitangent.x * screen_bc_coord.y + model_p2.bitangent.x * screen_bc_coord.z;
				screen_vertex.color=model_p0.color* screen_bc_coord.x + model_p1.color * screen_bc_coord.y + model_p2.color * screen_bc_coord.z;
				//如果当前片元在三角形内且通过深度测试则渲染到颜色缓存中，否则丢弃该片元(这里使用提前深度测试)
				if (screen_bc_coord.x >= 0.0f && screen_bc_coord.y >= 0.0f && screen_bc_coord.z >= 0.0f &&
					m_Framebuffer->GetDepthbuffer()->GetValue(x, y) >= screen_vertex.position.z && screen_vertex.position.z >= -1.0f)
				{
					m_Framebuffer->GetDepthbuffer()->SetValue(x, y, screen_vertex.position.z);
					m_Framebuffer->GetColorbuffer()->SetValue(x, y, m_Shader->FragmentShader(screen_vertex, m_BufferExtent));
				}
			}
		}
	}

	void Rasterizer::SetShader(const std::shared_ptr<Shader> &s)
	{
		m_Shader = s;
	}

	const std::shared_ptr<Shader> &Rasterizer::GetShader() const
	{
		return m_Shader;
	}

	Vector3f Rasterizer::BaryCenteric(const Vector2i32 &p0, const Vector2i32 &p1, const Vector2i32 &p2, const Vector2i32 &p)
	{
		Vector2i32 p1p0 = p1 - p0;
		Vector2i32 p2p0 = p2 - p0;
		Vector2i32 p0p = p0 - p;

		Vector3f factor = Vector3f::Cross(Vector3f(p2p0.x, p1p0.x, p0p.x), Vector3f(p2p0.y, p1p0.y, p0p.y));
		if (Math::Abs(factor.z) > 1e-2)
			return Vector3f(1.0f - (factor.x + factor.y) / factor.z, factor.y / factor.z, factor.x / factor.z);
		return Vector3f(-1.0f, -1.0f, -1.0f);
	}

	Vector3f Rasterizer::ToNDCSpace(const Vector4f &v)
	{
		return Vector4f::ToVector3(Vector4f::DivideByW(v));
	}

	Vector2i32 Rasterizer::ToScreenSpace(const Vector3f &v)
	{
		int32_t screen_x = Math::Round(m_BufferExtent.x * ((v.x + 1.0f) / 2.0f));
		int32_t screen_y = Math::Round(m_BufferExtent.y * ((v.y + 1.0f) / 2.0f));
		return Vector2i32(screen_x, screen_y);
	}

	void Rasterizer::CheckShader()
	{
		if(m_Shader != nullptr)
			return;
		ERROR_OUTPUT_LN("Current binding shader is null!");
		assert(m_Shader!=nullptr);
	}
}
