#pragma once
#include <unordered_map>
#include "Matrix4.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Vertex.h"
#include "Vector4.h"
#include "Vertex.h"

namespace SGL
{
	class Varyings
	{
	public:
		Varyings() {}
		~Varyings() {}

#define CommitAndGet(type, valueType)                              \
	void Commit##type##Varying(std::string name, valueType value); \
	valueType Get##type##Varying(std::string name) const;

		CommitAndGet(Float, float);
		CommitAndGet(Double, double);
		CommitAndGet(Int64, int64_t);
		CommitAndGet(Uint64, uint64_t);
		CommitAndGet(Int32, int32_t);
		CommitAndGet(Uint32, uint32_t);
		CommitAndGet(Int16, int16_t);
		CommitAndGet(Uint16, uint16_t);
		CommitAndGet(Int8, int8_t);
		CommitAndGet(Uint8, uint8_t);
		CommitAndGet(Vector2f, Vector2f);
		CommitAndGet(Vector2d, Vector2d);
		CommitAndGet(Vector2i64, Vector2i64);
		CommitAndGet(Vector2u64, Vector2u64);
		CommitAndGet(Vector2i32, Vector2i32);
		CommitAndGet(Vector2u32, Vector2u32);
		CommitAndGet(Vector2i16, Vector2i16);
		CommitAndGet(Vector2u16, Vector2u16);
		CommitAndGet(Vector2i8, Vector2i8);
		CommitAndGet(Vector2u8, Vector2u8);
		CommitAndGet(Vector3f, Vector3f);
		CommitAndGet(Vector3d, Vector3d);
		CommitAndGet(Vector3i64, Vector3i64);
		CommitAndGet(Vector3u64, Vector3u64);
		CommitAndGet(Vector3i32, Vector3i32);
		CommitAndGet(Vector3u32, Vector3u32);
		CommitAndGet(Vector3i16, Vector3i16);
		CommitAndGet(Vector3u16, Vector3u16);
		CommitAndGet(Vector3i8, Vector3i8);
		CommitAndGet(Vector3u8, Vector3u8);
		CommitAndGet(Vector4f, Vector4f);
		CommitAndGet(Vector4d, Vector4d);
		CommitAndGet(Vector4i64, Vector4i64);
		CommitAndGet(Vector4u64, Vector4u64);
		CommitAndGet(Vector4i32, Vector4i32);
		CommitAndGet(Vector4u32, Vector4u32);
		CommitAndGet(Vector4i16, Vector4i16);
		CommitAndGet(Vector4u16, Vector4u16);
		CommitAndGet(Vector4i8, Vector4i8);
		CommitAndGet(Vector4u8, Vector4u8);
		CommitAndGet(Matrix2f, Matrix2f);
		CommitAndGet(Matrix3f, Matrix3f);
		CommitAndGet(Matrix4f, Matrix4f);

	private:
		friend class Rasterizer;
		std::unordered_map<std::string, float> m_FVaryings;
		std::unordered_map<std::string, double> m_DVaryings;
		std::unordered_map<std::string, int64_t> m_I64Varyings;
		std::unordered_map<std::string, uint64_t> m_U64Varyings;
		std::unordered_map<std::string, int32_t> m_I32Varyings;
		std::unordered_map<std::string, uint32_t> m_U32Varyings;
		std::unordered_map<std::string, int16_t> m_I16Varyings;
		std::unordered_map<std::string, uint16_t> m_U16Varyings;
		std::unordered_map<std::string, int8_t> m_I8Varyings;
		std::unordered_map<std::string, uint8_t> m_U8Varyings;

		std::unordered_map<std::string, Vector2f> m_Vector2fVaryings;
		std::unordered_map<std::string, Vector2d> m_Vector2dVaryings;
		std::unordered_map<std::string, Vector2i64> m_Vector2i64Varyings;
		std::unordered_map<std::string, Vector2u64> m_Vector2u64Varyings;
		std::unordered_map<std::string, Vector2i32> m_Vector2i32Varyings;
		std::unordered_map<std::string, Vector2u32> m_Vector2u32Varyings;
		std::unordered_map<std::string, Vector2i16> m_Vector2i16Varyings;
		std::unordered_map<std::string, Vector2u16> m_Vector2u16Varyings;
		std::unordered_map<std::string, Vector2i8> m_Vector2i8Varyings;
		std::unordered_map<std::string, Vector2u8> m_Vector2u8Varyings;

		std::unordered_map<std::string, Vector3f> m_Vector3fVaryings;
		std::unordered_map<std::string, Vector3d> m_Vector3dVaryings;
		std::unordered_map<std::string, Vector3i64> m_Vector3i64Varyings;
		std::unordered_map<std::string, Vector3u64> m_Vector3u64Varyings;
		std::unordered_map<std::string, Vector3i32> m_Vector3i32Varyings;
		std::unordered_map<std::string, Vector3u32> m_Vector3u32Varyings;
		std::unordered_map<std::string, Vector3i16> m_Vector3i16Varyings;
		std::unordered_map<std::string, Vector3u16> m_Vector3u16Varyings;
		std::unordered_map<std::string, Vector3i8> m_Vector3i8Varyings;
		std::unordered_map<std::string, Vector3u8> m_Vector3u8Varyings;

		std::unordered_map<std::string, Vector4f> m_Vector4fVaryings;
		std::unordered_map<std::string, Vector4d> m_Vector4dVaryings;
		std::unordered_map<std::string, Vector4i64> m_Vector4i64Varyings;
		std::unordered_map<std::string, Vector4u64> m_Vector4u64Varyings;
		std::unordered_map<std::string, Vector4i32> m_Vector4i32Varyings;
		std::unordered_map<std::string, Vector4u32> m_Vector4u32Varyings;
		std::unordered_map<std::string, Vector4i16> m_Vector4i16Varyings;
		std::unordered_map<std::string, Vector4u16> m_Vector4u16Varyings;
		std::unordered_map<std::string, Vector4i8> m_Vector4i8Varyings;
		std::unordered_map<std::string, Vector4u8> m_Vector4u8Varyings;

		std::unordered_map<std::string, Matrix2f> m_Matrix2fVaryings;
		std::unordered_map<std::string, Matrix3f> m_Matrix3fVaryings;
		std::unordered_map<std::string, Matrix4f> m_Matrix4fVaryings;
	};

	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() {}

	protected:
#define uniform public:
		Vector3f Reflect(Vector3f i, Vector3f n);
		Vector3f Refract(Vector3f i, Vector3f n, float eta);
	};

	class GraphicsShaderProgram : public ShaderProgram
	{
	public:
		GraphicsShaderProgram() {}
		virtual ~GraphicsShaderProgram() {}

		virtual Vector4f VertexShader(const Vertex &vertex, Varyings &varyings) = 0;
		virtual Vector4f FragmentShader(const Varyings &varyings) = 0;
	};
}