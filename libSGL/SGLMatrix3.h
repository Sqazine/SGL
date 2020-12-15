#pragma once
#include <xmmintrin.h>
#include "SGLMath.h"
template<typename T>
class SGLVector2;

template<typename T>
class SGLVector3;

template<typename T>
class SGLMatrix2;

template<typename T>
class SGLMatrix4;

template<typename T>
class SGLMatrix3
{
public:
	std::array<T, 9> elements;

	SGLMatrix3();
	SGLMatrix3(const T& value);
	SGLMatrix3(const SGLVector3<T>& diagonal);
	SGLMatrix3(const T& d00, const T& d11, const T& d22);
	SGLMatrix3(const T& e00, const T& e10, const T& e20, const T& e01, const T& e11, const T& e21, const T& e02, const T& e12, const T& e22);

	void Set(const SGLVector3<T>& diagonal);
	void Set(const T& d00, const T& d11, const T& d22);
	void Set(const T& e00, const T& e10, const T& e20, const T& e01, const T& e11, const T& e21, const T& e02, const T& e12, const T& e22);


	inline SGLMatrix3<T>& operator+=(const SGLMatrix3<T>& right);
	inline SGLMatrix3<T>& operator-=(const SGLMatrix3<T>& right);
	inline SGLMatrix3<T>& operator*=(const SGLMatrix3<T>& right);
	inline SGLMatrix3<T>& operator*=(const T& value);

	static SGLMatrix3<T> Rotate(const SGLVector3<T>& axis,const T&  radian);
	static SGLMatrix3<T> Scale(const T& factor);
	static SGLMatrix3<T> Scale(const SGLVector3<T>& factor);
	static SGLMatrix3<T> Transpose(const SGLMatrix3<T>& right);
	static SGLMatrix3<T> Inverse(const SGLMatrix3<T>& right);
	static T Determinant(const SGLMatrix3<T>& right);
	static SGLMatrix3<T> Adjoint(const SGLMatrix3<T>& right);
	static SGLMatrix4<T> ToMatrix4(const SGLMatrix3<T>& matrix);

	static const SGLMatrix3<T> IDENTITY;
};

typedef SGLMatrix3<float> SGLMatrix3f;
typedef SGLMatrix3<double> SGLMatrix3d;
typedef SGLMatrix3<int32_t> SGLMatrix3i32;
typedef SGLMatrix3<uint32_t> SGLMatrix3u32;
typedef SGLMatrix3<int16_t> SGLMatrix3i16;
typedef SGLMatrix3<uint16_t> SGLMatrix3u16;
typedef SGLMatrix3<int8_t> SGLMatrix3i8;
typedef SGLMatrix3<uint8_t> SGLMatrix3u8;

template<typename T>
const SGLMatrix3<T> SGLMatrix3<T>::IDENTITY = SGLMatrix3();

template<typename T>
inline SGLMatrix3<T>::SGLMatrix3()
	:elements({ static_cast<T>(1.0f),static_cast<T>(0.0f),static_cast<T>(0.0f),
		static_cast<T>(0.0f),static_cast<T>(1.0f),static_cast<T>(0.0f),
		static_cast<T>(0.0f),static_cast<T>(0.0f),static_cast<T>(1.0f)})
{
}

template<typename T>
inline SGLMatrix3<T>::SGLMatrix3(const T& value)
	:elements({ value,static_cast<T>(0.0f),static_cast<T>(0.0f),
		static_cast<T>(0.0f),value,static_cast<T>(0.0f),
		static_cast<T>(0.0f),static_cast<T>(0.0f),value })
{
}

template<typename T>
inline SGLMatrix3<T>::SGLMatrix3(const T& d00, const T& d11, const T& d22)
	: elements({ d00,static_cast<T>(0.0f),static_cast<T>(0.0f),
			static_cast<T>(0.0f),d11,static_cast<T>(0.0f),
			static_cast<T>(0.0f),static_cast<T>(0.0f),d22 })
{
}

template<typename T>
inline SGLMatrix3<T>::SGLMatrix3(const T& e00, const T& e10, const T& e20, const T& e01, const T& e11, const T& e21, const T& e02, const T& e12, const T& e22)
	:elements({ e00,e10,e20,e01,e11,e21,e02,e12,e22 })
{
}

