#pragma once
#include <cstring>
#include <assert.h>
#include <xmmintrin.h>

#pragma warning(push)
#pragma warning(disable : 4201)

namespace CommonUtilities
{
	template <typename T>
	struct Matrix44
	{
	public:
		Matrix44<T>();
		Matrix44<T>(const Matrix44<T>& aMatrix);
		Matrix44<T>(const Matrix33<T>& aMatrix, const Vector3<T>& aVector = Vector3<T>());
		Matrix44<T>(const T aMatrix[16]);
		Matrix44<T>(const T& a11, const T& a12, const T& a13, const T& a14, const T& a21, const T& a22, const T& a23, const T& a24, const T& a31, const T& a32, const T& a33, const T& a34, const T& a41, const T& a42, const T& a43, const T& a44);
		//Matrix44<T>(const Vector3<T> & aScale, const Vector3<T> & aRotation, const Vector3<T> & aTranslation);

		Matrix44<T>& operator=(const Matrix44<T>& aMatrix);
		Vector4<T>& operator[](const int aIndex);
		const Vector4<T>& operator[](const int aIndex) const;

		static Matrix44<T> CreateLookAtLH(const Vector3<T>& aEye, const Vector3<T>& aAt, const Vector3<T>& aUp = { 0.f, 1.f, 0.f });
		static Matrix44<T> CreatePerspectiveFovLH(float aAspectHByW, float aFovAngleY,	float aNearZ, float aFarZ);
		static Matrix44<T> CreateOrthoProjectionMatrix(float aWidth, float aHeight, float aNearZ, float aFarZ);
		static Matrix44<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundZ(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundAxis(const Vector3<T>& aAxis, T aAngleInRadians);
		static Matrix44<T> Transpose(const Matrix44<T>& aMatrixToTranspose);
		void Transpose();
		static Matrix44<T> GetFastInverse(const Matrix44<T>& aMatrix);
		static Matrix44<T> CreateTranslation(const Vector3<T>& aTranslation);
		static Matrix44<T> CreateScaling(const Vector3<T>& aScale);
		static Matrix44<T> CreateRotation(const Vector3<T>& aRotation);
		const Vector3<T>& GetTranslation() const;
		float GetDeterminant() const;
		Matrix44<T> GetSlowInverse() const;
		void SetTranslation(const Vector3<T>& aTranslation);

		T& At(int aX, int aY);
		const T& At(int aX, int aY) const;

		union
		{
			struct
			{
				T _11, _12, _13, _14;
				T _21, _22, _23, _24;
				T _31, _32, _33, _34;
				T _41, _42, _43, _44;
			};
			struct
			{
				__m128 m1, m2, m3, m4;
			};
			struct
			{
				Vector4<T> row0, row1, row2, row3;
			};
			struct
			{
				T myMatrix[16];
			};
		};
	};
	//operators

	template <typename T>
	Matrix44<T> operator+(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		Matrix44<T> sum;
		for (int i = 0; i < 16; i++)
		{
			sum.myMatrix[i] = aMatrix0.myMatrix[i] + aMatrix1.myMatrix[i];
		}
		return sum;
	}

	template <typename T>
	Matrix44<T> operator-(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		Matrix44<T> difference;
		for (int i = 0; i < 16; i++)
		{
			difference.myMatrix[i] = aMatrix0.myMatrix[i] - aMatrix1.myMatrix[i];
		}
		return difference;
	}

	template <typename T>
	Matrix44<T> operator*(const Matrix44<T>& aMatrix0, const float aScalar)
	{
		Matrix44<T> difference;
		for (int i = 0; i < 16; i++)
		{
			difference.myMatrix[i] = aMatrix0.myMatrix[i] * aScalar;
		}
		return difference;
	}

