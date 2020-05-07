#pragma once

namespace CommonUtilities
{
	template <class T>
	struct Vector3;

	template <class T>
	struct Vector4;

	template <class T>
	struct Vector2
	{
	public:
		T x;
		T y;

		//Creates an empty vector
		Vector2<T>();

		//Creates a vector (aX, aY)
		Vector2<T>(const T& aX, const T& aY);

		//Copy constructor
		//Default keyword states compiler generated version, don't need to write a body
		Vector2<T>(const Vector2<T>& aVector) = default;

		//Explicit stops compiler from implicit conversion
		explicit Vector2<T>(const T& aVal) { x = y = aVal; }

		//Assignment operator (compiler generated)
		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;

		//Destructor (compiler generated)
		~Vector2<T>() = default;

		//Returns the squared length of the vector
		T Length2() const;

		//Returns the length of the vector
		T Length() const;

		//Returns a normalized copy of this
		Vector2<T> GetNormalized() const;

		//Normalizes the vector
		void Normalize();

		bool InRange(const Vector2<T>& aVector0, const Vector2<T> aVector1);

		//Returns the dot product of this and aVector
		T Dot(const Vector2<T>& aVector) const;

		Vector3<T> ToVector3(float aZ) const;
		Vector3<T> ToVector3XZ(float aY) const;
		Vector4<T> ToVector4(float aZ, float aW) const;

		void Trunc(const T aLength);

		template <typename T2>
		Vector2<T2> AsType() const
		{
			return { static_cast<T2>(x), static_cast<T2>(y) };
		}

		Vector2 operator-() const
		{
			Vector2<T> newVector;

			newVector.x = -x;
			newVector.y = -y;

			return newVector;
		}

		T& operator[](const int aIndex);
		const T& operator[](const int aIndex) const;
	};

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(
			aVector0.x + aVector1.x,
			aVector0.y + aVector1.y
			);
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(
			aVector0.x - aVector1.x,
			aVector0.y - aVector1.y
			);
	}

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(
			aVector0.x * aVector1.x,
			aVector0.y * aVector1.y
			);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T>(
			aVector.x * aScalar,
			aVector.y * aScalar
			);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return Vector2<T>(
			aVector.x * aScalar,	//x
			aVector.y * aScalar
			);
	}

	//Returns the vector aVector0 divided by aVector1
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(
			aVector0.x / aVector1.x,
			aVector0.y / aVector1.y
			);
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T>(
			aVector.x / aScalar,
			aVector.y / aScalar
			);
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}

	//Equivalent to setting aVector0 to (aVector0 * aVector1)
	template <class T> void operator*=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x *= aVector1.x;
		aVector0.y *= aVector1.y;
	}

	//Equivalent to setting aVector0 to (aVector0 / aVector1)
	template <class T> void operator/=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x /= aVector1.x;
		aVector0.y /= aVector1.y;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
	}

	//Comparison
	template <class T> bool operator==(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return(aVector0.x == aVector1.x && aVector0.y == aVector1.y);
	}

	//Comparison
	template <class T> bool operator!=(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return (aVector0.x != aVector1.x || aVector0.y != aVector1.y);
	}

	template<class T> inline Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template<class T> inline Vector2<T>::Vector2(const T & aX, const T & aY)
	{
		x = aX;
		y = aY;
	}

	template<class T> inline T Vector2<T>::Length2() const
	{
		return x*x + y*y;
	}

	template<class T> inline T Vector2<T>::Length() const
	{
		return sqrt(Length2());
	}

	template<class T> inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		float length2 = Length2();
		if (length2 == 0)
		{
			return *this;
		}
		return (*this) / sqrt(length2);
	}

	template<class T> inline void Vector2<T>::Normalize()
	{
		(*this) = this->GetNormalized();
	}

	template<class T>
	inline bool Vector2<T>::InRange(const Vector2<T>& aVector0, const Vector2<T> aVector1)
	{
		if (((x > aVector0.x && x < aVector1.x) || (x > aVector1.x && x < aVector0.x))
		&& ((y > aVector0.y && y < aVector1.y) || (y > aVector1.y && y < aVector0.y)))
		{
			return true;
		}
		return false;
	}

	template<class T> inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return x*aVector.x + y*aVector.y;
	}

	template<class T>
	inline Vector3<T> Vector2<T>::ToVector3(float aZ) const
	{
		return Vector3<T>(x, y, aZ);
	}

	template<class T>
	inline Vector3<T> Vector2<T>::ToVector3XZ(float aY) const
	{
		return Vector3<T>(x, aY, y);
	}

	template<class T>
	inline Vector4<T> Vector2<T>::ToVector4(float aZ, float aW) const
	{
		return Vector4<T>(x, y, aZ, aW);
	}

	template<typename T>
	inline void Vector2<T>::Trunc(const T aLength)
	{
		if (Length2() > aLength * aLength)
		{
			*this = GetNormalized() * aLength;
		}
	}

	template<class T> inline T DistanceBetween(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return (aVector0 - aVector1).Length();
	}
	template<class T>
	inline T& Vector2<T>::operator[](const int aIndex)
	{
		assert(aIndex >= 0 && aIndex < 2);
		return *((&x) + aIndex);
	}
	template<class T>
	inline const T& Vector2<T>::operator[](const int aIndex) const
	{
		assert(aIndex >= 0 && aIndex < 2);
		return *((&x) + aIndex);
	}
}