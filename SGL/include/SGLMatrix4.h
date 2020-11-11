#pragma once
#include <xmmintrin.h>
#include <cstdint>
#include <array>
#include "SGLMath.h"
#include <iostream>
template<typename T>
class SGLVector3;

template<typename T>
class SGLVector4;

template<typename T>
class SGLMatrix3;

template<typename T>
class SGLMatrix4
{
public:
	union
	{
		struct
		{
			std::array<__m128, 4> col;
		};
		struct
		{
			std::array<T, 16> elements;
		};
	};

	SGLMatrix4();
	SGLMatrix4(const T& value);
	SGLMatrix4(const SGLVector4<T>& diagonal);
	SGLMatrix4(const T& d00, const T& d11, const T& d22, const T& d33);
	SGLMatrix4(const T& e00, const T& e10, const T& e20, const T& e30,
		const T& e01, const T& e11, const T& e21, const T& e31,
		const T& e02, const T& e12, const T& e22, const T& e32,
		const T& e03, const T& e13, const T& e23, const T& e33);

	void Set(const SGLVector4<T>& diagonal);
	void Set(const T& d00, const T& d11, const T& d22, const T& d33);
	void Set(const T& e00, const T& e10, const T& e20, const T& e30,
		const T& e01, const T& e11, const T& e21, const T& e31,
		const T& e02, const T& e12, const T& e22, const T& e32,
		const T& e03, const T& e13, const T& e23, const T& e33);


	inline SGLMatrix4<T>& operator+=(const SGLMatrix4<T>& right);
	inline SGLMatrix4<T>& operator-=(const SGLMatrix4<T>& right);
	inline SGLMatrix4<T>& operator*=(const SGLMatrix4<T>& right);
	inline SGLMatrix4<T>& operator*=(const T& value);

	static SGLMatrix4<T> Translate(const SGLVector3<T>& position);
	static SGLMatrix4<T> Rotate(const SGLVector3<T>& axis, const T& radian);
	static SGLMatrix4<T> Scale(const T& factor);
	static SGLMatrix4<T> Scale(const SGLVector3<T>& factor);
	static SGLMatrix4<T> Transpose(const SGLMatrix4<T>& right);
	static SGLMatrix4<T> Inverse(const SGLMatrix4<T>& right);
	static T Determinant(const SGLMatrix4<T>& right);
	static SGLMatrix4<T> Adjoint(const SGLMatrix4<T>& right);
	static SGLMatrix4<T> GLOrthoGraphic(const T& left, const T& right, const T& top, const T& bottom, const T& znear, const T& zfar);
	static SGLMatrix4<T> GLPerspective(const T& fov, const T& aspect, const T& znear, const T& zfar);
	static SGLMatrix4<T> LookAt(const SGLVector3<T>& position, const SGLVector3<T>& target, const SGLVector3<T>& up);
	static SGLMatrix3<T> ToMatrix3(const SGLMatrix4<T>& matrix);

	static const SGLMatrix4<T> IDENTITY;
};

typedef SGLMatrix4<float> SGLMatrix4f;
typedef SGLMatrix4<int32_t> SGLMatrix4i32;
typedef SGLMatrix4<uint32_t> SGLMatrix4u32;

template<typename T>
const SGLMatrix4<T> SGLMatrix4<T>::IDENTITY = SGLMatrix4<T>();

