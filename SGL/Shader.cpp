#include <cassert>
#include "Shader.h"
#include "Macros.h"
namespace SGL
{

#define CommitVarying(type, actualType, container)                           \
	void Varyings::Commit##type##Varying(std::string name, actualType value) \
	{                                                                        \
		container[name] = value;                                             \
	}

#define GetVarying(type, actualType, container)                                       \
	actualType Varyings::Get##type##Varying(std::string name) const                   \
	{                                                                                 \
		auto iter = container.find(name);                                             \
		if (iter == container.end())                                                  \
		{                                                                             \
			ERROR_OUTPUT_LN("varying '" + name + "' not exits in varying container"); \
			assert(iter != container.end());                                          \
		}                                                                             \
		return iter->second;                                                          \
	}

#define CommitAndGetVarying(type, actualType, container) \
	CommitVarying(type, actualType, container);          \
	GetVarying(type, actualType, container);

	CommitAndGetVarying(Float, float, m_FVaryings);
	CommitAndGetVarying(Double, double, m_DVaryings);
	CommitAndGetVarying(Int64, int64_t, m_I64Varyings);
	CommitAndGetVarying(Uint64, uint64_t, m_U64Varyings);
	CommitAndGetVarying(Int32, int32_t, m_I32Varyings);
	CommitAndGetVarying(Uint32, uint32_t, m_U32Varyings);
	CommitAndGetVarying(Int16, int16_t, m_I16Varyings);
	CommitAndGetVarying(Uint16, uint16_t, m_U16Varyings);
	CommitAndGetVarying(Int8, int8_t, m_I8Varyings);
	CommitAndGetVarying(Uint8, uint8_t, m_U8Varyings);

	CommitAndGetVarying(Vector2f, Vector2f, m_Vector2fVaryings);
	CommitAndGetVarying(Vector2d, Vector2d, m_Vector2dVaryings);
	CommitAndGetVarying(Vector2i64, Vector2i64, m_Vector2i64Varyings);
	CommitAndGetVarying(Vector2u64, Vector2u64, m_Vector2u64Varyings);
	CommitAndGetVarying(Vector2i32, Vector2i32, m_Vector2i32Varyings);
	CommitAndGetVarying(Vector2u32, Vector2u32, m_Vector2u32Varyings);
	CommitAndGetVarying(Vector2i16, Vector2i16, m_Vector2i16Varyings);
	CommitAndGetVarying(Vector2u16, Vector2u16, m_Vector2u16Varyings);
	CommitAndGetVarying(Vector2i8, Vector2i8, m_Vector2i8Varyings);
	CommitAndGetVarying(Vector2u8, Vector2u8, m_Vector2u8Varyings);

	CommitAndGetVarying(Vector3f, Vector3f, m_Vector3fVaryings);
	CommitAndGetVarying(Vector3d, Vector3d, m_Vector3dVaryings);
	CommitAndGetVarying(Vector3i64, Vector3i64, m_Vector3i64Varyings);
	CommitAndGetVarying(Vector3u64, Vector3u64, m_Vector3u64Varyings);
	CommitAndGetVarying(Vector3i32, Vector3i32, m_Vector3i32Varyings);
	CommitAndGetVarying(Vector3u32, Vector3u32, m_Vector3u32Varyings);
	CommitAndGetVarying(Vector3i16, Vector3i16, m_Vector3i16Varyings);
	CommitAndGetVarying(Vector3u16, Vector3u16, m_Vector3u16Varyings);
	CommitAndGetVarying(Vector3i8, Vector3i8, m_Vector3i8Varyings);
	CommitAndGetVarying(Vector3u8, Vector3u8, m_Vector3u8Varyings);

	CommitAndGetVarying(Vector4f, Vector4f, m_Vector4fVaryings);
	CommitAndGetVarying(Vector4d, Vector4d, m_Vector4dVaryings);
	CommitAndGetVarying(Vector4i64, Vector4i64, m_Vector4i64Varyings);
	CommitAndGetVarying(Vector4u64, Vector4u64, m_Vector4u64Varyings);
	CommitAndGetVarying(Vector4i32, Vector4i32, m_Vector4i32Varyings);
	CommitAndGetVarying(Vector4u32, Vector4u32, m_Vector4u32Varyings);
	CommitAndGetVarying(Vector4i16, Vector4i16, m_Vector4i16Varyings);
	CommitAndGetVarying(Vector4u16, Vector4u16, m_Vector4u16Varyings);
	CommitAndGetVarying(Vector4i8, Vector4i8, m_Vector4i8Varyings);
	CommitAndGetVarying(Vector4u8, Vector4u8, m_Vector4u8Varyings);

	CommitAndGetVarying(Matrix2f, Matrix2f, m_Matrix2fVaryings);
	CommitAndGetVarying(Matrix3f, Matrix3f, m_Matrix3fVaryings);
	CommitAndGetVarying(Matrix4f, Matrix4f, m_Matrix4fVaryings);

#undef CommitAndGetVarying
#undef GetVarying
#undef CommitVarying

	Vector3f ShaderProgram::Reflect(SGL::Vector3f i, SGL::Vector3f n)
	{
		return i - 2 * SGL::Vector3f::Dot(i, n) * n;
	}
}