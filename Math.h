#pragma once
#define EPSILON 0.00001f
#define POW2(aPow) (1 << aPow)

namespace CommonUtilities
{
	template <typename T>
	T Sqrt(const T aSquare)
	{
		return (T)sqrt(aSquare);
	}

	template <typename T>
	T InvSqrt(const T aSquare)
	{
		return (T)1 / Sqrt(aSquare);
	}

	template <typename T>
	T Sin(const T aScalar)
	{
		return (T)sin(aScalar);
	}

	template <typename T>
	T Cos(const T aScalar)
	{
		return (T)cos(aScalar);
	}

	template <typename T>
	T Tan(const T aScalar)
	{
		return (T)tan(aScalar);
	}

	template <typename T>
	T ASin(const T aScalar)
	{
		return (T)asin(aScalar);
	}

	template <typename T>
	T ACos(const T aScalar)
	{
		return (T)acos(aScalar);
	}

	template <typename T>
	T ATan(const T aScalar)
	{
		return (T)atan(aScalar);
	}

	template <typename T>
	T ATan2(const T aScalar1, const T aScalar2)
	{
		return (T)atan2f((T)aScalar1, (T)aScalar2);
	}

	template<typename T>
	inline T Lerp(const T & aStart, const T & aEnd, float aPercentage)
	{
		return aStart + (aEnd - aStart) * aPercentage;
	}

	template<typename T>
	inline T NLerp(const T& aStart, const T& aEnd, float aPercentage)
	{
		return Lerp(aStart, aEnd, aPercentage).GetNormalized();
	}

	template<typename T>
	inline T Clamp(const T& aValue, const T& aMinimum, const T& aMaximum)
	{
		return ((aValue < aMinimum)) ? aMinimum : ((aValue > aMaximum) ? aMaximum : aValue);
	}

	template<typename T>
	inline T Ceil(const T& aValue)
	{
		return (T)ceilf((T)aValue);
	}

	template <typename T>
	inline bool Equals(const T& aValue1, const T& aValue2, const T aEpsilon = EPSILON)
	{
		return (aValue1 + aEpsilon >= aValue2) && (aValue1 - aEpsilon <= aValue2);
	}

	__forceinline float Clamp(float aVal, float aLowerlimit, float aUpperlimit)
	{
		return CU_MIN(CU_MAX(aVal, aLowerlimit), aUpperlimit);
	}

	__forceinline float Smoothstep(float aEdge0, float aEdge1, float aVal)
	{
		float val = Clamp((aVal - aEdge0) / (aEdge1 - aEdge0), 0.f, 1.f);

		return val * val * (3 - 2 * val);
	}

	enum EAxis : uint8
	{
		EAxis_X = 0,
		EAxis_Y,
		EAxis_Z,
	};

	uint8 CreateRotationOrder(EAxis aAxis1, EAxis aAxis2, EAxis aAxis3);

}