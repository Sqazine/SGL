#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace SGL
{
	struct Vertex
	{
		SGL::Vector4f position;
		SGL::Vector2f texcoord;
		SGL::Vector3f normal;
		SGL::Vector3f tangent;
		SGL::Vector3f bitangent;
		SGL::Vector4f color;

		SGL::Vector3f posWS;
	};
}