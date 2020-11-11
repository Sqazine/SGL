#pragma once
#include <cstdint>
#include <ostream>
#include <array>
#include "SGLMath.h"

template<typename T>
class SGLVector3;

template<typename T>
class SGLMatrix2;

template<typename T>
class SGLVector2
{
public:
	union
	{
		struct
		{
			T x, y;
		};
		struct
		{
			std::array<T, 2> values;
		};
	};

	SGLVector2();
	SGLVector2(const T& x, const T& y);
	SGLVector2(const T& value);


	inline SGLVector2<T>& operator+=(const T& value);
	inline SGLVector2<T>& operator+=(const SGLVector2<T>& right);
	inline SGLVector2<T>& operator-=(const T& value);
	inline SGLVector2<T>& operator-=(const SGLVector2<T>& right);
	inline SGLVector2<T>& operator*=(const T& value);
	inline SGLVector2<T>& operator*=(const SGLVector2<T>& right);
	inline SGLVector2<T>& operator/=(const T& value);
	inline SGLVector2<T>& operator/=(const SGLVector2<T>& right);
	inline SGLVector2<T>& operator=(const SGLVector2<T>& right);

	inline T SquareLength() const;
	T Length() const;

	static T Dot(const SGLVector2<T>& left, const SGLVector2<T>& right);
	static SGLVector2<T> Normalize(const SGLVector2<T>& vec);
	static T IncludedAngle(const SGLVector2<T>& left, const SGLVector2<T>& right);
	static SGLVector3<T> ToVector3(const SGLVector2<T>& right, T zValue);

	static const SGLVector2<T> ZERO;
	static const SGLVector2<T> UNIT_X;
	static const SGLVector2<T> UNIT_Y;
};

typedef SGLVector2<float> SGLVector2f;
typedef SGLVector2<double> SGLVector2d;
typedef SGLVector2<int32_t> SGLVector2i32;
typedef SGLVector2<uint32_t> SGLVector2u32;
typedef SGLVector2<int16_t> SGLVector2i16;
typedef SGLVector2<uint16_t> SGLVector2u16;
typedef SGLVector2<int8_t> SGLVector2i8;
typedef SGLVector2<uint8_t> SGLVector2u8;
typedef SGLVector2<int64_t> SGLVector2i64;
typedef SGLVector2<uint64_t> SGLVector2u64;

template<typename T>
const SGLVector2<T> SGLVector2<T>::ZERO = SGLVector2<T>();

template<typename T>
const SGLVector2<T> SGLVector2<T>::UNIT_X = SGLVector2<T>(static_cast<T>(1.0f), static_cast<T>(0.0f));

template<typename T>
const SGLVector2<T> SGLVector2<T>::UNIT_Y = SGLVector2<T>(static_cast<T>(0.0f), static_cast<T>(1.0f));

template<typename T>
inline SGLVector2<T>::SGLVector2()
	:values({ static_cast<T>(0.0f),static_cast<T>(0.0f) })
{
}
template<typename T>
inline SGLVector2<T>::SGLVector2(const T& x, const T& y)
	: values({ x,y })
{
}
template<typename T>
inline SGLVector2<T>::SGLVector2(const T& value)
	: values({ value,value })
{
}