template<typename T>
inline void SGLMatrix3<T>::Set(const SGLVector3<T>& diagonal)
{
	Set(diagonal.x, diagonal.y, diagonal.z);
}

template<typename T>
inline void SGLMatrix3<T>::Set(const T& d00, const T& d11, const T& d22)
{
	elements[0] = d00;
	elements[4] = d11;
	elements[8] = d22;
}

template<typename T>
inline void SGLMatrix3<T>::Set(const T& e00, const T& e10, const T& e20, const T& e01, const T& e11, const T& e21, const T& e02, const T& e12, const T& e22)
{
	elements[0] = e00;
	elements[1] = e10;
	elements[2] = e20;
	elements[3] = e01;
	elements[4] = e11;
	elements[5] = e21;
	elements[6] = e02;
	elements[7] = e12;
	elements[8] = e22;
}

template<typename T>
inline SGLMatrix3<T>::SGLMatrix3(const SGLVector3<T>& diagonal)
	: elements({ diagonal.x,static_cast<T>(0.0f),static_cast<T>(0.0f),
		   static_cast<T>(0.0f),diagonal.y,static_cast<T>(0.0f),
		   static_cast<T>(0.0f),static_cast<T>(0.0f),diagonal.z })
{
}

template<typename T>
inline SGLMatrix3<T>& SGLMatrix3<T>::operator+=(const SGLMatrix3<T>& right)
{
	// TODO: 在此处插入 return 语句
	for (uint8_t i = 0; i < 9; ++i)
		elements[i] += right.elements[i];
	return *this;
}

template<typename T>
inline SGLMatrix3<T>& SGLMatrix3<T>::operator-=(const SGLMatrix3<T>& right)
{
	// TODO: 在此处插入 return 语句
	for (uint8_t i = 0; i < 9; ++i)
		elements[i] -= right.elements[i];
	return *this;
}

template<typename T>
inline SGLMatrix3<T>& SGLMatrix3<T>::operator*=(const SGLMatrix3<T>& right)
{
	// TODO: 在此处插入 return 语句
	for (uint8_t i = 0; i < 9; ++i)
		elements[i] *= right.elements[i];
	return *this;
}

template<typename T>
inline SGLMatrix3<T>& SGLMatrix3<T>::operator*=(const T& value)
{
	// TODO: 在此处插入 return 语句
	for (uint8_t i = 0; i < 9; ++i)
		elements[i] *=value;
	return *this;
}


template<typename T>
inline SGLMatrix3<T> SGLMatrix3<T>::Rotate(const SGLVector3<T>& axis,const  T& radian)
{
	SGLMatrix3<T> tmp;
	float radian_cos = SGLMath::Cos(radian);
	float radian_sin = SGLMath::Sin(radian);
	float tmpNum = 1 - radian_cos;

	tmp.elements[0] = axis.x * axis.x * tmpNum + radian_cos;
	tmp.elements[1] = axis.y * axis.x * tmpNum + axis.z * radian_sin;
	tmp.elements[2] = axis.x * axis.z * tmpNum - axis.y * radian_sin;
	tmp.elements[3] = axis.y * axis.x * tmpNum - axis.z * radian_sin;
	tmp.elements[4] = axis.y * axis.y * tmpNum + radian_cos;
	tmp.elements[5] = axis.z * axis.y * tmpNum + axis.x * radian_sin;
	tmp.elements[6] = axis.x * axis.z * tmpNum + axis.y * radian_sin;
	tmp.elements[7] = axis.z * axis.y * tmpNum - axis.x * radian_sin;
	tmp.elements[8] = axis.z * axis.z * tmpNum + radian_cos;

	return tmp;
}

template<typename T>
inline SGLMatrix3<T> SGLMatrix3<T>::Scale(const T& factor)
{
	 SGLMatrix3<T> tmp;
	 tmp.Set(SGLVector3<T>(factor));
	 return tmp;
}

