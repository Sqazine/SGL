#pragma once
#include <cstdint>
#include <ostream>
#include <array>
#include "SGLMath.h"

template<typename T>
class SGLVector2;

template<typename T>
class SGLMatrix3;

template<typename T>
class SGLVector3
{
public:
	union {
		struct
		{
			T x, y, z;
		};
		struct
		{
			std::array<T, 3> values;
		};
	};
	SGLVector3();
	SGLVector3(const T& x, const T& y, const T& z);
	SGLVector3(const T& value);
	SGLVector3(const SGLVector2<T>& value, const T& zValue);

	inline SGLVector3<T>& operator+=(const T& value);
	inline SGLVector3<T>& operator+=(const SGLVector3<T>& right);
	inline SGLVector3<T>& operator-=(const T& value);
	inline SGLVector3<T>& operator-=(const SGLVector3<T>& right);
	inline SGLVector3<T>& operator*=(const T& value);
	inline SGLVector3<T>& operator*=(const SGLVector3<T>& right);
	inline SGLVector3<T>& operator/=(const T& value);
	inline SGLVector3<T>& operator=(const SGLVector3<T>& right);

	static T Dot(const SGLVector3<T>& left, const SGLVector3<T>& right);
	static SGLVector3<T> Cross(const SGLVector3<T>& left, const SGLVector3<T>& right);
	static SGLVector3<T> Normalize(const SGLVector3<T>& vec);
	static T IncludedAngle(const SGLVector3<T>& left, const SGLVector3<T>& right);
	static SGLVector2<T> ToSGLVector2(const SGLVector3<T>& right);
	T SquareLength() const;
	T Length() const;

	static const SGLVector3<T> ZERO;
	static const SGLVector3<T> UNIT_X;
	static const SGLVector3<T> UNIT_Y;
	static const SGLVector3<T> UNIT_Z;
};

typedef SGLVector3<float> SGLVector3f;
typedef SGLVector3<double> SGLVector3d;
typedef SGLVector3<int32_t> SGLVector3i32;
typedef SGLVector3<uint32_t> SGLVector3u32;
typedef SGLVector3<int16_t> SGLVector3i16;
typedef SGLVector3<uint16_t> SGLVector3u16;
typedef SGLVector3<int8_t> SGLVector3i8;
typedef SGLVector3<uint8_t> SGLVector3u8;


template<typename T>
const SGLVector3<T> SGLVector3<T>::ZERO=SGLVector3<T>();
template<typename T>
const SGLVector3<T> SGLVector3<T>::UNIT_X=SGLVector3<T>(static_cast<T>(1.0f),static_cast<T>(0.0f),static_cast<T>(0.0f));
template<typename T>
const SGLVector3<T> SGLVector3<T>::UNIT_Y=SGLVector3<T>(static_cast<T>(0.0f),static_cast<T>(1.0f),static_cast<T>(0.0f));
template<typename T>
const SGLVector3<T> SGLVector3<T>::UNIT_Z=SGLVector3<T>(static_cast<T>(0.0f),static_cast<T>(0.0f),static_cast<T>(1.0f));


template<typename T>
inline SGLVector3<T>::SGLVector3()
	:values({ static_cast<T>(0.0f),static_cast<T>(0.0f),static_cast<T>(0.0f) })
{
}
template<typename T>
inline SGLVector3<T>::SGLVector3(const T& x, const T& y, const T& z)
	: values({ x,y,z })
{
}
template<typename T>
inline SGLVector3<T>::SGLVector3(const T& value)
	: values({ value,value,value })
{
}
template<typename T>
inline SGLVector3<T>::SGLVector3(const SGLVector2<T>& value, const T& zValue)
	: values({ value.x,value.y,zValue })
{
}

