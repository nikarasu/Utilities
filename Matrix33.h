#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix44.h"
#include <assert.h>
#include <initializer_list>

#pragma warning(push)
#pragma warning(disable : 4201)

namespace CommonUtilities
{

	template <typename T>
	struct Vector3;

	template <typename T>
	struct Matrix33
	{
	public:
		Matrix33<T>();
		Matrix33<T>(const Matrix33<T>& aMatrix);
		Matrix33<T>(const Matrix44<T>& aMatrix);
		Matrix33<T>(const float aMatrix[9]);
		Matrix33<T>(const std::initializer_list<T> aMatrix);

		Matrix33<T>& operator=(const Matrix33<T>& aMatrix);
		T& operator[](const int aIndex);
		const T& operator[](const int aIndex) const;

		static Matrix33<T> CreateRotationRollPitchYaw(const Vector3<T> & aRotationInRadians);
		static Matrix33<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundZ(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundAxis(const Vector3<T>& aAxis, T aAngleInRadians);
		static Matrix33<T> CreateRotation(const Vector3<T> & aRotation);
		static Matrix33<T> Transpose(const Matrix33<T>& aMatrixToTranspose);



		T& At(int aX, int aY);
		const T& At(int aX, int aY) const;

		union //What's this commie bullshit? // CCCP
		{
			struct
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			struct
			{
				Vector3<T> row0, row1, row2;
			};
			struct
			{
				T myMatrix[9];
			};
		};
	};

	typedef Matrix33<float> Matrix33f;

	//operators

	template <typename T>
	Matrix33<T> operator+(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		Matrix33<T> sum;
		for (int i = 0; i < 9; i++)
		{
			sum.myMatrix[i] = aMatrix0.myMatrix[i] + aMatrix1.myMatrix[i];
		}
		return sum;
	}

	template <typename T>
	Matrix33<T> operator-(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		Matrix33<T> difference;
		for (int i = 0; i < 9; i++)
		{
			difference.myMatrix[i] = aMatrix0.myMatrix[i] - aMatrix1.myMatrix[i];
		}
		return difference;
	}

	template <typename T>
	Matrix33<T> operator*(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		Matrix33<T> product;
		for (int y = 1; y <= 3; y++)
		{
			for (int x = 1; x <= 3; x++)
			{
				product.At(x, y) = 0;
				for (int arg = 1; arg <= 3; arg++)
				{
					product.At(x, y) += aMatrix0.At(arg, y) * aMatrix1.At(x, arg);
				}
			}
		}
		return product;
	}

	template <typename T>
	void operator+=(Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 + aMatrix1;
	}

	template <typename T>
	void operator-=(Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 - aMatrix1;
	}

	template <typename T>
	void operator*=(Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 * aMatrix1;
	}

	template <typename T>
	bool operator==(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		for (int i = 0; i < 9; i++)
		{
			if (aMatrix0.myMatrix[i] != aMatrix1.myMatrix[i])
			{
				return false;
			}
		}
		return true;
	}


	//Vector operations

	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix33<T>& aMatrix)
	{	
		return
		{
			(aVector.x * aMatrix.At(1,1) + aVector.y * aMatrix.At(1,2) + aVector.z * aMatrix.At(1,3)),
			(aVector.x * aMatrix.At(2,1) + aVector.y * aMatrix.At(2,2) + aVector.z * aMatrix.At(2,3)),
			(aVector.x * aMatrix.At(3,1) + aVector.y * aMatrix.At(3,2) + aVector.z * aMatrix.At(3,3))
		};
	}

	template <typename T>
	void operator*=(Vector3<T>& aVector, const Matrix33<T>& aMatrix)
	{
		aVector = aVector*aMatrix;
	}

	template <typename T>
	Vector2<T> operator*(const Vector2<T>& aVector, const Matrix33<T>& aMatrix)
	{
		return
		{
			(aVector.x * aMatrix.At(3, 1) * aMatrix.At(1,1) + aVector.y * aMatrix.At(1,2) * aMatrix.At(3, 2) + aMatrix.At(1,3)),
			(aVector.x * aMatrix.At(3, 1) * aMatrix.At(2,1) + aVector.y * aMatrix.At(2,2) * aMatrix.At(3, 2) + aMatrix.At(2,3)),
		};
	}

	template <typename T>
	void operator*=(Vector2<T>& aVector, const Matrix33<T>& aMatrix)
	{
		aVector = aVector*aMatrix;
	}

	//Member functions

	template<typename T>
	inline Matrix33<T>::Matrix33()
		: myMatrix{
			1, 0, 0,
			0, 1, 0,
			0, 0, 1}
	{}

	template<typename T>
	inline Matrix33<T>::Matrix33(const Matrix33<T>& aMatrix)
	{
		memcpy(myMatrix, aMatrix.myMatrix, 9 * sizeof(T));
	}
	template<typename T>
	inline Matrix33<T>::Matrix33(const float aMatrix[9])
	{
		memcpy(myMatrix, aMatrix, 9 * sizeof(T));
	}

