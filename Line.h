#pragma once
#include "Vector3.h"
namespace CommonUtilities
{
	template<typename T>
	class Line
	{
	public:
		Line();
		Line(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1);
		void InitWith2Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1);
		void InitWithPointAndDirection(const Vector3<T>& aPoint, const Vector3<T>& aDirection);
		const Vector3<T> & GetPoint0() const;
		const Vector3<T> & GetPoint1() const;
		Vector3<T> GetDirection() const;
		Vector3<T> GetClosestPointOnSegment(const Vector3<T> & aPoint, float * distOut = nullptr) const;
		Vector3<T> GetClosestPointOnLine(const Vector3<T> & aPoint, float * distOut = nullptr) const;
		T GetLength() const;

	private:
		Vector3<T> myPoint0;
		Vector3<T> myPoint1;
	};

	template<typename T>
	inline Line<T>::Line()
	{
		myPoint0 = { 0, 0, 0 };
		myPoint1 = { 0, 0, 0 };
	}
	
	template<typename T>
	inline Line<T>::Line(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1)
	{
		InitWith2Points(aPoint0, aPoint1);
	}
	
	template<typename T>
	inline void Line<T>::InitWith2Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1)
	{
		myPoint0 = aPoint0;
		myPoint1 = aPoint1;
	}
	
	template<typename T>
	inline void Line<T>::InitWithPointAndDirection(const Vector3<T>& aPoint, const Vector3<T>& aDirection)
	{
		myPoint0 = aPoint;
		myPoint1 = myPoint0 + aDirection.GetNormalized();
	}

	template<typename T>
	inline const Vector3<T>& Line<T>::GetPoint0() const
	{
		return myPoint0;
	}

	template<typename T>
	inline const Vector3<T>& Line<T>::GetPoint1() const
	{
		return myPoint1;
	}

	template<typename T>
	inline Vector3<T> Line<T>::GetDirection() const
	{
		return (myPoint1 - myPoint0).GetNormalized();
	}

	template<typename T>
	inline Vector3<T> Line<T>::GetClosestPointOnSegment(const Vector3<T>& aPoint, float * distOut) const
	{
		Vector3<T> u = GetDirection();
		Vector3<T> v = aPoint - myPoint0;
		float w = u.Dot(v);

		w = CU_MAX(w, 0.f);
		w = CU_MIN(w, (myPoint1 - myPoint0).Length());

		if (distOut != nullptr)
		{
			*distOut = w;
		}

		return myPoint0 + u * w;
	}

	template<typename T>
	inline Vector3<T> Line<T>::GetClosestPointOnLine(const Vector3<T>& aPoint, float * distOut) const
	{
		Vector3<T> u = GetDirection();
		Vector3<T> v = aPoint - myPoint0;
		float w = u.Dot(v);

// 		w = MAX(w, 0.f);
// 		w = MIN(w, (myPoint1 - myPoint0).Length());

		if (distOut != nullptr)
		{
			*distOut = w;
		}

		return myPoint0 + u * w;
	}

	template<typename T>
	inline T Line<T>::GetLength() const
	{
		return (myPoint1 - myPoint0).Length();
	}
}

namespace CU = CommonUtilities;