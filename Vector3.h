#pragma once

namespace CommonUtilities
{
	template <class T>
	struct Vector3
	{
	public:
		T x;
		T y;
		T z;

		Vector3<T>();
		Vector3<T>(const T& aX, const T& aY, const T& aZ);
		Vector3<T>(const Vector2<T>& aVector, float aZ) { x = aVector.x; y = aVector.y; z = aZ; }
		explicit Vector3<T>(T aVal) { x = aVal; y = aVal; z = aVal; }

		Vector3<T> GetAnyPerpendicular() const;

		bool Approximately(const Vector3<T> & aOther) const;

		//Returns the squared length of the vector
		T Length2() const;

		//Returns the length of the vector
		T Length() const;

		//Returns a normalized copy of this
		Vector3<T> GetNormalized() const;

		//Normalizes the vector
		void Normalize();

		//Returns a truncated copy of this
		Vector3<T> GetTruncated(T aLength) const;

		//Truncates the vector at a length
		void Trunc(T aLength);

		//Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const;

		//Returns the cross product of this and aVector
		Vector3<T> Cross(const Vector3<T>& aVector) const;

		Vector2<T> ToVector2() const;
		Vector2<T> ToVector2XZ() const;
		Vector2<T> ToVector2XY() const;
		Vector4<T> ToVector4(T aW) const;

		template <typename T2>
		Vector3<T2> AsType() const;

		T& operator[](const int aIndex);
		const T& operator[](const int aIndex) const;
		Vector3<T> operator-() const;

		void Add(const Vector3<T> & aVec);
		void Sub(const Vector3<T> & aVec);
		void Mul(const float aFloat);
		void Div(const float aFloat);
	};

	template<class T>
	template <typename T2>
	inline Vector3<T2> Vector3<T>::AsType() const
	{
		return{
			static_cast<T2>(x),
			static_cast<T2>(y),
			static_cast<T2>(z)
		};
	}
	typedef Vector3<float> Vector3f;
	typedef Vector3<unsigned> Vector3ui;

	//Returns the vector sum of aVector0 and aVector1
	template <class T>
	inline Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(
			aVector0.x + aVector1.x,
			aVector0.y + aVector1.y,
			aVector0.z + aVector1.z
			);
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T>
	inline Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(
			aVector0.x - aVector1.x,
			aVector0.y - aVector1.y,
			aVector0.z - aVector1.z
			);
	}

	//Returns the vector sum of aVector0 and aVector1
	template <class T>
	inline Vector3<T> operator*(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(
			aVector0.x * aVector1.x,
			aVector0.y * aVector1.y,
			aVector0.z * aVector1.z
			);
	}

	template <class T>
	inline Vector3<T> operator/(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(
			aVector0.x / aVector1.x,
			aVector0.y / aVector1.y,
			aVector0.z / aVector1.z
			);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	inline Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>(
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar	
			);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	inline Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return Vector3<T>(
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar
			);
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T>
	inline Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>(
			aVector.x / aScalar,
			aVector.y / aScalar,
			aVector.z / aScalar
			);
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T>
	inline void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T>
	inline void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	//Equivalent to setting aVector to (aVector * aVector)
	template <class T>
	inline void operator*=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x *= aVector1.x;
		aVector0.y *= aVector1.y;
		aVector0.z *= aVector1.z;
	}


	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T>
	inline void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T>
	inline void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
	}

	
	template <class T>
	inline bool operator==(const Vector3<T>& aVectorFirst, const Vector3<T>& aVectorSecond)
	{
		return	(aVectorFirst.x == aVectorSecond.x && aVectorFirst.y == aVectorSecond.y && aVectorFirst.z == aVectorSecond.z);
	}

	template <class T>
	inline bool operator!=(const Vector3<T>& aVectorFirst, const Vector3<T>& aVectorSecond)
	{
		return	(aVectorFirst == aVectorSecond) == false;
	}

	template<class T> inline Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	template<class T> inline Vector3<T>::Vector3(const T & aX, const T & aY, const T & aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<class T> inline Vector3<T> Vector3<T>::GetAnyPerpendicular() const
	{
		return {-y, z, x};
	}

	template<class T> inline T Vector3<T>::Length2() const
	{
		return (x*x + y*y + z*z);
	}

	template<class T> inline T Vector3<T>::Length() const
	{
		return sqrt(Length2());
	}

	template<class T> inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		float length2 = Length2();
		if (length2 == 0)
		{
			return *this;
		}
		return (*this) / sqrt(length2);
	}

	template<class T> inline void Vector3<T>::Normalize()
	{
		(*this) = this->GetNormalized();
	}

	template<class T>
	inline Vector3<T> Vector3<T>::GetTruncated(T aLength) const
	{
		Vector3<T> vec(*this);
		vec.Trunc(aLength);
		return vec;
	}
	
	template<class T>
	inline void Vector3<T>::Trunc(T aLength)
	{
		if (Length2() > (aLength * aLength))
		{
			*this = GetNormalized() * aLength;
		}
	}

	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return x*aVector.x + y*aVector.y + z*aVector.z;
	}

	template<class T>
	inline bool Vector3<T>::Approximately(const Vector3<T> &aOther) const
	{
		bool aX = fabs(x - aOther.x) < FLT_EPSILON;
		bool aY = fabs(y - aOther.y) < FLT_EPSILON;
		bool aZ = fabs(z - aOther.z) < FLT_EPSILON;

		return (aX == aY && aZ == aX);
	}

	template<class T> inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		return Vector3<T>(
			y*aVector.z - z*aVector.y,
			z*aVector.x - x*aVector.z,
			x*aVector.y - y*aVector.x
		);
	}

	template<class T>
	inline Vector2<T> Vector3<T>::ToVector2() const
	{
		return Vector2<T>(x, y);
	}
	template<class T>
	inline Vector2<T> Vector3<T>::ToVector2XZ() const
	{
		return Vector2<T>(x, z);
	}
	template<class T>
	inline Vector2<T> Vector3<T>::ToVector2XY() const
	{
		return Vector2<T>(x, y);
	}
	template<class T>
	inline Vector4<T> Vector3<T>::ToVector4(T aW) const
	{
		return Vector4<T>(x, y, z, aW);
	}
	template<class T>
	inline T & Vector3<T>::operator[](const int aIndex)
	{
		assert(aIndex >= 0 && aIndex < 3);
		return *((&x) + aIndex);
	}
	template<class T>
	inline const T & Vector3<T>::operator[](const int aIndex) const
	{
		assert(aIndex >= 0 && aIndex < 3);
		return *((&x) + aIndex);
	}
	template <class T>
	inline Vector3<T> Vector3<T>::operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}
	template<class T>
	inline void Vector3<T>::Add(const Vector3<T> & aVec)
	{
		*this += aVec;
	}
	template<class T>
	inline void Vector3<T>::Sub(const Vector3<T> & aVec)
	{
		*this -= aVec;
	}
	template<class T>
	inline void Vector3<T>::Mul(const float aFloat)
	{
		*this *= aFloat;
	}
	template<class T>
	inline void Vector3<T>::Div(const float aFloat)
	{
		*this /= aFloat;
	}
}