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
	virtual SGLVector4f FragmentShader(const SGLVertex& screenVertex = SGLVertex(), const SGLVector2u32& bufferExtent=SGLVector2u32::ZERO) = 0;
protected:
	SGLVector3f Reflect(SGLVector3f i, SGLVector3f n);
	SGLVector3f Refract(SGLVector3f i, SGLVector3f n, float eta);

};
