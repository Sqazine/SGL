#pragma once
#include <array>
#include "Math.h"

namespace SGL
{

	template <typename T>
	class Vector3;

	template <typename T>
	class Matrix4;

	template <typename T>
	class Vector4
	{
	public:
		union
		{
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				std::array<T, 4> values;
			};
		};

		Vector4();
		Vector4(const T &value);
		Vector4(const T &x, const T &y, const T &z, const T &w = static_cast<T>(1.0f));
		Vector4(const Vector3<T> &vec, const T &w = 1.0f);

		template <typename T2>
		 Vector4<T> &operator+=(const T2 &value);
		template <typename T2>
		 Vector4<T> &operator+=(const Vector4<T2> &right);
		template <typename T2>
		 Vector4<T> &operator-=(const T2 &value);
		template <typename T2>
		 Vector4<T> &operator-=(const Vector4<T2> &right);
		template <typename T2>
		 Vector4<T> &operator*=(const T2 &value);
		template <typename T2>
		 Vector4<T> &operator*=(const Vector4<T2> &right);
		template <typename T2>
		 Vector4<T> &operator/=(const T2 &value);
		template <typename T2>
		 Vector4<T> &operator/=(const Vector4<T2> &right);
		template <typename T2>
		 Vector4<T> &operator=(const Vector4<T2> &right);

		static Vector4<T> DivideByW(const Vector4<T> &vec);
		static Vector3<T> ToVector3(const Vector4<T> &vec);

