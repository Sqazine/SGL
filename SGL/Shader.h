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
		Varyings();
		~Varyings();

		void CommitFloatVarying(std::string name, float value);
		float GetFloatVarying(std::string name) const;

		void CommitDoubleVarying(std::string name, double value);
		double GetDoubleVarying(std::string name) const;

		void CommitInt64Varying(std::string name, int64_t value);
		int64_t GetInt64Varying(std::string name) const;

		void CommitUint64Varying(std::string name, uint64_t value);
		uint64_t GetUint64Varying(std::string name) const;

		void CommitInt32Varying(std::string name, int32_t value);
		int32_t GetInt32Varying(std::string name) const;

		void CommitUint32Varying(std::string name, uint32_t value);
		uint32_t GetUint32Varying(std::string name) const;

		void CommitInt16Varying(std::string name, int16_t value);
		int16_t GetInt16Varying(std::string name) const;

		void CommitUint16Varying(std::string name, uint16_t value);
		uint16_t GetUint16Varying(std::string name) const;

		void CommitInt8Varying(std::string name, int8_t value);
		int8_t GetInt8Varying(std::string name) const;

		void CommitUint8Varying(std::string name, uint8_t value);
		uint8_t GetUint8Varying(std::string name) const;

		void CommitVector2fVarying(std::string name, const Vector2f &value);
		const Vector2f &GetVector2fVarying(std::string name) const;

		void CommitVector2dVarying(std::string name, const Vector2d &value);
		const Vector2d &GetVector2dVarying(std::string name) const;

		void CommitVector2i64Varying(std::string name, const Vector2i64 &value);
		const Vector2i64 &GetVector2i64Varying(std::string name) const;

		void CommitVector2u64Varying(std::string name, const Vector2u64 &value);
		const Vector2u64 &GetVector2u64Varying(std::string name) const;

		void CommitVector2i32Varying(std::string name, const Vector2i32 &value);
		const Vector2i32 &GetVector2i32Varying(std::string name) const;

		void CommitVector2u32Varying(std::string name, const Vector2u32 &value);
		const Vector2u32 &GetVector2u32Varying(std::string name) const;

		void CommitVector2i16Varying(std::string name, const Vector2i16 &value);
		const Vector2i16 &GetVector2i16Varying(std::string name) const;

		void CommitVector2u16Varying(std::string name, const Vector2u16 &value);
		const Vector2u16 &GetVector2u16Varying(std::string name) const;

		void CommitVector2i8Varying(std::string name, const Vector2i8 &value);
		const Vector2i8 &GetVector2i8Varying(std::string name) const;

		void CommitVector2u8Varying(std::string name, const Vector2u8 &value);
		const Vector2u8 &GetVector2u8Varying(std::string name) const;

		void CommitVector3fVarying(std::string name, const Vector3f &value);
		const Vector3f &GetVector3fVarying(std::string name) const;

		void CommitVector3dVarying(std::string name, const Vector3d &value);
		const Vector3d &GetVector3dVarying(std::string name) const;

		void CommitVector3i64Varying(std::string name, const Vector3i64 &value);
		const Vector3i64 &GetVector3i64Varying(std::string name) const;

		void CommitVector3u64Varying(std::string name, const Vector3u64 &value);
		const Vector3u64 &GetVector3u64Varying(std::string name) const;

		void CommitVector3i32Varying(std::string name, const Vector3i32 &value);
		const Vector3i32 &GetVector3i32Varying(std::string name) const;

		void CommitVector3u32Varying(std::string name, const Vector3u32 &value);
		const Vector3u32 &GetVector3u32Varying(std::string name) const;

		void CommitVector3i16Varying(std::string name, const Vector3i16 &value);
		const Vector3i16 &GetVector3i16Varying(std::string name) const;

		void CommitVector3u16Varying(std::string name, const Vector3u16 &value);
		const Vector3u16 &GetVector3u16Varying(std::string name) const;

		void CommitVector3i8Varying(std::string name, const Vector3i8 &value);
		const Vector3i8 &GetVector3i8Varying(std::string name) const;

		void CommitVector3u8Varying(std::string name, const Vector3u8 &value);
		const Vector3u8 &GetVector3u8Varying(std::string name) const;

		void CommitVector4fVarying(std::string name, const Vector4f &value);
		const Vector4f &GetVector4fVarying(std::string name) const;

		void CommitVector4dVarying(std::string name, const Vector4d &value);
		const Vector4d &GetVector4dVarying(std::string name) const;

		void CommitVector4i64Varying(std::string name, const Vector4i64 &value);
		const Vector4i64 &GetVector4i64Varying(std::string name) const;

		void CommitVector4u64Varying(std::string name, const Vector4u64 &value);
		const Vector4u64 &GetVector4u64Varying(std::string name) const;

		void CommitVector4i32Varying(std::string name, const Vector4i32 &value);
		const Vector4i32 &GetVector4i32Varying(std::string name) const;

		void CommitVector4u32Varying(std::string name, const Vector4u32 &value);
		const Vector4u32 &GetVector4u32Varying(std::string name) const;

		void CommitVector4i16Varying(std::string name, const Vector4i16 &value);
		const Vector4i16 &GetVector4i16Varying(std::string name) const;

		void CommitVector4u16Varying(std::string name, const Vector4u16 &value);
		const Vector4u16 &GetVector4u16Varying(std::string name) const;

		void CommitVector4i8Varying(std::string name, const Vector4i8 &value);
		const Vector4i8 &GetVector4i8Varying(std::string name) const;

		void CommitVector4u8Varying(std::string name, const Vector4u8 &value);
		const Vector4u8 &GetVector4u8Varying(std::string name) const;

		void CommitMatrix2fVarying(std::string name, const Matrix2f &value);
		const Matrix2f &GetMatrix2fVarying(std::string name) const;

		void CommitMatrix3fVarying(std::string name, const Matrix3f &value);
		const Matrix3f &GetMatrix3fVarying(std::string name) const;

		void CommitMatrix4fVarying(std::string name, const Matrix4f &value);
		const Matrix4f &GetMatrix4fVarying(std::string name) const;

	private:
		std::unordered_map<std::string, float> m_FloatVaryings;
		std::unordered_map<std::string, double> m_DoubleVaryings;
		std::unordered_map<std::string, int64_t> m_Int64Varyings;
		std::unordered_map<std::string, uint64_t> m_Uint64Varyings;
		std::unordered_map<std::string, int32_t> m_Int32Varyings;
		std::unordered_map<std::string, uint32_t> m_Uint32Varyings;
		std::unordered_map<std::string, int16_t> m_Int16Varyings;
		std::unordered_map<std::string, uint16_t> m_Uint16Varyings;
		std::unordered_map<std::string, int8_t> m_Int8Varyings;
		std::unordered_map<std::string, uint8_t> m_Uint8Varyings;
		std::unordered_map<std::string, SGL::Vector2f> m_Vector2fVaryings;
		std::unordered_map<std::string, SGL::Vector2d> m_Vector2dVaryings;
		std::unordered_map<std::string, SGL::Vector2i64> m_Vector2i64Varyings;
		std::unordered_map<std::string, SGL::Vector2u64> m_Vector2u64Varyings;
		std::unordered_map<std::string, SGL::Vector2i32> m_Vector2i32Varyings;
		std::unordered_map<std::string, SGL::Vector2u32> m_Vector2u32Varyings;
		std::unordered_map<std::string, SGL::Vector2i16> m_Vector2i16Varyings;
		std::unordered_map<std::string, SGL::Vector2u16> m_Vector2u16Varyings;
		std::unordered_map<std::string, SGL::Vector2i8> m_Vector2i8Varyings;
		std::unordered_map<std::string, SGL::Vector2u8> m_Vector2u8Varyings;
		std::unordered_map<std::string, SGL::Vector3f> m_Vector3fVaryings;
		std::unordered_map<std::string, SGL::Vector3d> m_Vector3dVaryings;
		std::unordered_map<std::string, SGL::Vector3i64> m_Vector3i64Varyings;
		std::unordered_map<std::string, SGL::Vector3u64> m_Vector3u64Varyings;
		std::unordered_map<std::string, SGL::Vector3i32> m_Vector3i32Varyings;
		std::unordered_map<std::string, SGL::Vector3u32> m_Vector3u32Varyings;
		std::unordered_map<std::string, SGL::Vector3i16> m_Vector3i16Varyings;
		std::unordered_map<std::string, SGL::Vector3u16> m_Vector3u16Varyings;
		std::unordered_map<std::string, SGL::Vector3i8> m_Vector3i8Varyings;
		std::unordered_map<std::string, SGL::Vector3u8> m_Vector3u8Varyings;
		std::unordered_map<std::string, SGL::Vector4f> m_Vector4fVaryings;
		std::unordered_map<std::string, SGL::Vector4d> m_Vector4dVaryings;
		std::unordered_map<std::string, SGL::Vector4i64> m_Vector4i64Varyings;
		std::unordered_map<std::string, SGL::Vector4u64> m_Vector4u64Varyings;
		std::unordered_map<std::string, SGL::Vector4i32> m_Vector4i32Varyings;
		std::unordered_map<std::string, SGL::Vector4u32> m_Vector4u32Varyings;
		std::unordered_map<std::string, SGL::Vector4i16> m_Vector4i16Varyings;
		std::unordered_map<std::string, SGL::Vector4u16> m_Vector4u16Varyings;
		std::unordered_map<std::string, SGL::Vector4i8> m_Vector4i8Varyings;
		std::unordered_map<std::string, SGL::Vector4u8> m_Vector4u8Varyings;
		std::unordered_map<std::string, SGL::Matrix2f> m_Matrix2fVaryings;
		std::unordered_map<std::string, SGL::Matrix3f> m_Matrix3fVaryings;
		std::unordered_map<std::string, SGL::Matrix4f> m_Matrix4fVaryings;
	};

	class ShaderProgram
	{
	protected:
#define uniform public:
		Vector3f Reflect(Vector3f i, Vector3f n);
		Vector3f Refract(Vector3f i, Vector3f n, float eta);
	};

	class GraphicsShaderProgram:public ShaderProgram
	{
	public:
		GraphicsShaderProgram() {}
		virtual ~GraphicsShaderProgram() {}

		virtual Vertex VertexShader(const Vertex &modelVertex) = 0;
		virtual Vector4f FragmentShader(const Vertex &screenVertex = Vertex(), const Vector2u32 &bufferExtent = Vector2u32::ZERO) = 0;
	};
}