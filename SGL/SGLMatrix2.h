#pragma once
#include <xmmintrin.h>
#include <array>

template<typename T>
class SGLVector2;

template<typename T>
class SGLMatrix3;

template<typename T>
class SGLMatrix2
{
public:

	union
	{
		struct
		{
			__m128 col;
		};
		struct
		{
			std::array<T, 4> elements;
		};
	};

	SGLMatrix2();
	SGLMatrix2(const T& value);
	SGLMatrix2(const T& e00, const T& e01, const T& e10, const T& e11);
	SGLMatrix2(const T& d00, const T& d11);
	SGLMatrix2(const SGLVector2<T>& diagonal);
	~SGLMatrix2();

	void Set(const T& e00, const T& e01, const T& e10, const T& e11);
	void Set(const T& d00, const T& d11);
	void Set(const SGLVector2<T>& diagonal);

	inline SGLMatrix2<T>& operator+=(const SGLMatrix2<T>& right);
	inline SGLMatrix2<T>& operator-=(const SGLMatrix2<T>& right);
	inline SGLMatrix2<T>& operator*=(const SGLMatrix2<T>& right);
	inline SGLMatrix2<T>& operator*=(const T& value);

	static SGLMatrix2<T> Rotate(const T& radian);
	static SGLMatrix2<T> Scale(const T& factor);
	static SGLMatrix2<T> Scale(const SGLVector2<T>& factor);
	static T Determinant(const SGLMatrix2<T>& matrix);
	static SGLMatrix2<T> Inverse(const SGLMatrix2<T>& matrix);
	static SGLMatrix2<T> Adjoint(const SGLMatrix2<T>& matrix);
	static SGLMatrix3<T> ToMatrix3(const SGLMatrix2<T>& matrix);

	static const SGLMatrix2<T> IDENTITY;
};

typedef SGLMatrix2<float> SGLMatrix2f;
typedef SGLMatrix2<int32_t> SGLVectori32;
typedef SGLMatrix2<uint32_t> SGLMatrix2u32;

template<typename T>
const SGLMatrix2<T> SGLMatrix2<T>::IDENTITY = SGLMatrix2<T>();

template<typename T>
inline SGLMatrix2<T>::SGLMatrix2()
	:col(static_cast<T>(1.0f),static_cast<T>(0.0f),static_cast<T>(0.0f),static_cast<T>(1.0f))
{
}

template<typename T>
inline SGLMatrix2<T>::SGLMatrix2(const T& value)
	:col(value,static_cast<T>(0.0f),static_cast<T>(0.0f),static_cast<T>(1.0f))
{
}

template<typename T>
inline SGLMatrix2<T>::SGLMatrix2(const T& e00, const T& e01, const T& e10, const T& e11)
	:col(e11,e10,e01,e00)
{
}

template<typename T>
inline SGLMatrix2<T>::SGLMatrix2(const T& d00, const T& d11)
{
	Set(d00, d11);
}

template<typename T>
inline SGLMatrix2<T>::SGLMatrix2(const SGLVector2<T>& diagonal)
{
	Set(diagonal);
}

template<typename T>
inline SGLMatrix2<T>::~SGLMatrix2<T>()
{
}

template<typename T>
inline void SGLMatrix2<T>::Set(const T& e00, const T& e01, const T& e10, const T& e11)
{
	col = _mm_set_ps(e11, e10, e01, e00);
}

template<typename T>
inline void SGLMatrix2<T>::Set(const T& d00, const T& d11)
{
	elements[0] = d00;
	elements[1] = d11;
}

template<typename T>
inline void SGLMatrix2<T>::Set(const SGLVector2<T>& diagonal)
{
	Set(diagonal.x, diagonal.y);
}

template<typename T>
inline SGLMatrix2<T> operator+(const SGLMatrix2<T>& left, const SGLMatrix2<T>& right)
{
	SGLMatrix2<T> tmp;
	tmp.col = _mm_add_ps(left.col, right.col);
	return tmp;
}
template<typename T>
inline SGLMatrix2<T> operator-(const SGLMatrix2<T>& left, const SGLMatrix2<T>& right)
{
	SGLMatrix2<T> tmp;
	tmp.col = _mm_sub_ps(left.col, right.col);
	return tmp;
}

