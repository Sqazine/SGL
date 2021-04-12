#pragma once

#include "Matrix4.h"
#include "Vertex.h"
#include "Vector4.h"
#include "Vertex.h"

#define uniform public:
namespace SGL
{
	class Shader
	{
	public:
		Shader() {}
		virtual ~Shader() {}

		virtual Vertex VertexShader(const Vertex &modelVertex) = 0;
		virtual Vector4f FragmentShader(const Vertex &screenVertex = Vertex(), const Vector2u32 &bufferExtent = Vector2u32::ZERO) = 0;

	protected:
		Vector3f Reflect(Vector3f i, Vector3f n);
		Vector3f Refract(Vector3f i, Vector3f n, float eta);
	};
}