template<typename T>
inline T SGLMatrix4<T>::Determinant(const SGLMatrix4<T>& right)
{
	return right.elements[0] * right.elements[5] * right.elements[10] * right.elements[15] -
		right.elements[4] * right.elements[9] * right.elements[14] * right.elements[3] +
		right.elements[8] * right.elements[13] * right.elements[2] * right.elements[7] -
		right.elements[12] * right.elements[1] * right.elements[6] * right.elements[11] +
		right.elements[12] * right.elements[9] * right.elements[6] * right.elements[3] -
		right.elements[0] * right.elements[12] * right.elements[10] * right.elements[7] +
		right.elements[4] * right.elements[1] * right.elements[14] * right.elements[11] -
		right.elements[8] * right.elements[5] * right.elements[2] * right.elements[15]
		+
		right.elements[4] * right.elements[9] * right.elements[2] * right.elements[15] -
		right.elements[8] * right.elements[1] * right.elements[14] * right.elements[7] +
		right.elements[0] * right.elements[13] * right.elements[6] * right.elements[11] -
		right.elements[12] * right.elements[5] * right.elements[10] * right.elements[3] +
		right.elements[12] * right.elements[1] * right.elements[10] * right.elements[7] -
		right.elements[4] * right.elements[13] * right.elements[2] * right.elements[11] +
		right.elements[8] * right.elements[5] * right.elements[14] * right.elements[3] -
		right.elements[0] * right.elements[9] * right.elements[6] * right.elements[15]
		+
		right.elements[8] * right.elements[1] * right.elements[6] * right.elements[15] -
		right.elements[0] * right.elements[5] * right.elements[14] * right.elements[11] +
		right.elements[4] * right.elements[13] * right.elements[10] * right.elements[3] -
		right.elements[12] * right.elements[9] * right.elements[2] * right.elements[7] +
		right.elements[12] * right.elements[5] * right.elements[2] * right.elements[11] -
		right.elements[8] * right.elements[13] * right.elements[6] * right.elements[3] +
		right.elements[0] * right.elements[9] * right.elements[14] * right.elements[7] -
		right.elements[4] * right.elements[1] * right.elements[10] * right.elements[15]
		;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::Adjoint(const SGLMatrix4<T>& right)
{
	return SGLMatrix4<T>();
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::GLOrthoGraphic(const T& left, const T& right, const T& top, const T& bottom, const T& znear, const T& zfar)
{
	SGLMatrix4<T> tmp;
	tmp.elements[0] = 2 / (right - left);
	tmp.elements[5] = 2 / (top - bottom);
	tmp.elements[10] = 2 / (znear - zfar);
	tmp.elements[12] = (left + right) / (left - right);
	tmp.elements[13] = (bottom + top) / (bottom - top);
	tmp.elements[14] = (znear + zfar) / (znear - zfar);
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::GLPerspective(const T& fov, const T& aspect, const T& znear, const T& zfar)
{
	SGLMatrix4<T> tmp(static_cast<T>(0.0f));
	T cotFov = SGLMath::Cot(fov / 2);
	tmp.elements[0] = cotFov / aspect;
	tmp.elements[5] = cotFov;
	tmp.elements[10] = (znear + zfar) / (znear - zfar);
	tmp.elements[11] = static_cast<T>(-1.0f);
	tmp.elements[14] = 2 * znear * zfar / (znear - zfar);

	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::LookAt(const SGLVector3<T>& position, const SGLVector3<T>& target, const SGLVector3<T>& up)
{
	SGLVector3<T> axisZ = SGLVector3<T>::Normalize(position - target);
	SGLVector3<T> axisX = SGLVector3<T>::Normalize(SGLVector3<T>::Cross(up, axisZ));
	SGLVector3<T> axisY = SGLVector3<T>::Normalize(SGLVector3<T>::Cross(axisZ, axisX));

	SGLMatrix4<T> rotPart;
	rotPart.elements[0] = axisX.x;
	rotPart.elements[1] = axisY.x;
	rotPart.elements[2] = axisZ.x;

	rotPart.elements[4] = axisX.y;
	rotPart.elements[5] = axisY.y;
	rotPart.elements[6] = axisZ.y;

	rotPart.elements[8] = axisX.z;
	rotPart.elements[9] = axisY.z;
	rotPart.elements[10] = axisZ.z;

	SGLMatrix4<T> transPart;
	transPart.elements[12] = -position.x;
	transPart.elements[13] = -position.y;
	transPart.elements[14] = -position.z;

	return rotPart * transPart;
}

template<typename T>
inline SGLMatrix3<T> SGLMatrix4<T>::ToMatrix3(const SGLMatrix4<T>& matrix)
{
	SGLMatrix3<T> tmp;
	tmp.elements[0] = matrix.elements[0];
	tmp.elements[1] = matrix.elements[1];
	tmp.elements[2] = matrix.elements[2];
	tmp.elements[3] = matrix.elements[4];
	tmp.elements[4] = matrix.elements[5];
	tmp.elements[5] = matrix.elements[6];
	tmp.elements[6] = matrix.elements[8];
	tmp.elements[7] = matrix.elements[9];
	tmp.elements[8] = matrix.elements[10];
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> operator+(const SGLMatrix4<T>& left, const SGLMatrix4<T>& right)
{
	SGLMatrix4<T> tmp;
	for (uint8_t i = 0; i < 4; ++i)
		tmp.col[i] = _mm_add_ps(left.col[i], right.col[i]);
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> operator-(const SGLMatrix4<T>& left, const SGLMatrix4<T>& right)
{
	SGLMatrix4<T> tmp;
	for (uint8_t i = 0; i < 4; ++i)
		tmp.col[i] = _mm_sub_ps(left.col[i], right.col[i]);
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> operator*(const SGLMatrix4<T>& left, const SGLMatrix4<T>& right)
{
	SGLMatrix4<T> tmp;

	tmp.elements[0] = left.elements[0] * right.elements[0] + left.elements[4] * right.elements[1] + left.elements[8] * right.elements[2] + left.elements[12] * right.elements[3];
	tmp.elements[1] = left.elements[1] * right.elements[0] + left.elements[5] * right.elements[1] + left.elements[9] * right.elements[2] + left.elements[13] * right.elements[3];
	tmp.elements[2] = left.elements[2] * right.elements[0] + left.elements[6] * right.elements[1] + left.elements[10] * right.elements[2] + left.elements[14] * right.elements[3];
	tmp.elements[3] = left.elements[3] * right.elements[0] + left.elements[7] * right.elements[1] + left.elements[11] * right.elements[2] + left.elements[15] * right.elements[3];

	tmp.elements[4] = left.elements[0] * right.elements[4] + left.elements[4] * right.elements[5] + left.elements[8] * right.elements[6] + left.elements[12] * right.elements[7];
	tmp.elements[5] = left.elements[1] * right.elements[4] + left.elements[5] * right.elements[5] + left.elements[9] * right.elements[6] + left.elements[13] * right.elements[7];
	tmp.elements[6] = left.elements[2] * right.elements[4] + left.elements[6] * right.elements[5] + left.elements[10] * right.elements[6] + left.elements[14] * right.elements[7];
	tmp.elements[7] = left.elements[3] * right.elements[4] + left.elements[7] * right.elements[5] + left.elements[11] * right.elements[6] + left.elements[15] * right.elements[7];

	tmp.elements[8] = left.elements[0] * right.elements[8] + left.elements[4] * right.elements[9] + left.elements[8] * right.elements[10] + left.elements[12] * right.elements[11];
	tmp.elements[9] = left.elements[1] * right.elements[8] + left.elements[5] * right.elements[9] + left.elements[9] * right.elements[10] + left.elements[13] * right.elements[11];
	tmp.elements[10] = left.elements[2] * right.elements[8] + left.elements[6] * right.elements[9] + left.elements[10] * right.elements[10] + left.elements[14] * right.elements[11];
	tmp.elements[11] = left.elements[3] * right.elements[8] + left.elements[7] * right.elements[9] + left.elements[11] * right.elements[10] + left.elements[15] * right.elements[11];

	tmp.elements[12] = left.elements[0] * right.elements[12] + left.elements[4] * right.elements[13] + left.elements[8] * right.elements[14] + left.elements[12] * right.elements[15];
	tmp.elements[13] = left.elements[1] * right.elements[12] + left.elements[5] * right.elements[13] + left.elements[9] * right.elements[14] + left.elements[13] * right.elements[15];
	tmp.elements[14] = left.elements[2] * right.elements[12] + left.elements[6] * right.elements[13] + left.elements[10] * right.elements[14] + left.elements[14] * right.elements[15];
	tmp.elements[15] = left.elements[3] * right.elements[12] + left.elements[7] * right.elements[13] + left.elements[11] * right.elements[14] + left.elements[15] * right.elements[15];

	return tmp;
}

template<typename T>
inline SGLMatrix4<T> operator/(const SGLMatrix4<T>& left, const T& value)
{
	if (!SGLMath::IsNearZero(value))
	{
		SGLMatrix4<T> tmp;
		for (uint8_t i = 0; i < 4; ++i)
			tmp.col[i] = _mm_div_ps(left.col[i], _mm_set_ps1(value));
		return tmp;
	}
	return left;
}

template<typename T>
inline SGLMatrix4<T> operator*(const T& value, const SGLMatrix4<T>& right)
{
	SGLMatrix4<T> tmp;
	for (uint8_t i = 0; i < 4; ++i)
		tmp.col[i] = _mm_mul_ps(right.col[i], _mm_set_ps1(value));
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> operator*(const SGLMatrix4<T>& left, const T& value)
{
	return value*left;
}

template<typename T>
inline SGLMatrix4<T>& SGLMatrix4<T>::operator+=(const SGLMatrix4<T>& right)
{
	// TODO: 在此处插入 return 语句
	*this = *this + right;
	return *this;
}

template<typename T>
inline SGLMatrix4<T>& SGLMatrix4<T>::operator-=(const SGLMatrix4<T>& right)
{
	// TODO: 在此处插入 return 语句
	*this = this - right;
	return *this;
}

template<typename T>
inline SGLMatrix4<T>& SGLMatrix4<T>::operator*=(const SGLMatrix4<T>& right)
{
	// TODO: 在此处插入 return 语句
	*this = *this * right;
	return *this;
}

template<typename T>
inline SGLMatrix4<T>& SGLMatrix4<T>::operator*=(const T& value)
{
	// TODO: 在此处插入 return 语句
	*this = *this * value;
	return *this;
}


template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::Translate(const SGLVector3<T>& position)
{
	SGLMatrix4<T> tmp;
	tmp.col[3] = _mm_set_ps(static_cast<T>(1.0f), position.z, position.y, position.x);
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::Rotate(const SGLVector3<T>& axis, const T& radian)
{
	SGLMatrix4<T> tmp;
	T radian_cos = SGLMath::Cos(radian);
	T radian_sin = SGLMath::Sin(radian);
	T tmpNum = static_cast<T>(1.0f) - radian_cos;

	tmp.elements[0] = axis.x * axis.x * tmpNum + radian_cos;
	tmp.elements[1] = axis.y * axis.x * tmpNum + axis.z * radian_sin;
	tmp.elements[2] = axis.x * axis.z * tmpNum - axis.y * radian_sin;

	tmp.elements[4] = axis.y * axis.x * tmpNum - axis.z * radian_sin;
	tmp.elements[5] = axis.y * axis.y * tmpNum + radian_cos;
	tmp.elements[6] = axis.z * axis.y * tmpNum + axis.x * radian_sin;

	tmp.elements[8] = axis.x * axis.z * tmpNum + axis.y * radian_sin;
	tmp.elements[9] = axis.z * axis.y * tmpNum - axis.x * radian_sin;
	tmp.elements[10] = axis.z * axis.z * tmpNum + radian_cos;

	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::Scale(const T& factor)
{
	SGLMatrix4<T> tmp;
	tmp.elements[0] = factor;
	tmp.elements[5] = factor;
	tmp.elements[10] = factor;
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::Scale(const SGLVector3<T>& factor)
{
	SGLMatrix4<T> tmp;
	tmp.elements[0] = factor.x;
	tmp.elements[5] = factor.y;
	tmp.elements[10] = factor.z;
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::Transpose(const SGLMatrix4<T>& right)
{
	SGLMatrix4<T> tmp;
	tmp.col[0] = _mm_set_ps(right.elements[12], right.elements[8], right.elements[4], right.elements[0]);
	tmp.col[1] = _mm_set_ps(right.elements[13], right.elements[9], right.elements[5], right.elements[1]);
	tmp.col[2] = _mm_set_ps(right.elements[14], right.elements[10], right.elements[6], right.elements[2]);
	tmp.col[3] = _mm_set_ps(right.elements[15], right.elements[11], right.elements[7], right.elements[3]);
	return tmp;
}

template<typename T>
inline SGLMatrix4<T> SGLMatrix4<T>::Inverse(const SGLMatrix4<T>& right)
{
	return SGLMatrix4<T>::Adjoint(right)/SGLMatrix4<T>::Determinant(right);
}

template<typename T>
inline SGLMatrix4<T>::SGLMatrix4()
	:col({ _mm_set_ps(static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(1.0f)),
		_mm_set_ps(static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(1.0f), static_cast<T>(0.0f)),
		_mm_set_ps(static_cast<T>(0.0f), static_cast<T>(1.0f), static_cast<T>(0.0f), static_cast<T>(0.0f)),
		_mm_set_ps(static_cast<T>(1.0f), static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(0.0f)) })
{
}

template<typename T>
inline SGLMatrix4<T>::SGLMatrix4(const T& value)
	:col({ _mm_set_ps(static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(0.0f), value),
		_mm_set_ps(static_cast<T>(0.0f), static_cast<T>(0.0f), value, static_cast<T>(0.0f)),
		_mm_set_ps(static_cast<T>(0.0f), value, static_cast<T>(0.0f), static_cast<T>(0.0f)),
		_mm_set_ps(value, static_cast<T>(0.0f), static_cast<T>(0.0f), static_cast<T>(0.0f)) })
{
}

template<typename T>
inline SGLMatrix4<T>::SGLMatrix4(const SGLVector4<T>& diagonal)
	:col({ _mm_set_ps1(static_cast<T>(0.0f)), _mm_set_ps1(static_cast<T>(0.0f)), _mm_set_ps1(static_cast<T>(0.0f)), _mm_set_ps1(static_cast<T>(0.0f)) })
{
	Set(diagonal);
}

template<typename T>
inline SGLMatrix4<T>::SGLMatrix4(const T& d00, const T& d11, const T& d22, const T& d33)
	:col({ _mm_set_ps1(static_cast<T>(0.0f)), _mm_set_ps1(static_cast<T>(0.0f)), _mm_set_ps1(static_cast<T>(0.0f)), _mm_set_ps1(static_cast<T>(0.0f)) })
{
	Set(d00, d11, d22, d33);
}

template<typename T>
inline SGLMatrix4<T>::SGLMatrix4(const T& e00, const T& e10, const T& e20, const T& e30, const T& e01, const T& e11, const T& e21, const T& e31, const T& e02, const T& e12, const T& e22, const T& e32, const T& e03, const T& e13, const T& e23, const T& e33)
	:col({ _mm_set_ps(e30, e20, e10, e00),
		_mm_set_ps(e31,e21,e11,e01),
		_mm_set_ps(e32,e22,e12,e02),
		_mm_set_ps(e33,e23,e13,e03) })
{
}

template<typename T>
inline void SGLMatrix4<T>::Set(const SGLVector4<T>& diagonal)
{
	Set(diagonal.x, diagonal.y, diagonal.z, diagonal.w);
}

template<typename T>
inline void SGLMatrix4<T>::Set(const T& d00, const T& d11, const T& d22, const T& d33)
{
	elements[0] = d00;
	elements[5] = d11;
	elements[10] = d22;
	elements[15] = d33;
}

template<typename T>
inline void SGLMatrix4<T>::Set(const T& e00, const T& e10, const T& e20, const T& e30, const T& e01, const T& e11, const T& e21, const T& e31, const T& e02, const T& e12, const T& e22, const T& e32, const T& e03, const T& e13, const T& e23, const T& e33)
{
	col[0] = _mm_set_ps(e30, e20, e10, e00);
	col[1] = _mm_set_ps(e31, e21, e11, e01);
	col[2] = _mm_set_ps(e32, e22, e12, e02);
	col[2] = _mm_set_ps(e33, e23, e13, e03);
}
