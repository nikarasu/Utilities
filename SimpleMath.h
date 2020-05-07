#pragma once

namespace CommonUtilities
{
	float RandomFloat(float aMin, float aMax);
	int RandomInt(int aMin, int aMax);

	template<typename T>
	T Random(T aMin, T aMax)
	{
		float percent = rand() / static_cast<float>(RAND_MAX);
		float valueAsFloat = aMin + percent * (aMax - aMin);
		return static_cast<T>(valueAsFloat);
	}

	template<typename T>
	Vector2<T> RandomVector2(Vector2<T> aMin, Vector2<T> aMax)
	{
		return Vector2<T>(Random(aMin.x, aMax.x), Random(aMin.y, aMax.y));
	}

	template<typename T>
	Vector3<T> RandomVector3(Vector3<T> aMin, Vector3<T> aMax)
	{
		return Vector3<T>(Random(aMin.x, aMax.x), Random(aMin.y, aMax.y), Random(aMin.z, aMax.z));
	}

	template<typename T>
	Vector4<T> RandomVector4(Vector4<T> aMin, Vector4<T> aMax)
	{
		return Vector4<T>(Random(aMin.x, aMax.x), Random(aMin.y, aMax.y), Random(aMin.z, aMax.z), Random(aMin.w, aMax.w));
	}

	//Slerp is a template but unless you know what you are doing restrain from othen than Vector3f
	template<typename T>
	inline T Slerp(const T& aStart, const T& aEnd, float aPercentage)
	{  
		// Dot product - the cosine of the angle between 2 vectors.
		float dot = aStart.Dot(aEnd);
		// Clamp it to be in the range of Acos()
		// This may be unnecessary, but floating point
		// precision can be a fickle mistress.
		CU::Clamp(dot, -1.0f, 1.0f);
		// Acos(dot) returns the angle between start and end,
		// And multiplying that by percent returns the angle between
		// start and the final result.
		float theta = acos(dot)*aPercentage;
		CU::Vector3f RelativeVec = aEnd - aStart * dot;

		RelativeVec.Normalize();     // Orthonormal basis
		return ( (aStart * cos(theta) ) + ( RelativeVec * sin(theta) ) );
	}

	bool GetScreenPosFromWorldPos(const Vector3f & aWorldPos, const Matrix44f & aView, const Matrix44f & aProjection, Vector2f & outPos);
}

namespace CU = CommonUtilities;