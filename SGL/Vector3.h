#pragma once
#include <cstdint>
#include <ostream>
#include <array>
#include "Math.h"

namespace SGL
{

	template <typename T>
	class Vector2;

	template <typename T>
	class Matrix3;

	template <typename T>
	class Vector3
	{
	public:
		union
		{
			struct
			{
				T x, y, z;
			};
			struct
			{
				std::array<T, 3> values;
			};
		};
		Vector3();
		Vector3(const T &x, const T &y, const T &z);
		Vector3(const T &value);
		Vector3(const Vector2<T> &value, const T &zValue);

		template <typename T2>
		inline Vector3<T> &operator+=(const T2 &value);
		template <typename T2>
		inline Vector3<T> &operator+=(const Vector3<T2> &right);
		template <typename T2>
		inline Vector3<T> &operator-=(const T2 &value);
		template <typename T2>
		inline Vector3<T> &operator-=(const Vector3<T2> &right);
		template <typename T2>
		inline Vector3<T> &operator*=(const T2 &value);
		template <typename T2>
		inline Vector3<T> &operator*=(const Vector3<T2> &right);
		template <typename T2>
		inline Vector3<T> &operator/=(const T2 &value);
		template <typename T2>
		inline Vector3<T> &operator/=(const Vector3<T2> &right);
		template <typename T2>
		inline Vector3<T> &operator=(const Vector3<T2> &right);

		static T Dot(const Vector3<T> &left, const Vector3<T> &right);
		static Vector3<T> Cross(const Vector3<T> &left, const Vector3<T> &right);
		static Vector3<T> Normalize(const Vector3<T> &vec);
		static T IncludedAngle(const Vector3<T> &left, const Vector3<T> &right);
		static Vector2<T> ToVector2(const Vector3<T> &right);
		T SquareLength() const;
		T Length() const;

		static const Vector3<T> ZERO;
		static const Vector3<T> UNIT_X;
		static const Vector3<T> UNIT_Y;
		static const Vector3<T> UNIT_Z;
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<int64_t> Vector3i64;
	typedef Vector3<uint64_t> Vector3u64;
	typedef Vector3<int32_t> Vector3i32;
	typedef Vector3<uint32_t> Vector3u32;
	typedef Vector3<int16_t> Vector3i16;
	typedef Vector3<uint16_t> Vector3u16;
	typedef Vector3<int8_t> Vector3i8;
	typedef Vector3<uint8_t> Vector3u8;

	template <typename T>
	const Vector3<T> Vector3<T>::ZERO = Vector3<T>();
	template <typename T>
	const Vector3<T> Vector3<T>::UNIT_X = Vector3<T>(static_cast<T>(1.0f), static_cast<T>(0.0f), static_cast<T>(0.0f));
	template <typename T>
	const Vector3<T> Vector3<T>::UNIT_Y = Vector3<T>(static_cast<T>(0.0f), static_cast<T>(1.0f), static_cast<T>(0.0f));
	template <typename T>
	const Vector3<T> Vector3<T>::UNIT_Z = Vector3<T>(static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(1.0f));

	template <typename T>
	inline Vector3<T>::Vector3()
		: values({static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(0.0f)})
	{
	}
	template <typename T>
	inline Vector3<T>::Vector3(const T &x, const T &y, const T &z)
		: values({x, y, z})
	{
	}
	template <typename T>
	inline Vector3<T>::Vector3(const T &value)
		: values({value, value, value})
	{
	}
	template <typename T>
	inline Vector3<T>::Vector3(const Vector2<T> &value, const T &zValue)
		: values({value.x, value.y, zValue})
	{
	}

