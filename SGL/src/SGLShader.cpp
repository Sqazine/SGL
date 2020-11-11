#include "SGLShader.h"
#include "SGLVertex.h"
SGLVector3f SGLShader::Reflect(SGLVector3f i, SGLVector3f n)
{
	return i - 2 * SGLVector3f::Dot(i, n) * n;
}