		static const Vector4<T> ZERO;
	};

	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
	typedef Vector4<int64_t> Vector4i64;
	typedef Vector4<uint64_t> Vector4u64;
	typedef Vector4<int32_t> Vector4i32;
	typedef Vector4<uint32_t> Vector4u32;
	typedef Vector4<int16_t> Vector4i16;
	typedef Vector4<uint16_t> Vector4u16;
	typedef Vector4<int8_t> Vector4i8;
	typedef Vector4<uint8_t> Vector4u8;

	template <typename T>
	const Vector4<T> Vector4<T>::ZERO = Vector4<T>();

	template <typename T>
	inline Vector4<T>::Vector4()
		: values({static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(1.0f)})
	{
	}

	template <typename T>
	inline Vector4<T>::Vector4(const T &value)
		: values({value, value, value, value})
	{
	}

	template <typename T>
	inline Vector4<T>::Vector4(const T &x, const T &y, const T &z, const T &w)
		: values({x, y, z, w})
	{
	}

	template <typename T>
	inline Vector4<T>::Vector4(const Vector3<T> &vec, const T &w)
		: values({vec.x, vec.y, vec.z, w})
	{
	}

	template <typename T,typename T2>
	inline Vector4<T> operator+(const Vector4<T> &left, const Vector4<T2> &right)
	{
		return Vector4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator+(const Vector4<T> &left, const T2 &value)
	{
		return Vector4<T>(left.x + value, left.y + value, left.z + value, left.w + value);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator+(const T &value, const Vector4<T2> &right)
	{
		return right + value;
	}

	template <typename T,typename T2>
	inline Vector4<T> operator-(const Vector4<T> &left, const Vector4<T2> &right)
	{
		return Vector4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator-(const Vector4<T> &left, const T2 &value)
	{
		return Vector4<T>(left.x - value, left.y - value, left.z - value, left.w - value);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator-(const T &value, const Vector4<T2> &right)
	{
		return Vector4<T>(value - right.x, value - right.y, value - right.z, value - right.w);
	}

	template <typename T>
	inline Vector4<T> operator-(const Vector4<T> &right)
	{
		return Vector4<T>(-right.x, -right.y, -right.z, -right.w);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator*(const Vector4<T> &left, const Vector4<T2> &right)
	{
		return Vector4<T>(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator*(const T2 &value, const Vector4<T> &right)
	{
		return Vector4<T>(value * right.x, value * right.y, value * right.z, value * right.w);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator*(const Vector4<T> &left, T2 value)
	{
		return value * left;
	}

	template <typename T,typename T2>
	inline Vector4<T> operator/(const Vector4<T> &left, T2 value)
	{
		if (!Math::IsNearZero(value))
			return Vector4<T>(left.x / value, left.y / value, left.z / value, left.w / value);
		return left;
	}

	template <typename T,typename T2>
	inline Vector4<T> operator/(const Vector4<T> &left, const Vector4<T2>& value)
	{
		
			return Vector4<T>(left.x / value.x, left.y / value.y, left.z / value.z, left.w / value.w);
	}

	template <typename T,typename T2>
	inline bool operator==(const Vector4<T> &left, const Vector4<T2> &right)
	{
		return !(Math::IsNearZero(left.x - right.x) || Math::IsNearZero(left.y - right.y) || Math::IsNearZero(left.z - right.z) || Math::IsNearZero(left.w - right.w));
	}

	template <typename T,typename T2>
	inline Vector4<T> operator*(const Matrix4<T> &matrix, const Vector4<T2> &vec)
	{
		__m128 v = _mm_set_ps(static_cast<T>(vec.w), static_cast<T>(vec.z), static_cast<T>(vec.y), static_cast<T>(vec.x));
		__m128 r0 = _mm_mul_ps(matrix.col[0], _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0)));
		__m128 r1 = _mm_mul_ps(matrix.col[1], _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)));
		__m128 r2 = _mm_mul_ps(matrix.col[2], _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)));
		__m128 r3 = _mm_mul_ps(matrix.col[3], _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3)));
		__m128 result = _mm_add_ps(_mm_add_ps(r0, r1), _mm_add_ps(r2, r3));

		alignas(16) T tmp[4];
		_mm_store_ps(tmp, result);
		return Vector4<T>(tmp[0], tmp[1], tmp[2], tmp[3]);
	}

	template <typename T,typename T2>
	inline Vector4<T> operator*(const Vector4<T> &vec, const Matrix4<T2> &matrix)
	{
		__m128 v = _mm_set_ps(static_cast<T>(vec.w), static_cast<T>(vec.z), static_cast<T>(vec.y), static_cast<T>(vec.x));

		__m128 p0 = _mm_mul_ps(v, matrix.col[0]);
		__m128 p1 = _mm_mul_ps(v, matrix.col[1]);
		__m128 p2 = _mm_mul_ps(v, matrix.col[2]);
		__m128 p3 = _mm_mul_ps(v, matrix.col[3]);

		_MM_TRANSPOSE4_PS(p0, p1, p2, p3);
		__m128 result = _mm_add_ps(_mm_add_ps(p0, p1), _mm_add_ps(p2, p3));

		alignas(16) T tmp[4];
		_mm_store_ps(tmp, result);
		return Vector4<T>(tmp[0], tmp[1], tmp[2], tmp[3]);
	}

	template <typename T>
	template <typename T2>
	inline Vector4<T> &Vector4<T>::operator+=(const T2 &value)
	{

		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector4<T> &Vector4<T>::operator+=(const Vector4<T2> &right)
	{

		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector4<T> &Vector4<T>::operator-=(const T2 &value)
	{

		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector4<T> &Vector4<T>::operator-=(const Vector4<T2> &right)
	{

		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector4<T> &Vector4<T>::operator/=(const T2 &value)
	{

		if (!Math::IsNearZero(value))
		{
			x /= value;
			y /= value;
			z /= value;
			w /= value;
		}
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector4<T> &Vector4<T>::operator=(const Vector4<T2> &right)
	{

		x = right.x;
		y = right.y;
		z = right.z;
		w = right.w;
		return *this;
	}

	template <typename T>
	inline Vector4<T> Vector4<T>::DivideByW(const Vector4<T> &vec)
	{
		return Vector4<T>(vec.x / vec.w, vec.y / vec.w, vec.z / vec.w, static_cast<T>(1.0f));
	}

	template <typename T>
	inline Vector3<T> Vector4<T>::ToVector3(const Vector4<T> &vec)
	{
		return Vector3<T>(vec.x, vec.y, vec.z);
	}
}