	template <typename T, typename T2>
	inline Vector3<T> operator+(const Vector3<T> &left, const Vector3<T2> &right)
	{
		return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator+(const Vector3<T> &left, const T2 &value)
	{
		return Vector3<T>(left.x + value, left.y + value, left.z + value);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator+(const T &value, const Vector3<T2> &right)
	{
		return right + value;
	}

	template <typename T, typename T2>
	inline Vector3<T> operator-(const Vector3<T> &left, const Vector3<T2> &right)
	{
		return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator-(const Vector3<T> &left, const T2 &value)
	{
		return Vector3<T>(left.x - value, left.y - value, left.z - value);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator-(const T &value, const Vector3<T2> &right)
	{
		return Vector3<T>(value - right.x, value - right.y, value - right.z);
	}

	template <typename T>
	inline Vector3<T> operator-(const Vector3<T> &right)
	{
		return Vector3<T>(-right.x, -right.y, -right.z);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator*(const Vector3<T> &left, const T2 &value)
	{
		return Vector3<T>(left.x * value, left.y * value, left.z * value);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator*(const T2 &value, const Vector3<T> &right)
	{
		return right * value;
	}

	template <typename T, typename T2>
	inline Vector3<T> operator*(const Vector3<T> &left, const Vector3<T2> &right)
	{
		return Vector3<T>(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator/(const Vector3<T> &left, const T2 &value)
	{
		if (value)
			return Vector3<T>(left.x / value, left.y / value, left.z / value);
		return left;
	}

	template <typename T, typename T2>
	inline Vector3<T> operator/(const Vector3<T> &left, const Vector3<T2> &right)
	{
		if (right.x && right.y && right.z)
			return Vector3<T>(left.x / right.x, left.y / right.y, left.z / right.z);
		return left;
	}

	template <typename T, typename T2>
	inline bool operator==(const Vector3<T> &left, const Vector3<T2> &right)
	{
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	template <typename T>
	inline std::ostream &operator<<(std::ostream &stream, const Vector3<T> &right)
	{

		stream << "(" << right.x << "," << right.y << "," << right.z << ")";
		return stream;
	}

	template <typename T, typename T2>
	inline Vector3<T> operator*(const Matrix3<T> &matrix, const Vector3<T2> &vec)
	{
		T x = matrix.elements[0] * vec.x + matrix.elements[3] * vec.y + matrix.elements[6] * vec.z;
		T y = matrix.elements[1] * vec.x + matrix.elements[4] * vec.y + matrix.elements[7] * vec.z;
		T z = matrix.elements[2] * vec.x + matrix.elements[5] * vec.y + matrix.elements[8] * vec.z;
		return Vector3<T>(x, y, z);
	}

	template <typename T, typename T2>
	inline Vector3<T> operator*(const Vector3<T> &vec, const Matrix3<T2> &matrix)
	{
		T x = vec.x * matrix.elements[0] + vec.y * matrix.elements[1] + vec.z * matrix.elements[2];
		T y = vec.x * matrix.elements[3] + vec.y * matrix.elements[4] + vec.z * matrix.elements[5];
		T z = vec.x * matrix.elements[6] + vec.y * matrix.elements[7] + vec.z * matrix.elements[8];
		return Vector3<T>(x, y, z);
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator+=(const T2 &value)
	{

		x += value;
		y += value;
		z += value;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator+=(const Vector3<T2> &right)
	{

		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator-=(const T2 &value)
	{

		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator-=(const Vector3<T2> &right)
	{

		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator*=(const T2 &value)
	{

		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator*=(const Vector3<T2> &right)
	{

		x *= right.x;
		y *= right.y;
		z *= right.z;
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator/=(const T2 &value)
	{

		if (!Math::IsNearZero(value))
		{
			x /= value;
			y /= value;
			z /= value;
		}
		return *this;
	}

	template <typename T>
	template <typename T2>
	inline Vector3<T> &Vector3<T>::operator=(const Vector3<T2> &right)
	{

		x = right.x;
		y = right.y;
		z = right.z;
		return *this;
	}

	template <typename T>
	inline T Vector3<T>::Dot(const Vector3<T> &left, const Vector3<T> &right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	template <typename T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T> &left, const Vector3<T> &right)
	{
		return Vector3<T>(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
	}

	template <typename T>
	inline Vector3<T> Vector3<T>::Normalize(const Vector3<T> &vec)
	{
		T len = vec.Length();
		if (!Math::IsNearZero(len))
		{
			return Vector3<T>(vec.x / len, vec.y / len, vec.z / len);
		}
		return vec;
	}

	template <typename T>
	inline T Vector3<T>::IncludedAngle(const Vector3<T> &left, const Vector3<T> &right)
	{
		return Math::ArcCos(Vector3<T>::Dot(Vector3<T>::Normalize(left), Vector3<T>::Normalize(right)));
	}

	template <typename T>
	inline Vector2<T> Vector3<T>::ToVector2(const Vector3<T> &right)
	{
		return Vector2<T>(right.x, right.y);
	}
	template <typename T>
	inline T Vector3<T>::SquareLength() const
	{
		return x * x + y * y + z * z;
	}

	template <typename T>
	inline T Vector3<T>::Length() const
	{
		return Math::Sqrt(SquareLength());
	}
}