template<typename T>
inline SGLVector3<T> operator+(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	return SGLVector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template<typename T>
inline SGLVector3<T> operator+(const SGLVector3<T>& left, const T& value)
{
	return SGLVector3<T>(left.x+value,left.y+value,left.z+value);
}

template<typename T>
inline SGLVector3<T> operator+(const T& value, const SGLVector3<T>& right)
{
	return right+value;
}

template<typename T>
inline SGLVector3<T> operator-(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	return SGLVector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template<typename T>
inline SGLVector3<T> operator-(const SGLVector3<T>& left, const T& value)
{
	return SGLVector3<T>(left.x - value, left.y - value, left.z-value);
}

template<typename T>
inline SGLVector3<T> operator-(const T& value, const SGLVector3<T>& right)
{
	return SGLVector3<T>(value-right.x,value-right.y,value-right.z);
}

template<typename T>
inline SGLVector3<T> operator-(const SGLVector3<T>& right)
{
	return SGLVector3<T>(-right.x, -right.y, -right.z);
}

template<typename T>
inline SGLVector3<T> operator*(const SGLVector3<T>& left, const T& value)
{
	return SGLVector3<T>(left.x * value, left.y * value, left.z * value);
}

template<typename T>
inline SGLVector3<T> operator*(const T& value, const SGLVector3<T>& right)
{
	return right * value;
}

template<typename T>
inline SGLVector3<T> operator*(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	return SGLVector3<T>(left.x * right.x, left.y * right.y, left.z * right.z);
}

template<typename T>
inline SGLVector3<T> operator/(const SGLVector3<T>& left, const T& value)
{
	if (value)
		return SGLVector3<T>(left.x / value, left.y / value, left.z / value);
	return left;
}

template<typename T>
inline SGLVector3<T> operator/(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	if (right.x && right.y && right.z)
		return SGLVector3<T>(left.x / right.x, left.y / right.y, left.z / right.z);
	return left;
}

template<typename T>
inline bool operator==(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const SGLVector3<T>& right)
{

	stream << "(" << right.x << "," << right.y << "," << right.z << ")";
	return stream;
}

template<typename T>
inline SGLVector3<T> operator*(const SGLMatrix3<T>& matrix, const SGLVector3<T>& vec)
{
	T x = matrix.elements[0] * vec.x + matrix.elements[3] * vec.y + matrix.elements[6] * vec.z;
	T y = matrix.elements[1] * vec.x + matrix.elements[4] * vec.y + matrix.elements[7] * vec.z;
	T z = matrix.elements[2] * vec.x + matrix.elements[5] * vec.y + matrix.elements[8] * vec.z;
	return SGLVector3<T>(x, y, z);
}

template<typename T>
inline SGLVector3<T> operator*(const SGLVector3<T>& vec, const SGLMatrix3<T>& matrix)
{
	T x=vec.x*matrix.elements[0]+vec.y*matrix.elements[1]+vec.z*matrix.elements[2];
	T y=vec.x*matrix.elements[3]+vec.y*matrix.elements[4]+vec.z*matrix.elements[5];
	T z=vec.x*matrix.elements[6]+vec.y*matrix.elements[7]+vec.z*matrix.elements[8];
	return SGLVector3<T>(x, y, z);
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator+=(const T& value)
{
	// TODO: 在此处插入 return 语句
	x += value;
	y += value;
	z += value;
	return *this;
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator+=(const SGLVector3<T>& right)
{
	// TODO: 在此处插入 return 语句
	x += right.x;
	y += right.y;
	z += right.z;
	return *this;
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator-=(const T& value)
{
	// TODO: 在此处插入 return 语句
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator-=(const SGLVector3<T>& right)
{
	// TODO: 在此处插入 return 语句
	x -= right.x;
	y -= right.y;
	z -= right.z;
	return *this;
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator*=(const T& value)
{
	// TODO: 在此处插入 return 语句
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator*=(const SGLVector3<T>& right)
{
	// TODO: 在此处插入 return 语句
	x *= right.x;
	y *= right.y;
	z *= right.z;
	return *this;
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator/=(const T& value)
{
	// TODO: 在此处插入 return 语句
	if (!SGLMath::IsNearZero(value))
	{
		x /= value;
		y /= value;
		z /= value;
	}
	return *this;
}

template<typename T>
inline SGLVector3<T>& SGLVector3<T>::operator=(const SGLVector3<T>& right)
{
	// TODO: 在此处插入 return 语句
	x = right.x;
	y = right.y;
	z = right.z;
	return *this;
}

template<typename T>
inline T SGLVector3<T>::Dot(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

template<typename T>
inline SGLVector3<T> SGLVector3<T>::Cross(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	return SGLVector3<T>(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
}

template<typename T>
inline SGLVector3<T> SGLVector3<T>::Normalize(const SGLVector3<T>& vec)
{
	T len = vec.Length();
	if (!SGLMath::IsNearZero(len))
	{
		return SGLVector3<T>(vec.x / len, vec.y / len, vec.z / len);
	}
	return vec;
}

template<typename T>
inline T SGLVector3<T>::IncludedAngle(const SGLVector3<T>& left, const SGLVector3<T>& right)
{
	return SGLMath::ArcCos(SGLVector3<T>::Dot(SGLVector3<T>::Normalize(left),SGLVector3<T>::Normalize(right)));
}

template<typename T>
inline SGLVector2<T> SGLVector3<T>::ToSGLVector2(const SGLVector3<T>& right)
{
	return SGLVector2<T>(right.x,right.y);
}
template<typename T>
inline T SGLVector3<T>::SquareLength() const
{
	return x*x+y*y+z*z;
}

template<typename T>
inline T SGLVector3<T>::Length() const
{
	return SGLMath::Sqrt(SquareLength());
}
