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

#define CommitAndGet(type, name, valueType)                        \
	void Commit##type##Varying(std::string name, valueType value); \
	valueType Get##type##Varying(std::string name) const;

		CommitAndGet(Float, name, float);
		CommitAndGet(Double, name, double);
		CommitAndGet(Int64, name, int64_t);
		CommitAndGet(Uint64, name, uint64_t);
		CommitAndGet(Int32, name, int32_t);
		CommitAndGet(Uint32, name, uint32_t);
		CommitAndGet(Int16, name, int16_t);
		CommitAndGet(Uint16, name, uint16_t);
		CommitAndGet(Int8, name, int8_t);
		CommitAndGet(Uint8, name, uint8_t);
		CommitAndGet(Vector2f, name, Vector2f);
		CommitAndGet(Vector2d, name, Vector2d);
		CommitAndGet(Vector2i64, name, Vector2i64);
		CommitAndGet(Vector2u64, name, Vector2u64);
		CommitAndGet(Vector2i32, name, Vector2i32);
		CommitAndGet(Vector2u32, name, Vector2u32);
		CommitAndGet(Vector2i16, name, Vector2i16);
		CommitAndGet(Vector2u16, name, Vector2u16);
		CommitAndGet(Vector2i8, name, Vector2i8);
		CommitAndGet(Vector2u8, name, Vector2u8);
		CommitAndGet(Vector3f, name, Vector3f);
		CommitAndGet(Vector3d, name, Vector3d);
		CommitAndGet(Vector3i64, name, Vector3i64);
		CommitAndGet(Vector3u64, name, Vector3u64);
		CommitAndGet(Vector3i32, name, Vector3i32);
		CommitAndGet(Vector3u32, name, Vector3u32);
		CommitAndGet(Vector3i16, name, Vector3i16);
		CommitAndGet(Vector3u16, name, Vector3u16);
		CommitAndGet(Vector3i8, name, Vector3i8);
		CommitAndGet(Vector3u8, name, Vector3u8);
		CommitAndGet(Vector4f, name, Vector4f);
		CommitAndGet(Vector4d, name, Vector4d);
		CommitAndGet(Vector4i64, name, Vector4i64);
		CommitAndGet(Vector4u64, name, Vector4u64);
		CommitAndGet(Vector4i32, name, Vector4i32);
		CommitAndGet(Vector4u32, name, Vector4u32);
		CommitAndGet(Vector4i16, name, Vector4i16);
		CommitAndGet(Vector4u16, name, Vector4u16);
		CommitAndGet(Vector4i8, name, Vector4i8);
		CommitAndGet(Vector4u8, name, Vector4u8);
		CommitAndGet(Matrix2f, name, Matrix2f);
		CommitAndGet(Matrix3f, name, Matrix3f);
		CommitAndGet(Matrix4f, name, Matrix4f);

	private:
		std::unordered_map<std::string, uint32_t> m_FVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_DVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_I64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_U64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_I32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_U32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_I16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_U16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_I8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_U8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2fVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2dVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2i64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2u64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2i32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2u32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2i16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2u16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2i8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector2u8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3fVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3dVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3i64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3u64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3i32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3u32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3i16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3u16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3i8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector3u8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4fVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4dVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4i64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4u64VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4i32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4u32VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4i16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4u16VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4i8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Vector4u8VaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Matrix2fVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Matrix3fVaryingsIdx;
		std::unordered_map<std::string, uint32_t> m_Matrix4fVaryingsIdx;

	private:
		friend class Rasterizer;
		std::vector<float> m_FVaryings;
		std::vector<double> m_DVaryings;
		std::vector<int64_t> m_I64Varyings;
		std::vector<uint64_t> m_U64Varyings;
		std::vector<int32_t> m_I32Varyings;
		std::vector<uint32_t> m_U32Varyings;
		std::vector<int16_t> m_I16Varyings;
		std::vector<uint16_t> m_U16Varyings;
		std::vector<int8_t> m_I8Varyings;
		std::vector<uint8_t> m_U8Varyings;

		std::vector<Vector2f> m_Vector2fVaryings;
		std::vector<Vector2d> m_Vector2dVaryings;
		std::vector<Vector2i64> m_Vector2i64Varyings;
		std::vector<Vector2u64> m_Vector2u64Varyings;
		std::vector<Vector2i32> m_Vector2i32Varyings;
		std::vector<Vector2u32> m_Vector2u32Varyings;
		std::vector<Vector2i16> m_Vector2i16Varyings;
		std::vector<Vector2u16> m_Vector2u16Varyings;
		std::vector<Vector2i8> m_Vector2i8Varyings;
		std::vector<Vector2u8> m_Vector2u8Varyings;

		std::vector<Vector3f> m_Vector3fVaryings;
		std::vector<Vector3d> m_Vector3dVaryings;
		std::vector<Vector3i64> m_Vector3i64Varyings;
		std::vector<Vector3u64> m_Vector3u64Varyings;
		std::vector<Vector3i32> m_Vector3i32Varyings;
		std::vector<Vector3u32> m_Vector3u32Varyings;
		std::vector<Vector3i16> m_Vector3i16Varyings;
		std::vector<Vector3u16> m_Vector3u16Varyings;
		std::vector<Vector3i8> m_Vector3i8Varyings;
		std::vector<Vector3u8> m_Vector3u8Varyings;

		std::vector<Vector4f> m_Vector4fVaryings;
		std::vector<Vector4d> m_Vector4dVaryings;
		std::vector<Vector4i64> m_Vector4i64Varyings;
		std::vector<Vector4u64> m_Vector4u64Varyings;
		std::vector<Vector4i32> m_Vector4i32Varyings;
		std::vector<Vector4u32> m_Vector4u32Varyings;
		std::vector<Vector4i16> m_Vector4i16Varyings;
		std::vector<Vector4u16> m_Vector4u16Varyings;
		std::vector<Vector4i8> m_Vector4i8Varyings;
		std::vector<Vector4u8> m_Vector4u8Varyings;

		std::vector<Matrix2f> m_Matrix2fVaryings;
		std::vector<Matrix3f> m_Matrix3fVaryings;
		std::vector<Matrix4f> m_Matrix4fVaryings;
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
		virtual Vector4f FragmentShader(Varyings varyings) = 0;
	};
}