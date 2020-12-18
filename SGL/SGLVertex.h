#pragma once
#include "SGLVector2.h"
#include "SGLVector3.h"
#include "SGLVector4.h"

struct SGLVertex {
	SGLVector4f position;
	SGLVector2f texcoord;
	SGLVector3f normal;
	SGLVector3f tangent;
	SGLVector3f bitangent;
	SGLVector4f color;
};