template<typename T>
inline SGLVector2<T> operator+(const SGLVector2<T>& left, const SGLVector2<T>& right)
{
	return SGLVector2<T>(left.x + right.x, left.y + right.y);
}
template<typename T>
inline SGLVector2<T> operator+(const SGLVector2<T>& left, const T& value)
{
	return SGLVector2<T>(left.x+value,left.y+value);
}
template<typename T>
inline SGLVector2<T> operator+(const T& value, const SGLVector2<T>& right)
{
	return right+value;
}
template<typename T>
inline SGLVector2<T> operator-(const SGLVector2<T>& left, const SGLVector2<T>& right)
{
	return SGLVector2<T>(left.x - right.x, left.y - right.y);
}
template<typename T>
inline SGLVector2<T> operator-(const SGLVector2<T>& left, const T& value)
{
	return SGLVector2<T>(left.x-value,left.y-value);
}
template<typename T>
inline SGLVector2<T> operator-(const T& value, const SGLVector2<T>& right)
{
	return SGLVector2<T>(value-right.x,value-right.y);
}
template<typename T>
inline SGLVector2<T> operator-(const SGLVector2<T>& right)
{
	return SGLVector2<T>(-right.x, -right.y);
}
template<typename T>
inline SGLVector2<T> operator*(const SGLVector2<T>& left, const T& value)
{
	return SGLVector2<T>(left.x * value, left.y * value);
}
template<typename T>
inline SGLVector2<T> operator*(const T& value, const SGLVector2<T>& right)
{
	return SGLVector2<T>(value * right.x, value * right.y);
}
template<typename T>
inline SGLVector2<T> operator*(const SGLVector2<T>& left, const SGLVector2<T>& right)
{
	return SGLVector2<T>(left.x * right.x, left.y * right.y);
}
template<typename T>
inline SGLVector2<T> operator/(const SGLVector2<T>& left, const T& value)
{
	if (value)
		return SGLVector2<T>(left.x / value, left.y / value);
	return left;
}
template<typename T>
inline SGLVector2<T> operator/(const T& value, const SGLVector2<T>& right)
{
	return right / value;
}
template<typename T>
inline SGLVector2<T> operator/(const SGLVector2<T>& left, const SGLVector2<T>& right)
{
	if (right.x && right.y)
		return SGLVector2<T>(left.x / right.x, left.y / right.y);
	return left;
}
template<typename T>
inline bool operator==(const SGLVector2<T>& left, const SGLVector2<T>& right)
{
	return (left.x - right.x) == static_cast<T>(0.0f) && (left.y - right.y) == static_cast<T>(0.0f);
}
template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const SGLVector2<T>& vec)
{

	stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
	return stream;
}

template<typename T>
inline SGLVector2<T> operator*(const SGLMatrix2<T>& matrix, const SGLVector2<T>& vec)
{
	SGLVector2<T> tmp;
	tmp.x = matrix.elements[0] * vec.x + matrix.elements[2] * vec.y;
	tmp.y = matrix.elements[1] * vec.x + matrix.elements[3] * vec.y;
	return tmp;

}

template<typename T>
inline SGLVector2<T> operator*(const SGLVector2<T>& vec, const SGLMatrix2<T>& matrix)
{
	SGLVector2<T> tmp;
	tmp.x = vec.x * matrix.elements[0] + vec.y * matrix.elements[1];
	tmp.y = vec.x * matrix.elements[2] + vec.y * matrix.elements[3];
	return tmp;
}

template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator+=(const T& value)
{

	x += value;
	y += value;
	return *this;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator+=(const SGLVector2<T>& right)
{

	x += right.x;
	y += right.y;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator-=(const T& value)
{

	x -= value;
	y -= value;
	return *this;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator-=(const SGLVector2<T>& right)
{

	x -= right.x;
	y -= right.y;
	return *this;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator*=(const T& value)
{

	x *= value;
	y *= value;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator*=(const SGLVector2<T>& right)
{

	x *= right.x;
	y *= right.y;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator/=(const T& value)
{

	if (value)
	{
		x /= value;
		y /= value;
	}
	return *this;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator/=(const SGLVector2<T>& right)
{

	if (!SGLMath::IsNearZero(right.x) && !SGLMath::IsNearZero(right.y))
	{
		x /= right.x;
		y /= right.y;
	}
	return *this;
}
template<typename T>
inline SGLVector2<T>& SGLVector2<T>::operator=(const SGLVector2<T>& right)
{
	x = right.x;
	y = right.y;
	return *this;
}
template<typename T>
inline T SGLVector2<T>::SquareLength() const
{
	return x * x + y * y;
}
template<typename T>
inline T SGLVector2<T>::Length() const
{
	return SGLMath::Sqrt(SquareLength());
}
template<typename T>
inline T SGLVector2<T>::Dot(const SGLVector2<T>& left, const SGLVector2<T>& right)
{
	return left.x * right.x + left.y * right.y;
}
template<typename T>
inline SGLVector2<T> SGLVector2<T>::Normalize(const SGLVector2<T>& vec)
{
	T len = vec.Length();
	if (!SGLMath::IsNearZero(len))
		return SGLVector2<T>(vec.x / len, vec.y / len);
	return SGLVector2<T>::ZERO;
}
template<typename T>
inline T SGLVector2<T>::IncludedAngle(const SGLVector2<T>& left, const SGLVector2<T>& right)
{
	return SGLMath::ArcCos(SGLVector2<T>::Dot(SGLVector2<T>::Normalize(left), SGLVector2<T>::Normalize(right)));
}
template<typename T>
inline SGLVector3<T> SGLVector2<T>::ToVector3(const SGLVector2<T>& right, T zValue)
{
	return SGLVector3<T>(right, zValue);
}