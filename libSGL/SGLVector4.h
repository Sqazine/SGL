#pragma once
#include <array>
#include "SGLMath.h"
template<typename T>
class SGLVector3;

template<typename T>
class SGLMatrix4;

template<typename T>
class SGLVector4
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

	SGLVector4();
	SGLVector4(const T& value);
	SGLVector4(const T& x, const T& y, const T& z, const T& w = static_cast<T>(1.0f));
	SGLVector4(const SGLVector3<T>& vec, const T& w = 1.0f);

	inline SGLVector4<T>& operator+=(const T& value);
	inline SGLVector4<T>& operator+=(const SGLVector4<T>& right);
	inline SGLVector4<T>& operator-=(const T& value);
	inline SGLVector4<T>& operator-=(const SGLVector4<T>& right);
	inline SGLVector4<T>& operator/=(const T& value);
	inline SGLVector4<T>& operator=(const SGLVector4<T>& right);


	//用于除以w
	static SGLVector4<T> DivideByW(const SGLVector4<T>& vec);
	static SGLVector3<T> ToVector3(const SGLVector4<T>& vec);

	static const SGLVector4<T> ZERO;
};

typedef SGLVector4<float> SGLVector4f;
typedef SGLVector4<double> SGLVector4d;
typedef SGLVector4<int32_t> SGLVector4i32;
typedef SGLVector4<uint32_t> SGLVector4u32;
typedef SGLVector4<int16_t> SGLVector4i16;
typedef SGLVector4<uint16_t> SGLVector4u16;
typedef SGLVector4<int8_t> SGLVector4i8;
typedef SGLVector4<uint8_t> SGLVector4u8;

template<typename T>
inline SGLVector4<T>::SGLVector4()
	:values({ static_cast<T>(0.0f),static_cast<T>(0.0f),static_cast<T>(0.0f),static_cast<T>(1.0f) })
{
}

template<typename T>
inline SGLVector4<T>::SGLVector4(const T& value)
	: values({ value,value,value,value })
{
}

template<typename T>
inline SGLVector4<T>::SGLVector4(const T& x, const T& y, const T& z, const T& w)
	: values({ x,y,z,w })
{
}

template<typename T>
inline SGLVector4<T>::SGLVector4(const SGLVector3<T>& vec, const T& w)
	: values({ vec.x,vec.y,vec.z,w })
{
}

