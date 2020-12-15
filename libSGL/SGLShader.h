#pragma once

#include "SGLMatrix4.h"
#include "SGLVertex.h"
#include "SGLVector4.h"


class SGLShader
{
public:
	SGLShader() {}
	virtual ~SGLShader() {}

	virtual SGLVertex VertexShader(const SGLVertex& modelVertex) = 0;
	virtual SGLVector4f FragmentShader(const SGLVertex& screenVertex = SGLVertex(), uint32_t bufferWidth = 0, uint32_t bufferHeight = 0) = 0;
protected:
	SGLVector3f Reflect(SGLVector3f i, SGLVector3f n);
	SGLVector3f Refract(SGLVector3f i, SGLVector3f n, float eta);

};
