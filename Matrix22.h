#pragma once
#include "Vector2.h"
#include "Matrix33.h"
#include <assert.h>
#include <initializer_list>

namespace CommonUtilities
{
	template <typename T>
	class Matrix22
	{
	public:
		Matrix22<T>();
		Matrix22<T>(const Matrix22<T>& aMatrix);
		Matrix22<T>(const Matrix33<T>& aMatrix);
		Matrix22<T>(const float aMatrix[4]);
		Matrix22<T>(const std::initializer_list<T> aMatrix);

		Matrix22<T>& operator=(const Matrix22<T>& aMatrix);
		T& operator[](const int aIndex);
		const T& operator[](const int aIndex) const;

		static Matrix22<T> CreateRotation(T aAngleInRadians);
		static Matrix22<T> Transpose(const Matrix22<T>& aMatrixToTranspose);

		T& At(int aX, int aY);
		const T& At(int aX, int aY) const;

		T myMatrix[4];
	};

	typedef Matrix22<float> Matrix22f;

	//operators

	template <typename T>
	Matrix22<T> operator+(const Matrix22<T>& aMatrix0, const Matrix22<T>& aMatrix1)
	{
		Matrix22<T> sum;
		for (int i = 0; i < 4; i++)
		{
			sum.myMatrix[i] = aMatrix0.myMatrix[i] + aMatrix1.myMatrix[i];
		}
		return sum;
	}

	template <typename T>
	Matrix22<T> operator-(const Matrix22<T>& aMatrix0, const Matrix22<T>& aMatrix1)
	{
		Matrix22<T> difference;
		for (int i = 0; i < 4; i++)
		{
			difference.myMatrix[i] = aMatrix0.myMatrix[i] - aMatrix1.myMatrix[i];
		}
		return difference;
	}

	template <typename T>
	Matrix22<T> operator*(const Matrix22<T>& aMatrix0, const Matrix22<T>& aMatrix1)
	{
		Matrix22<T> product;
		for (int y = 1; y <= 2; y++)
		{
			for (int x = 1; x <= 2; x++)
			{
				product.At(x, y) = 0;
				for (int arg = 1; arg <= 2; arg++)
				{
					product.At(x, y) += aMatrix0.At(arg, y) * aMatrix1.At(x, arg);
				}
			}
		}
		return product;
	}

	template <typename T>
	void operator+=(Matrix22<T>& aMatrix0, const Matrix22<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 + aMatrix1;
	}

	template <typename T>
	void operator-=(Matrix22<T>& aMatrix0, const Matrix22<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 - aMatrix1;
	}

	template <typename T>
	void operator*=(Matrix22<T>& aMatrix0, const Matrix22<T>& aMatrix1)
	{
		aMatrix0 = aMatrix0 * aMatrix1;
	}

	template <typename T>
	bool operator==(const Matrix22<T>& aMatrix0, const Matrix22<T>& aMatrix1)
	{
		for (int i = 0; i < 4; i++)
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
	Vector2<T> operator*(const Vector2<T>& aVector, const Matrix22<T>& aMatrix)
	{
		return
		{
			(aVector.x * aMatrix.At(1,1) + aVector.y * aMatrix.At(1,2)),
			(aVector.x * aMatrix.At(2,1) + aVector.y * aMatrix.At(2,2))
		};
	}

	template <typename T>
	void operator*=(Vector2<T>& aVector, const Matrix22<T>& aMatrix)
	{
		aVector = aVector*aMatrix;
	}

	//Member functions

	template<typename T>
	inline Matrix22<T>::Matrix22()
		: myMatrix{
		1, 0,
		0, 1
	}
	{}

	template<typename T>
	inline Matrix22<T>::Matrix22(const Matrix22<T>& aMatrix)
	{
		memcpy(myMatrix, aMatrix.myMatrix, 4 * sizeof(T));
	}
	template<typename T>
	inline Matrix22<T>::Matrix22(const float aMatrix[4])
	{
		memcpy(myMatrix, aMatrix, 4 * sizeof(T));
	}

	template<typename T>
	inline Matrix22<T>::Matrix22(const std::initializer_list<T> aMatrix)
	{
		assert(aMatrix.size() == 4 && "Wrong number of arguments in Matrix22 constructor, takes 4 arguments!");
		auto listIterator = aMatrix.begin();
		for (int i = 0; i < 4; i++)
		{
			myMatrix[i] = *listIterator++;
		}
	}

	template<typename T>
	inline Matrix22<T>::Matrix22(const Matrix33<T>& aMatrix)
		:
		myMatrix{
		aMatrix.myMatrix[0], aMatrix.myMatrix[1],	//aMatrix.myMatrix[2],
		aMatrix.myMatrix[3], aMatrix.myMatrix[4]	// aMatrix.myMatrix[5],
	}	//aMatrix.myMatrix[6], aMatrix.myMatrix[7], aMatrix.myMatrix[8]
	{}

	template<typename T>
	inline Matrix22<T>& Matrix22<T>::operator=(const Matrix22<T>& aMatrix)
	{
		memcpy(this->myMatrix, aMatrix.myMatrix, sizeof(T) * 4);
		return *this;
	}

	template<typename T>
	inline T & Matrix22<T>::operator[](const int aIndex)
	{
		return myMatrix[aIndex];
	}

	template<typename T>
	inline const T & Matrix22<T>::operator[](const int aIndex) const
	{
		return myMatrix[aIndex];
	}

	template<typename T>
	inline Matrix22<T> Matrix22<T>::CreateRotation(T aAngleInRadians)
	{
		T c = static_cast<T>(std::cos(static_cast<double>(aAngleInRadians)));
		T s = static_cast<T>(std::sin(static_cast<double>(aAngleInRadians)));
		return
		{
			c,	s,
			-s,	c
		};
	}

	template<typename T>
	inline Matrix22<T> Matrix22<T>::Transpose(const Matrix22<T>& aMatrixToTranspose)
	{
		float transposedMatrix[4] = {
			aMatrixToTranspose.myMatrix[0], aMatrixToTranspose.myMatrix[2],
			aMatrixToTranspose.myMatrix[1], aMatrixToTranspose.myMatrix[3]
		};
		return transposedMatrix;
	}

	template<typename T>
	inline T & Matrix22<T>::At(int aX, int aY)
	{
		assert(aX > 0 && aX <= 2 && "Tried to access invalid matrix element!");
		assert(aY > 0 && aY <= 2 && "Tried to access invalid matrix element!");
		return myMatrix[(aY - 1) * 2 + (aX - 1)];
	}

	template<typename T>
	inline const T & Matrix22<T>::At(int aX, int aY) const
	{
		assert(aX > 0 && aX <= 2 && "Tried to access invalid matrix element!");
		assert(aY > 0 && aY <= 2 && "Tried to access invalid matrix element!");
		return myMatrix[(aY - 1) * 2 + (aX - 1)];
	}
}