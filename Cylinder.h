#pragma once
#include "Vector3.h"
namespace CommonUtilities
{
	template<typename T>
	class Cylinder
	{
	public:
		Cylinder();
		Cylinder(const Vector3<T>& aPoint, const T & aHeight, const T & aRadius, const Vector3<T>& aDirection = Vector3<T>(0, 1, 0));
		const Vector3<T> & GetPoint() const;
		const Vector3<T> & GetDirection() const;
		const T & GetHeight() const;
		const T & GetRadius() const;

		void SetPoint(const Vector3<T>& aPoint);

	private:
		Vector3<T> myPoint;
		Vector3<T> myDirection;
		T myHeight;
		T myRadius;
	};

	template<typename T>
	inline Cylinder<T>::Cylinder()
	{
		myPoint = { 0, 0, 0 };
		myDirection = { 0, 0, 1 };
		myHeight = 1.f;
		myRadius = 0.5f;
	}

	template<typename T>
	inline Cylinder<T>::Cylinder(const Vector3<T>& aPoint, const T & aHeight, const T & aRadius, const Vector3<T>& aDirection)
	{
		myPoint = aPoint;
		myDirection = aDirection.GetNormalized();
		myHeight = aHeight;
		myRadius = aRadius;
	}

	template<typename T>
	inline const Vector3<T> & Cylinder<T>::GetPoint() const
	{
		return myPoint;
	}

	template<typename T>
	inline const Vector3<T> & Cylinder<T>::GetDirection() const
	{
		return myDirection;
	}

	template<typename T>
	inline const T & Cylinder<T>::GetHeight() const
	{
		return myHeight;
	}

	template<typename T>
	inline const T & Cylinder<T>::GetRadius() const
	{
		return myRadius;
	}

	template<typename T>
	inline void Cylinder<T>::SetPoint(const Vector3<T>& aPoint)
	{
		myPoint = aPoint;
	}
		
}

namespace CU = CommonUtilities;