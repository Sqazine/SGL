#include "Shader.h"
#include "Vertex.h"

namespace SGL
{

	Vector3f ShaderProgram::Reflect(SGL::Vector3f i, SGL::Vector3f n)
	{
		return i - 2 * SGL::Vector3f::Dot(i, n) * n;
	}

}