	template <typename T>
	Matrix44<T> operator*(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
 		Matrix44<T> product;
 		__m128 t1, t2;
 
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[0]);
 		t2 = _mm_mul_ps(aMatrix1.m1, t1);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[1]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m2, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[2]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m3, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[3]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m4, t1), t2);
 
 		_mm_store_ps(&product.myMatrix[0], t2);
 
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[4]);
 		t2 = _mm_mul_ps(aMatrix1.m1, t1);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[5]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m2, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[6]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m3, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[7]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m4, t1), t2);
 
 		_mm_store_ps(&product.myMatrix[4], t2);
 
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[8]);
 		t2 = _mm_mul_ps(aMatrix1.m1, t1);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[9]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m2, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[10]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m3, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[11]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m4, t1), t2);
 
 		_mm_store_ps(&product.myMatrix[8], t2);
 
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[12]);
 		t2 = _mm_mul_ps(aMatrix1.m1, t1);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[13]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m2, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[14]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m3, t1), t2);
 		t1 = _mm_set1_ps(aMatrix0.myMatrix[15]);
 		t2 = _mm_add_ps(_mm_mul_ps(aMatrix1.m4, t1), t2);
 
 		_mm_store_ps(&product.myMatrix[12], t2);
		return product;
	}

	template <typename T>
	void operator+=(Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 + aMatrix1;
	}

	template <typename T>
	void operator-=(Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 - aMatrix1;
	}

	template <typename T>
	void operator*=(Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 * aMatrix1;
	}

	template <typename T>
	bool operator==(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		if (aMatrix0.myMatrix[0] != aMatrix1.myMatrix[0]
			|| aMatrix0.myMatrix[1] != aMatrix1.myMatrix[1]
			|| aMatrix0.myMatrix[2] != aMatrix1.myMatrix[2]
			|| aMatrix0.myMatrix[3] != aMatrix1.myMatrix[3]
			|| aMatrix0.myMatrix[4] != aMatrix1.myMatrix[4]
			|| aMatrix0.myMatrix[5] != aMatrix1.myMatrix[5]
			|| aMatrix0.myMatrix[6] != aMatrix1.myMatrix[6]
			|| aMatrix0.myMatrix[7] != aMatrix1.myMatrix[7]
			|| aMatrix0.myMatrix[8] != aMatrix1.myMatrix[8]
			|| aMatrix0.myMatrix[9] != aMatrix1.myMatrix[9]
			|| aMatrix0.myMatrix[10] != aMatrix1.myMatrix[10]
			|| aMatrix0.myMatrix[11] != aMatrix1.myMatrix[11]
			|| aMatrix0.myMatrix[12] != aMatrix1.myMatrix[12]
			|| aMatrix0.myMatrix[13] != aMatrix1.myMatrix[13]
			|| aMatrix0.myMatrix[14] != aMatrix1.myMatrix[14]
			|| aMatrix0.myMatrix[15] != aMatrix1.myMatrix[15])
		{
			return false;
		}
		return true;
	}

	template <typename T>
	bool operator!=(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		if (aMatrix0.myMatrix[0] != aMatrix1.myMatrix[0]
			|| aMatrix0.myMatrix[1] != aMatrix1.myMatrix[1]
			|| aMatrix0.myMatrix[2] != aMatrix1.myMatrix[2]
			|| aMatrix0.myMatrix[3] != aMatrix1.myMatrix[3]
			|| aMatrix0.myMatrix[4] != aMatrix1.myMatrix[4]
			|| aMatrix0.myMatrix[5] != aMatrix1.myMatrix[5]
			|| aMatrix0.myMatrix[6] != aMatrix1.myMatrix[6]
			|| aMatrix0.myMatrix[7] != aMatrix1.myMatrix[7]
			|| aMatrix0.myMatrix[8] != aMatrix1.myMatrix[8]
			|| aMatrix0.myMatrix[9] != aMatrix1.myMatrix[9]
			|| aMatrix0.myMatrix[10] != aMatrix1.myMatrix[10]
			|| aMatrix0.myMatrix[11] != aMatrix1.myMatrix[11]
			|| aMatrix0.myMatrix[12] != aMatrix1.myMatrix[12]
			|| aMatrix0.myMatrix[13] != aMatrix1.myMatrix[13]
			|| aMatrix0.myMatrix[14] != aMatrix1.myMatrix[14]
			|| aMatrix0.myMatrix[15] != aMatrix1.myMatrix[15])
		{
			return true;
		}
		return false;
	}


	//Vector operations

	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix44<T>& aMatrix)
	{
		return
		{	
			(aVector.x * aMatrix.At(0, 0) + aVector.y * aMatrix.At(0, 1) + aVector.z * aMatrix.At(0, 2) + aVector.w * aMatrix.At(0, 3)),
			(aVector.x * aMatrix.At(1, 0) + aVector.y * aMatrix.At(1, 1) + aVector.z * aMatrix.At(1, 2) + aVector.w * aMatrix.At(1, 3)),
			(aVector.x * aMatrix.At(2, 0) + aVector.y * aMatrix.At(2, 1) + aVector.z * aMatrix.At(2, 2) + aVector.w * aMatrix.At(2, 3)),
			(aVector.x * aMatrix.At(3, 0) + aVector.y * aMatrix.At(3, 1) + aVector.z * aMatrix.At(3, 2) + aVector.w * aMatrix.At(3, 3))
		};
	}

	template <typename T>
	void operator*=(Vector4<T>& aVector, const Matrix44<T>& aMatrix)
	{
		aVector = aVector*aMatrix;
	}

	//Member functions

	template<typename T>
	inline Matrix44<T>::Matrix44()
		: myMatrix{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1}
	{}

	template<typename T>
	inline Matrix44<T>::Matrix44(const Matrix44<T>& aMatrix)
	{
		memcpy(myMatrix, aMatrix.myMatrix, 16 * sizeof(T));
	}

	template<typename T>
 	inline Matrix44<T>::Matrix44(const Matrix33<T>& aMatrix, const Vector3<T>& aVector = Vector3<T>()) : Matrix44()
 	{
 		memcpy(&myMatrix[0], &aMatrix.myMatrix[0], 3 * sizeof(T));
 		memcpy(&myMatrix[5], &aMatrix.myMatrix[4], 3 * sizeof(T));
 		memcpy(&myMatrix[10], &aMatrix.myMatrix[8], 3 * sizeof(T));
		memcpy(&myMatrix[12], &aVector.x, 3 * sizeof(T));
		myMatrix[3] = 0;
		myMatrix[7] = 0;
		myMatrix[11] = 0;
		myMatrix[15] = 1;
 	}

	template<typename T>
	inline Matrix44<T>::Matrix44(const T aMatrix[16])
	{
		memcpy(myMatrix, aMatrix, 16 * sizeof(T));
	}

	template<typename T>
	inline Matrix44<T>::Matrix44(const T & a11, const T & a12, const T & a13, const T & a14, const T & a21, const T & a22, const T & a23, const T & a24, const T & a31, const T & a32, const T & a33, const T & a34, const T & a41, const T & a42, const T & a43, const T & a44)
	{
		myMatrix[0] = a11;
		myMatrix[1] = a12;
		myMatrix[2] = a13;
		myMatrix[3] = a14;
		myMatrix[4] = a21;
		myMatrix[5] = a22;
		myMatrix[6] = a23;
		myMatrix[7] = a24;
		myMatrix[8] = a31;
		myMatrix[9] = a32;
		myMatrix[10] = a33;
		myMatrix[11] = a34;
		myMatrix[12] = a41;
		myMatrix[13] = a42;
		myMatrix[14] = a43;
		myMatrix[15] = a44;
	}

	template<typename T>
	inline Matrix44<T>& Matrix44<T>::operator=(const Matrix44<T>& aMatrix)
	{
		memcpy(myMatrix, aMatrix.myMatrix, sizeof(T) * 16);
		return *this;
	}

	template<typename T>
	inline Vector4<T>& Matrix44<T>::operator[](const int aIndex)
	{
		assert(aIndex >= 0 && aIndex < 4);
		return (Vector4<T>&)myMatrix[aIndex * 4];
	}

	template<typename T>
	inline const Vector4<T> & Matrix44<T>::operator[](const int aIndex) const
	{
		assert(aIndex >= 0 && aIndex < 4);
		return (const Vector4<T>&)myMatrix[aIndex * 4];
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreateLookAtLH(const Vector3<T>& aEye, const Vector3<T>& aAt, const Vector3<T>& aUp)
	{
		Vector3<T> zAxis((aAt - aEye).GetNormalized());
		Vector3<T> xAxis(aUp.Cross(zAxis).GetNormalized());
		Vector3<T> yAxis(zAxis.Cross(xAxis));
		return
		{
			xAxis.x,	yAxis.x,	zAxis.x,	0,
			xAxis.y,	yAxis.y,	zAxis.y,	0,
			xAxis.z,	yAxis.z,	zAxis.z,	0,
			-xAxis.Dot(aEye),	-yAxis.Dot(aEye),	zAxis.Dot(aEye),	1
		};
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreatePerspectiveFovLH(float aAspectHByW, float aFovAngleY, float aNearZ, float aFarZ)
	{
		float value = 0.5f * aFovAngleY;

		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
		float quotient = _1DIV2PI_F*value;
		if (value >= 0.0f)
		{
			quotient = (float)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (float)((int)(quotient - 0.5f));
		}
		float y = value - _2PI_F*quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		float sign;
		if (y > _PIDIV2_F)
		{
			y = PI_F - y;
			sign = -1.0f;
		}
		else if (y < -_PIDIV2_F)
		{
			y = -PI_F - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		float sinFov = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		float cosFov = sign*p;

		//DirectX::XMScalarSinCos(&sinFov, &cosFov, value);

		float height = cosFov / sinFov;
		float width = height / aAspectHByW;
		float fRange = aFarZ / (aFarZ - aNearZ);

		Matrix44f projectionMatrix;
		projectionMatrix[0][0] = width;
		projectionMatrix[1][1] = height;
		projectionMatrix[2][2] = fRange;
		projectionMatrix[2][3] = 1.0f;
		projectionMatrix[3][2] = -fRange * aNearZ;
		projectionMatrix[3][3] = 0.0f;
		return projectionMatrix;
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreateOrthoProjectionMatrix(float aWidth, float aHeight, float aNearZ, float aFarZ)
	{
		float fRange = 1.0f / (aFarZ - aNearZ);

		Matrix44f M;
		M[0][0] = 2.0f / aWidth;
		M[1][1] = 2.0f / aHeight;
		M[2][2] = fRange;
		M[3][2] = -fRange * aNearZ;
		return M;
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			1,	0,	0,	0,
			0,	c,	s,	0,
			0,	-s,	c,	0,
			0,	0,	0,	1
		};
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			c,	0,	-s,	0,
			0,	1,	0,	0,
			s,	0,	c,	0,
			0,	0,	0,	1,
		};
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			c,	s,	0,	0,
			-s,	c,	0,	0,
			0,	0,	1,	0,
			0,	0,	0,	1
		};
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreateRotateAroundAxis(const Vector3<T>& aAxis, T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return CU::Matrix44<T>(
			(aAxis.x*aAxis.x*(1 - c) + c),			(aAxis.x*aAxis.y*(1 - c) + aAxis.z*s),	(aAxis.x*aAxis.z*(1 - c) - aAxis.y*s),	static_cast<T>(0),
			(aAxis.x*aAxis.y*(1 - c) - aAxis.z*s),	(aAxis.y*aAxis.y*(1 - c) + c),			(aAxis.y*aAxis.z*(1 - c) + aAxis.x*s),	static_cast<T>(0),
			(aAxis.x*aAxis.z*(1 - c) + aAxis.y*s),	(aAxis.y*aAxis.z*(1 - c) - aAxis.x*s),	(aAxis.z*aAxis.z*(1 - c) + c),			static_cast<T>(0),
			static_cast<T>(0),						static_cast<T>(0),						static_cast<T>(0),						static_cast<T>(1)
		);
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::Transpose(const Matrix44<T>& aMatrixToTranspose)
	{
		return {
			aMatrixToTranspose.myMatrix[0], aMatrixToTranspose.myMatrix[4], aMatrixToTranspose.myMatrix[8], aMatrixToTranspose.myMatrix[12],
			aMatrixToTranspose.myMatrix[1], aMatrixToTranspose.myMatrix[5], aMatrixToTranspose.myMatrix[9], aMatrixToTranspose.myMatrix[13],
			aMatrixToTranspose.myMatrix[2], aMatrixToTranspose.myMatrix[6], aMatrixToTranspose.myMatrix[10], aMatrixToTranspose.myMatrix[14],
			aMatrixToTranspose.myMatrix[3], aMatrixToTranspose.myMatrix[7], aMatrixToTranspose.myMatrix[11], aMatrixToTranspose.myMatrix[15]
		};
	}

	template<typename T>
	inline void Matrix44<T>::Transpose()
	{
		*this = Matrix44<T>::Transpose(*this);
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::GetFastInverse(const Matrix44<T>& aMatrix)
	{
		T inverseX = (-aMatrix.myMatrix[12] * aMatrix.myMatrix[0]) + (-aMatrix.myMatrix[13] * aMatrix.myMatrix[1]) + (-aMatrix.myMatrix[14] * aMatrix.myMatrix[2]);
		T inverseY = (-aMatrix.myMatrix[12] * aMatrix.myMatrix[4]) + (-aMatrix.myMatrix[13] * aMatrix.myMatrix[5]) + (-aMatrix.myMatrix[14] * aMatrix.myMatrix[6]);
		T inverseZ = (-aMatrix.myMatrix[12] * aMatrix.myMatrix[8]) + (-aMatrix.myMatrix[13] * aMatrix.myMatrix[9]) + (-aMatrix.myMatrix[14] * aMatrix.myMatrix[10]);

		return{
			aMatrix.myMatrix[0],	aMatrix.myMatrix[4],	aMatrix.myMatrix[8],		aMatrix.myMatrix[3],
			aMatrix.myMatrix[1],	aMatrix.myMatrix[5],	aMatrix.myMatrix[9],		aMatrix.myMatrix[7],
			aMatrix.myMatrix[2],	aMatrix.myMatrix[6],	aMatrix.myMatrix[10],	aMatrix.myMatrix[11],
			inverseX,	inverseY,	inverseZ,		aMatrix.myMatrix[15]
		};
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::CreateTranslation(const Vector3<T>& aTranslation)
	{
		return
		{ 
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			aTranslation.x, aTranslation.y, aTranslation.z, 1
		};
	}

	template <typename T>
	inline Matrix44<T> Matrix44<T>::CreateScaling(const Vector3<T>& aScale)
	{
		return
		{
			aScale.x, 0, 0, 0,
			0, aScale.y, 0, 0,
			0, 0, aScale.z, 0,
			0, 0, 0, 1
		};
	}



	template <typename T>
	inline Matrix44<T> Matrix44<T>::CreateRotation(const Vector3<T>& aRotation)
	{
		return CreateRotateAroundZ(aRotation.z) * CreateRotateAroundX(aRotation.x) * CreateRotateAroundY(aRotation.y);
	}

	template<typename T>
	inline const Vector3<T> & Matrix44<T>::GetTranslation() const
	{
		return row3.ToVector3();
	}

	template<typename T>
	inline float Matrix44<T>::GetDeterminant() const
	{
		return _11 * _22 * _33
			+ _12 * _23 * _31
			+ _13 * _21 * _32
			- _13 * _22 * _31
			- _12 * _21 * _33
			- _11 * _23 * _32;
	}

	template<typename T>
	inline Matrix44<T> Matrix44<T>::GetSlowInverse() const
	{
		Matrix44<T> inverse;

		Matrix44<T> transposedSrcMatrix = Matrix44<T>::Transpose(*this);
		T* src = transposedSrcMatrix.myMatrix;

		// calculate pairs for first 8 elements (cofactors)
		T tmp[12];
		tmp[0] = src[10] * src[15];
		tmp[1] = src[11] * src[14];
		tmp[2] = src[9] * src[15];
		tmp[3] = src[11] * src[13];
		tmp[4] = src[9] * src[14];
		tmp[5] = src[10] * src[13];
		tmp[6] = src[8] * src[15];
		tmp[7] = src[11] * src[12];
		tmp[8] = src[8] * src[14];
		tmp[9] = src[10] * src[12];
		tmp[10] = src[8] * src[13];
		tmp[11] = src[9] * src[12];

		// calculate first 8 elements (cofactors)
		inverse.myMatrix[0] = (tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7]) - (tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7]);
		inverse.myMatrix[1] = (tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7]) - (tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7]);
		inverse.myMatrix[2] = (tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7]) - (tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7]);
		inverse.myMatrix[3] = (tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6]) - (tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6]);
		inverse.myMatrix[4] = (tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3]) - (tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3]);
		inverse.myMatrix[5] = (tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3]) - (tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3]);
		inverse.myMatrix[6] = (tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3]) - (tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3]);
		inverse.myMatrix[7] = (tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2]) - (tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2]);

		// calculate pairs for second 8 elements (cofactors)
		tmp[0] = src[2] * src[7];
		tmp[1] = src[3] * src[6];
		tmp[2] = src[1] * src[7];
		tmp[3] = src[3] * src[5];
		tmp[4] = src[1] * src[6];
		tmp[5] = src[2] * src[5];
		tmp[6] = src[0] * src[7];
		tmp[7] = src[3] * src[4];
		tmp[8] = src[0] * src[6];
		tmp[9] = src[2] * src[4];
		tmp[10] = src[0] * src[5];
		tmp[11] = src[1] * src[4];

		// calculate second 8 elements (cofactors)
		inverse.myMatrix[8] = (tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15]) - (tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15]);
		inverse.myMatrix[9] = (tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15]) - (tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15]);
		inverse.myMatrix[10] = (tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15]) - (tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15]);
		inverse.myMatrix[11] = (tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14]) - (tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14]);
		inverse.myMatrix[12] = (tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9]) - (tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10]);
		inverse.myMatrix[13] = (tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10]) - (tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8]);
		inverse.myMatrix[14] = (tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8]) - (tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9]);
		inverse.myMatrix[15] = (tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9]) - (tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8]);

		// calculate determinant
		T det = src[0] * inverse.myMatrix[0] + src[1] * inverse.myMatrix[1] + src[2] * inverse.myMatrix[2] + src[3] * inverse.myMatrix[3];

		// calculate matrix inverse
		T invdet = 1 / det;
		for (uint j = 0; j < 16; ++j)
		{
			inverse.myMatrix[j] *= invdet;
		}

		return inverse;
	}

	template<typename T>
	inline void Matrix44<T>::SetTranslation(const Vector3<T>& aTranslation)
	{
		myMatrix[12] = aTranslation.x;
		myMatrix[13] = aTranslation.y;
		myMatrix[14] = aTranslation.z;
	}

	template<typename T>
	inline T& Matrix44<T>::At(int aX, int aY)
	{
		assert(aX >= 0 && aX < 4 && "Tried to access invalid matrix element!");
		assert(aY >= 0 && aY < 4 && "Tried to access invalid matrix element!");
		return myMatrix[aY * 4 + aX];
	}

	template<typename T>
	inline const T& Matrix44<T>::At(int aX, int aY) const
	{
		assert(aX >= 0 && aX < 4 && "Tried to access invalid matrix element!");
		assert(aY >= 0 && aY < 4 && "Tried to access invalid matrix element!");
		return myMatrix[aY * 4 + aX];
	}
}

namespace CU = CommonUtilities;
#pragma warning(pop)