	template<typename T>
	inline Matrix33<T>::Matrix33(const std::initializer_list<T> aMatrix)
	{
		assert(aMatrix.size() == 9 && "Wrong number of arguments in Matrix33 constructor, takes 9 arguments!");
		auto listIterator = aMatrix.begin();
		for (int i = 0; i < 9; i++)
		{
			myMatrix[i] = *listIterator++;
		}
	}

	template<typename T>
	inline Matrix33<T>::Matrix33(const Matrix44<T>& aMatrix)
	:
		myMatrix{
			aMatrix.myMatrix[0], aMatrix.myMatrix[1], aMatrix.myMatrix[2],	//aMatrix.myMatrix[3],
			aMatrix.myMatrix[4], aMatrix.myMatrix[5], aMatrix.myMatrix[6],	//aMatrix.myMatrix[7],
			aMatrix.myMatrix[8], aMatrix.myMatrix[9], aMatrix.myMatrix[10]	//aMatrix.myMatrix[11],

			//aMatrix.myMatrix[12], aMatrix.myMatrix[13], aMatrix.myMatrix[14], aMatrix.myMatrix[15]
		}
	{}
	

	template<typename T>
	inline Matrix33<T>& Matrix33<T>::operator=(const Matrix33<T>& aMatrix)
	{
		memcpy(this->myMatrix, aMatrix.myMatrix, sizeof(T) * 9);
		return *this;
	}

	template<typename T>
	inline T & Matrix33<T>::operator[](const int aIndex)
	{
		return myMatrix[aIndex];
	}

	template<typename T>
	inline const T & Matrix33<T>::operator[](const int aIndex) const
	{
		return myMatrix[aIndex];
	}

	template<typename T>
	inline Matrix33<T> Matrix33<T>::CreateRotationRollPitchYaw(const Vector3<T> & aRotationInRadians)
	{
		return (CreateRotateAroundX(aRotationInRadians.x) * CreateRotateAroundY(aRotationInRadians.y) * CreateRotateAroundZ(aRotationInRadians.z));
	}

	template<typename T>
	inline Matrix33<T> Matrix33<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			1,	0,	0,
			0,	c,	s,
			0,	-s,	c
		};
	}

	template<typename T>
	inline Matrix33<T> Matrix33<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			c,	0,	-s,
			0,	1,	0,
			s,	0,	c
		};
	}

	template<typename T>
	inline Matrix33<T> Matrix33<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			c,	s,	0,
			-s,	c,	0,
			0,	0,	1
		};
	}

	template<typename T>
	inline Matrix33<T> Matrix33<T>::CreateRotateAroundAxis(const Vector3<T>& aAxis, T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			aAxis.x*aAxis.x*(1 - c) + c,			aAxis.x*aAxis.y*(1 - c) + aAxis.z*s,	aAxis.x*aAxis.z*(1 - c) + aAxis.y*s,
			aAxis.x*aAxis.y*(1 - c) + aAxis.z*s,	aAxis.y*aAxis.y*(1 - c) + c,			aAxis.y*aAxis.z*(1 - c) + aAxis.x*s,
			aAxis.x*aAxis.z*(1 - c) + aAxis.y*s,	aAxis.y*aAxis.z*(1 - c) + aAxis.x*s,	aAxis.z*aAxis.z*(1 - c) + c
		};
	}

	template<typename T>
	inline Matrix33<T> Matrix33<T>::CreateRotation(const Vector3<T>& aRotation)
	{
		return CreateRotateAroundZ(aRotation.z) * CreateRotateAroundX(aRotation.x) * CreateRotateAroundY(aRotation.y);
	}

	template<typename T>
	inline Matrix33<T> Matrix33<T>::Transpose(const Matrix33<T>& aMatrixToTranspose)
	{
		float transposedMatrix[9] = {
			aMatrixToTranspose.myMatrix[0], aMatrixToTranspose.myMatrix[3], aMatrixToTranspose.myMatrix[6],
			aMatrixToTranspose.myMatrix[1], aMatrixToTranspose.myMatrix[4], aMatrixToTranspose.myMatrix[7],
			aMatrixToTranspose.myMatrix[2], aMatrixToTranspose.myMatrix[5], aMatrixToTranspose.myMatrix[8]
		};
		return transposedMatrix;
	}

	template<typename T>
	inline T & Matrix33<T>::At(int aX, int aY)
	{
		assert(aX > 0 && aX <= 3 && "Tried to access invalid matrix element!");
		assert(aY > 0 && aY <= 3 && "Tried to access invalid matrix element!");
		return myMatrix[(aY - 1) * 3 + (aX - 1)];
	}

	template<typename T>
	inline const T & Matrix33<T>::At(int aX, int aY) const
	{
		assert(aX > 0 && aX <= 3 && "Tried to access invalid matrix element!");
		assert(aY > 0 && aY <= 3 && "Tried to access invalid matrix element!");
		return myMatrix[(aY - 1) * 3 + (aX - 1)];
	}
}

#pragma warning(pop)
