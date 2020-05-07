#pragma once
#pragma warning(push)
#pragma warning(disable : 4201)

namespace CommonUtilities
{
	template <class T>
	struct Vector4
	{
	public:
		union
		{
			struct
			{
				T x, y, z, w;
			};
		};

		//Creates a null-vector
		Vector4<T>();

		//Creates a vector (aX, aY, aZ)
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);

		//Creates a vector (aVector3.x, aVector3.y, aVector3.z, aW)
		Vector4<T>(const Vector3<T>& aVector3, const T& aW);

		Vector4<T>(const T*& aXYZW); //must be size 4

		//Copy constructor (compiler generated)
		Vector4<T>(const Vector4<T>& aVector) = default;

		Vector4<T>(const Color & aColour);

		//Assignment operator (compiler generated)
		Vector4<T>& operator=(const Vector4<T>& aVector) = default;

		//Destructor (compiler generated)
		~Vector4<T>() = default;

		//Returns the squared length of the vector
		T Length2() const;

		//Returns the length of the vector
		T Length() const;

		//Returns a normalized copy of this
		Vector4<T> GetNormalized() const;

		//Normalizes the vector
		void Normalize();

		//Returns the dot product of this and aVector
		T Dot(const Vector4<T>& aVector) const;

		template <typename T2>
		Vector4<T2> AsType() const;

		//Returns a vector3 with the xyz values of the vector
		const Vector3<T> & ToVector3() const;
		const Vector2<T> & ToVector2() const;

		T& operator[](const int aIndex);
		const T& operator[](const int aIndex) const;
		Vector4<T> operator-() const;
	};

	typedef Vector4<float> Vector4f;
	typedef Vector4<unsigned> Vector4ui;

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return Vector4<T>(
			aVector0.x + aVector1.x,
			aVector0.y + aVector1.y,
			aVector0.z + aVector1.z,
			aVector0.w + aVector1.w
			);
	}

	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return Vector4<T>(
			aVector0.x - aVector1.x,
			aVector0.y - aVector1.y,
			aVector0.z - aVector1.z,
			aVector0.w - aVector1.w
			);
	}

	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return Vector4<T>(
			aVector0.x * aVector1.x,
			aVector0.y * aVector1.y,
			aVector0.z * aVector1.z,
			aVector0.w * aVector1.w
			);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		return Vector4<T>(
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar,
			aVector.w * aScalar
			);
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return Vector4<T>(
			aVector.x * aScalar,
			aVector.y * aScalar,
			aVector.z * aScalar,
			aVector.w * aScalar
			);
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		return Vector4<T>(
			aVector.x / aScalar,
			aVector.y / aScalar,
			aVector.z / aScalar,
			aVector.w / aScalar
			);
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> Vector4<T> operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
		return aVector0;
	}

	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> Vector4<T> operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
		return aVector0;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> Vector4<T> operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
		return aVector;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> Vector4<T> operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
		aVector.w /= aScalar;
		return aVector;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> bool operator==(const Vector4<T> & aVector0, const Vector4<T> & aVector1)
	{
		return((aVector0.x == aVector1.x)
			&& (aVector0.y == aVector1.y)
			&& (aVector0.z == aVector1.z)
			&& (aVector0.w == aVector1.w));
	}

	template<class T> inline Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template<class T> inline Vector4<T>::Vector4(const T & aX, const T & aY, const T & aZ, const T & aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template<class T> inline Vector4<T>::Vector4(const Vector3<T>& aVector3, const T& aW)
	{
		x = aVector3.x;
		y = aVector3.y;
		z = aVector3.z;
		w = aW;
	}

	template<class T>
	inline Vector4<T>::Vector4(const T*& aXYZW)
	{
		x = aXYZW[0];
		y = aXYZW[1];
		z = aXYZW[2];
		w = aXYZW[3];
	}

	template<class T>
	inline Vector4<T>::Vector4(const Color & aColour)
	{
		x = aColour.myR;
		y = aColour.myG;
		z = aColour.myB;
		w = aColour.myA;
	}

	template<class T> inline T Vector4<T>::Length2() const
	{
		return (x*x + y*y + z*z + w*w);
	}

	template<class T> inline T Vector4<T>::Length() const
	{
		return sqrt(Length2());
	}

	template<class T> inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		float length2 = Length2();
		if (length2 == 0)
		{
			return *this;
		}
		return (*this) / sqrt(length2);
	}

	template<class T> inline void Vector4<T>::Normalize()
	{
		(*this) = this->GetNormalized();
	}

	template<class T> inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return x*aVector.x + y*aVector.y + z*aVector.z + w*aVector.w;
	}

	template<class T>
	template <typename T2>
	inline Vector4<T2> Vector4<T>::AsType() const
	{
		return {
			static_cast<T2>(x),
			static_cast<T2>(y),
			static_cast<T2>(z),
			static_cast<T2>(w)
		};
	}

	template<class T>
	inline const Vector3<T>& Vector4<T>::ToVector3() const
	{
		return reinterpret_cast<const Vector3<T>&>(x);
	}
	template<class T>
	inline const Vector2<T>& Vector4<T>::ToVector2() const
	{
		return reinterpret_cast<const Vector2<T>&>(x);
	}
	template<class T>
	inline T & Vector4<T>::operator[](const int aIndex)
	{
		assert(aIndex >= 0 && aIndex < 4);
		return *((&x) + aIndex);
	}
	template<class T>
	inline const T & Vector4<T>::operator[](const int aIndex) const
	{
		assert(aIndex >= 0 && aIndex < 4);
		return *((&x) + aIndex);
	}
	template<class T>
	inline Vector4<T> Vector4<T>::operator-() const
	{
		return Vector4<T>(-x, -y, -z, -w);
	}
}
#pragma warning(pop)