template<typename T>
inline SGLMatrix3<T> SGLMatrix3<T>::Scale(const SGLVector3<T>& factor)
{
	SGLMatrix3<T> tmp;
	tmp.Set(factor);
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> SGLMatrix3<T>::Transpose(const SGLMatrix3<T>& right)
{
	SGLMatrix3<T> tmp=right;
	tmp.elements[1] = right.elements[3];
	tmp.elements[2] = right.elements[6];
	tmp.elements[3] = right.elements[1];
	tmp.elements[5] = right.elements[7];
	tmp.elements[6] = right.elements[2];
	tmp.elements[7] = right.elements[5];
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> SGLMatrix3<T>::Inverse(const SGLMatrix3<T>& right)
{
	return SGLMatrix3<T>::Adjoint(right)/SGLMatrix3<T>::Determinant(right);
}

template<typename T>
inline T SGLMatrix3<T>::Determinant(const SGLMatrix3<T>& right)
{
	return right.elements[0] * right.elements[4] * right.elements[8] +
		right.elements[3] * right.elements[7] * right.elements[2] +
		right.elements[6] * right.elements[1] * right.elements[5] -
		right.elements[6] * right.elements[4] * right.elements[2] -
		right.elements[5] * right.elements[7] * right.elements[0] -
		right.elements[8] * right.elements[1] * right.elements[3];
}

template<typename T>
inline SGLMatrix3<T> SGLMatrix3<T>::Adjoint(const SGLMatrix3<T>& right)
{
	SGLMatrix3<T> tmp;
	tmp.elements[0] = SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[4],right.elements[5],right.elements[7],right.elements[8]));
	tmp.elements[1] =-SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[3],right.elements[5],right.elements[6],right.elements[8]));
	tmp.elements[2] = SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[3],right.elements[4],right.elements[6],right.elements[7]));

	tmp.elements[3] =-SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[1], right.elements[2], right.elements[7], right.elements[8]));
	tmp.elements[4] = SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[0], right.elements[2], right.elements[6], right.elements[8]));
	tmp.elements[5] =-SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[0], right.elements[1], right.elements[6], right.elements[7]));

	tmp.elements[6] = SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[1], right.elements[2], right.elements[4], right.elements[5]));
	tmp.elements[7] =-SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[0], right.elements[2], right.elements[3], right.elements[5]));
	tmp.elements[8] = SGLMatrix2<T>::Determinant(SGLMatrix2<T>(right.elements[0], right.elements[1], right.elements[3], right.elements[4]));
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix3<T>::ToMatrix4(const SGLMatrix3<T>& matrix)
{
	SGLMatrix4<T> tmp;
	tmp.col[0] = _mm_set_ps(static_cast<T>(0.0f), matrix.elements[2], matrix.elements[1], matrix.elements[0]);
	tmp.col[1] = _mm_set_ps(static_cast<T>(0.0f), matrix.elements[5], matrix.elements[4], matrix.elements[3]);
	tmp.col[2] = _mm_set_ps(static_cast<T>(0.0f), matrix.elements[8], matrix.elements[7], matrix.elements[6]);
	tmp.col[3] = _mm_set_ps(static_cast<T>(1.0f), static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(0.0f));
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> operator+(const SGLMatrix3<T>& left, const SGLMatrix3<T>& right)
{
	SGLMatrix3<T> tmp;
	for (uint8_t i = 0; i < 9; ++i)
		tmp.elements[i] = left.elements[i] + right.elements[i];
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> operator-(const SGLMatrix3<T>& left, const SGLMatrix3<T>& right)
{
	SGLMatrix3<T> tmp;
	for (uint8_t i = 0; i < 9; ++i)
		tmp.elements[i] = left.elements[i] - right.elements[i];
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> operator*(const SGLMatrix3<T>& left, const SGLMatrix3<T>& right)
{
	SGLMatrix3<T> tmp;
	for (uint32_t i = 0; i < 9; ++i)
		tmp.elements[i] = left.elements[i] + right.elements[i];
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> operator/(const SGLMatrix3<T>& left, const T& value)
{
	if (!SGLMath::IsNearZero(value))
	{
		SGLMatrix3<T> tmp;
		for (uint8_t i = 0; i < 9; ++i)
			tmp.elements[i] /= value;
		return tmp;
	}
	return left;
}

template<typename T>
inline SGLMatrix3<T> operator*(const SGLMatrix3<T>& left, const T& value)
{
	SGLMatrix3<T> tmp;
	for (uint8_t i = 0; i < 9; ++i)
		tmp.elements[i] *= value;
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> operator*(const T& value, const SGLMatrix3<T>& right)
{
	return right * value;
}

template<typename T>
inline bool operator==(const SGLMatrix3<T>& left, const SGLMatrix3<T>& right)
{
	for (uint8_t i = 0; i < 9; ++i)
		if (left.elements[i] != right.elements[i])
			return false;
	return true;
}
