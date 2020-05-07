#pragma once
#include "Vector2.h"

namespace CommonUtilities
{
	template <typename T>
	struct Rect_t
	{
		Vector2<T> myMin;
		Vector2<T> myMax;
	};
	typedef Rect_t<float> Rect;

	template <typename T>
	Vector2<T> GetRectSize(const Rect_t<T>& aRect)
	{
		return aRect.myMax - aRect.myMin;
	}

	template <typename T>
	Vector2<T> GetClosestPointOnRect(const Rect_t<T>& aRect, const Vector2<T>& aPoint)
	{
		CU::Vector2f point = aPoint;
		if (point.x > myMax.x) point.x = myMax.x;
		if (point.x < myMin.x) point.x = myMin.x;
		if (point.x > myMax.y) point.y = myMax.y;
		if (point.x < myMin.y) point.y = myMin.y;
		return point;
	}

	template <typename T>
	Rect_t<T> GetLetterboxRect(const Rect_t<T>& aContainingRect, float aTargetRatio)
	{
		const CU::Vector2<T> pos = aContainingRect.myMin;
		const CU::Vector2<T> size = GetRectSize(aContainingRect);
		float widthByHeight = size.x / size.y;

		Rect_t<T> rect;
		if (widthByHeight >= aTargetRatio)
		{
			float letterWidth = aTargetRatio * size.y;

			rect.myMin = pos + CU::Vector2f((size.x - letterWidth) / 2.f, 0.f);
			rect.myMax = rect.myMin + CU::Vector2f(letterWidth, size.y);
		}
		else
		{
			float letterHeight = size.x / aTargetRatio;

			rect.myMin = pos + CU::Vector2f(0.f, (size.y - letterHeight) / 2.f);
			rect.myMax = rect.myMin + CU::Vector2f(size.x, letterHeight);
		}

		return rect;
	}
}