#pragma once
#include "SGL/SGL.h"
struct Vertex
{
	SGL::Vector4f position;
	SGL::Vector2f texcoord;
	SGL::Vector3f normal;
	SGL::Vector3f tangent;
	SGL::Vector3f bitangent;
	SGL::Vector4f color;
};