template<typename T>
inline SGLMatrix2<T> operator*(const SGLMatrix2<T>& left, const SGLMatrix2<T>& right)
{
	SGLMatrix2<T> tmp;
	tmp.elements[0] = left.elements[0] * right.elements[0] + left.elements[2] * right.elements[1];
	tmp.elements[2] = left.elements[0] * right.elements[2] + left.elements[2] * right.elements[3];
	tmp.elements[1] = left.elements[1] * right.elements[0] + left.elements[3] * right.elements[1];
	tmp.elements[3] = left.elements[1] * right.elements[2] + left.elements[3] * right.elements[3];
	return tmp;
}

template<typename T>
inline SGLMatrix2<T> operator/(const SGLMatrix2<T>& left,const T& value)
{
	if (!SGLMath::IsNearZero(value))
	{
		SGLMatrix2<T> tmp;
		tmp.col = _mm_sub_ps(left.col, _mm_set_ps1(value));
		return tmp;
	}
	return left;
}

template<typename T>
inline SGLMatrix2<T> operator*(const T& value, const SGLMatrix2<T>& right)
{
	SGLMatrix2<T> tmp;
	tmp.col = _mm_mul_ps(right.col, _mm_set_ps1(value));
	return tmp;
}

template<typename T>
inline SGLMatrix2<T> operator*(const SGLMatrix2<T>& left,const T& value)
{
	return value * left;
}

template<typename T>
inline bool operator==(const SGLMatrix2<T>& left, const SGLMatrix2<T>& right)
{
	for (uint8_t i = 0; i < 4; ++i)
		if (left.elements[i] != right.elements[i])
			return false;
	return true;
}

template<typename T>
inline SGLMatrix2<T>& SGLMatrix2<T>::operator+=(const SGLMatrix2<T>& right)
{
	
	*this = *this + right;
	return *this;
}

template<typename T>
inline SGLMatrix2<T>& SGLMatrix2<T>::operator-=(const SGLMatrix2<T>& right)
{
	
	*this = *this - right;
	return *this;
}

template<typename T>
inline SGLMatrix2<T>& SGLMatrix2<T>::operator*=(const SGLMatrix2<T>& right)
{
	
	*this = *this * right;
	return *this;
}

template<typename T>
inline SGLMatrix2<T>& SGLMatrix2<T>::operator*=(const T& value)
{
	
	*this = *this * value;
	return *this;
}

template<typename T>
inline SGLMatrix2<T> SGLMatrix2<T>::Rotate(const T& radian)
{
	SGLMatrix2<T> tmp;
	tmp.col = _mm_set_ps(SGLMath::Cos(radian), -SGLMath::Sin(radian), SGLMath::Sin(radian), SGLMath::Cos(radian));
	return tmp;
}

template<typename T>
inline SGLMatrix2<T> SGLMatrix2<T>::Scale(const T& factor)
{
	SGLMatrix2<T> tmp;
	tmp.col = _mm_set_ps(factor, static_cast<T>(0.0f), static_cast<T>(0.0f), factor);
	return tmp;
}

template<typename T>
inline SGLMatrix2<T> SGLMatrix2<T>::Scale(const SGLVector2<T>& factor)
{
	SGLMatrix2<T> tmp;
	tmp.col = _mm_set_ps(factor.y, static_cast<T>(0.0f), static_cast<T>(0.0f), factor.x);
}

template<typename T>
inline T SGLMatrix2<T>::Determinant(const SGLMatrix2<T>& matrix)
{
	return matrix.elements[0]*matrix.elements[3]-matrix.elements[2]*matrix.elements[1];
}

template<typename T>
inline SGLMatrix2<T> SGLMatrix2<T>::Inverse(const SGLMatrix2<T>& matrix)
{
	return SGLMatrix2<T>::Adjoint(matrix)/SGLMatrix2<T>::Determinant(matrix);
}

template<typename T>
inline SGLMatrix2<T> SGLMatrix2<T>::Adjoint(const SGLMatrix2<T>& matrix)
{
	SGLMatrix2<T> tmp;
	tmp.col = _mm_set_ps(matrix.elements[0],-matrix.elements[1],-matrix.elements[2],matrix.elements[3]);
	return tmp;
}

template<typename T>
inline SGLMatrix3<T> SGLMatrix2<T>::ToMatrix3(const SGLMatrix2<T>& matrix)
{
	SGLMatrix3<T> tmp;
	tmp.elements[0] = matrix.elements[0];
	tmp.elements[1] = matrix.elements[1];
	tmp.elements[3] = matrix.elements[2];
	tmp.elements[4] = matrix.elements[3];
	return tmp;
}