template<typename T>
inline SGLVector4<T> operator+(const SGLVector4<T>& left, const SGLVector4<T>& right)
{
	return SGLVector4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

template<typename T>
inline SGLVector4<T> operator+(const SGLVector4<T>& left, const T& value)
{
	return SGLVector4<T>(left.x+value,left.y+value,left.z+value,left.w+value);
}

template<typename T>
inline SGLVector4<T> operator+(const T& value, const SGLVector4<T>& right)
{
	return right+value;
}

template<typename T>
inline SGLVector4<T> operator-(const SGLVector4<T>& left, const SGLVector4<T>& right)
{
	return SGLVector4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

template<typename T>
inline SGLVector4<T> operator-(const SGLVector4<T>& left, const T& value)
{
	return SGLVector4<T>(left.x - value, left.y-value,left.z-value,left.w-value);
}

template<typename T>
inline SGLVector4<T> operator-(const T& value, const SGLVector4<T>& right)
{
	return SGLVector4<T>(value- right.x,value- right.y,value- right.z,value-right.w);
}

template<typename T>
inline SGLVector4<T> operator-(const SGLVector4<T>& right)
{
	return SGLVector4<T>(-right.x, -right.y, -right.z, -right.w);
}

template<typename T>
inline SGLVector4<T> operator*(const SGLVector4<T>& left, const SGLVector4<T>& right)
{
	return SGLVector4<T>(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

template<typename T>
inline SGLVector4<T> operator*(const T& value, const SGLVector4<T>& right)
{
	return SGLVector4<T>(value * right.x, value * right.y, value * right.z, value * right.w);
}

template<typename T>
inline SGLVector4<T> operator*(const SGLVector4<T>& left, T value)
{
	return value * left;
}

template<typename T>
inline SGLVector4<T> operator/(const SGLVector4<T>& left, T value)
{
	if (!SGLMath::IsNearZero(value))
		return SGLVector4<T>(left.x / value, left.y / value, left.z / value, left.w / value);
	return left;
}

template<typename T>
inline bool operator==(const SGLVector4<T>& left, const SGLVector4<T>& right)
{
	return !(SGLMath::IsNearZero(left.x - right.x) || SGLMath::IsNearZero(left.y - right.y) || SGLMath::IsNearZero(left.z - right.z) || SGLMath::IsNearZero(left.w - right.w));
}

template<typename T>
inline SGLVector4<T> operator*(const SGLMatrix4<T>& matrix, const SGLVector4<T>& vec)
{
	T x = matrix.elements[0] * vec.x + matrix.elements[4] * vec.y + matrix.elements[8] * vec.z + matrix.elements[12] * vec.w;
	T y = matrix.elements[1] * vec.x + matrix.elements[5] * vec.y + matrix.elements[9] * vec.z + matrix.elements[13] * vec.w;
	T z = matrix.elements[2] * vec.x + matrix.elements[6] * vec.y + matrix.elements[10] * vec.z + matrix.elements[14] * vec.w;
	T w = matrix.elements[3] * vec.x + matrix.elements[7] * vec.y + matrix.elements[11] * vec.z + matrix.elements[15] * vec.w;

	return SGLVector4<T>(x, y, z, w);
}

template<typename T>
inline SGLVector4<T> operator*(const SGLVector4<T>& vec, const SGLMatrix4<T>& matrix)
{
	T x = vec.x * matrix.elements[0] + vec.y * matrix.elements[1] + vec.z * matrix.elements[2] + vec.w * matrix.elements[3];
	T y = vec.x * matrix.elements[4] + vec.y * matrix.elements[5] + vec.z * matrix.elements[6] + vec.w * matrix.elements[7];
	T z = vec.x * matrix.elements[8] + vec.y * matrix.elements[9] + vec.z * matrix.elements[10] + vec.w * matrix.elements[11];
	T w = vec.x * matrix.elements[12] + vec.y * matrix.elements[13] + vec.z * matrix.elements[14] + vec.w * matrix.elements[15];
	return SGLVector4<T>(x, y, z, w);
}

template<typename T>
inline SGLVector4<T>& SGLVector4<T>::operator+=(const T& value)
{
	// TODO: 在此处插入 return 语句
	x += value;
	y += value;
	z += value;
	w += value;
	return *this;
}

template<typename T>
inline SGLVector4<T>& SGLVector4<T>::operator+=(const SGLVector4<T>& right)
{
	// TODO: 在此处插入 return 语句
	x += right.x;
	y += right.y;
	z += right.z;
	w += right.w;
	return *this;
}

template<typename T>
inline SGLVector4<T>& SGLVector4<T>::operator-=(const T& value)
{
	// TODO: 在此处插入 return 语句
	x -= value;
	y -= value;
	z -= value;
	w -= value;
	return *this;
}

template<typename T>
inline SGLVector4<T>& SGLVector4<T>::operator-=(const SGLVector4<T>& right)
{
	// TODO: 在此处插入 return 语句
	x -= right.x;
	y -= right.y;
	z -= right.z;
	w -= right.w;
	return *this;
}

template<typename T>
inline SGLVector4<T>& SGLVector4<T>::operator/=(const T& value)
{
	// TODO: 在此处插入 return 语句
	if (!SGLMath::IsNearZero(value))
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
	}
	return *this;
}

template<typename T>
inline SGLVector4<T>& SGLVector4<T>::operator=(const SGLVector4<T>& right)
{
	// TODO: 在此处插入 return 语句
	x = right.x;
	y = right.y;
	z = right.z;
	w = right.w;
	return *this;
}

template<typename T>
inline SGLVector4<T> SGLVector4<T>::DivideByW(const SGLVector4<T>& vec)
{
	return SGLVector4<T>(vec.x/vec.w,vec.y/vec.w,vec.z/vec.w,static_cast<T>(1.0f));
}

template<typename T>
inline SGLVector3<T> SGLVector4<T>::ToVector3(const SGLVector4<T>& vec)
{
	return SGLVector3<T>(vec.x,vec.y,vec.z);
}
