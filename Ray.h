#pragma once
#include "Vector3.h"
namespace CommonUtilities
{
	template<typename T>
	class Ray
	{
	public:
		Ray();
		Ray(const Vector3<T>& aPoint, const Vector3<T>& aDirection);
		const Vector3<T> & GetPoint() const;
		const Vector3<T> & GetDirection() const;
		Vector3<T> GetClosestPoint(const Vector3<T> & aPoint);

	private:
		Vector3<T> myPoint;
		Vector3<T> myDirection;
	};

	template<typename T>
	inline Ray<T>::Ray()
	{
		myPoint = { 0, 0, 0 };
		myDirection = { 0, 0, 1 };
	}

	template<typename T>
	inline Ray<T>::Ray(const Vector3<T>& aPoint, const Vector3<T>& aDirection)
	{
		myPoint = aPoint;
		myDirection = aDirection.GetNormalized();
	}

	template<typename T>
	inline const Vector3<T> & Ray<T>::GetPoint() const
	{
		return myPoint;
	}

	template<typename T>
	inline const Vector3<T> & Ray<T>::GetDirection() const
	{
		return myDirection;
	}

	template<typename T>
	inline Vector3<T> Ray<T>::GetClosestPoint(const Vector3<T>& aPoint)
	{
		return myPoint + myDirection * (aPoint - myPoint).Dot(myDirection);
	}
}

namespace CU = CommonUtilities;