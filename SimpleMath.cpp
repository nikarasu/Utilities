#include "stdafx.h"
#include "SimpleMath.h"
#include <random>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

float CommonUtilities::RandomFloat(float aMin, float aMax)
{
	int val = rand() % RAND_MAX;
	return aMin + (((1.f*val) / (RAND_MAX * 1.f)) * (aMax - aMin));
}

int CommonUtilities::RandomInt(int aMin, int aMax)
{	
	return (rand() % ((aMax - aMin) + 1)) + aMin;
}

bool CommonUtilities::GetScreenPosFromWorldPos(const CU::Vector3f & aWorldPos, const CU::Matrix44f & aView, const CU::Matrix44f & aProjection, CU::Vector2f & outPos)
{
	CU::Vector4f projectedPos = (aWorldPos.ToVector4(1.f) * aView.GetSlowInverse()) * aProjection;

	CU::Vector2f returnPos = { (projectedPos.x + 1.f) / 2.f, (1.f - (projectedPos.y + 1.f) / 2.f) };
	returnPos /= projectedPos.z;
	returnPos.x += 0.5f;
	returnPos.y += 0.5f;

	if (projectedPos.z >= 0.f)
	{
		outPos = returnPos;
		return true;
	}
	return false;
}
