#pragma once
#include "Line.h"
#include "GrowingArray.h"
#include "Vector2.h"

namespace CommonUtilities
{
	template <typename T>
	class LineVolume
	{
	public:
		LineVolume(const GrowingArray<Line<T>>& aLineList);
		void AddLine(const Line<T>& aLine);
		bool Inside(const Vector2<T>& aPosition) const;
		bool Inside(const LineVolume<T>& aLineVolume) const;
		const GrowingArray<Line<T>> & GetLines() const;
		GrowingArray<Vector2<T>> GetPoints() const;
	private:
		GrowingArray<Line<T>> myLineList;
	};

	template<typename T>
	inline LineVolume<T>::LineVolume(const GrowingArray<Line<T>>& aLineList)
	{
		myLineList = aLineList;
	}

	template<typename T>
	inline void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLineList.Add(aLine);
	}

	template<typename T>
	inline bool LineVolume<T>::Inside(const Vector2<T>& aPosition) const
	{
		for (unsigned short i = 0; i < myLineList.Size(); i++)
		{
			if (myLineList[i].Inside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool LineVolume<T>::Inside(const LineVolume<T>& aLineVolume) const
	{
		const GrowingArray<Line<T>>& lines = aLineVolume.GetLines();
		if (lines.Size() > 0 && myLineList.Size() > 0)
		{
			for (unsigned short i = 0; i < lines.Size(); i++)
			{
				for (unsigned short j = 0; j < myLineList.Size(); j++)
				{


					/*
							PLS FIX THIS BROKEN TRASH!
					*/



					const Vector2<T> & p1 = lines[i].GetPoint0();
					/*const Vector2<T> & p2 = lines[i].GetPoint1();
					const Vector2<T> & p3 = myLineList[j].GetPoint0();
					const Vector2<T> & p4 = myLineList[j].GetPoint1();
					T numerator = (p1.x * p2.y - p1.y * p2.x) * (p3.x * p4.y - p3.y * p4.x);
					T denominator = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y)*(p3.x - p4.x);
					if (denominator != 0)
					{
						CU::Vector2f intersection = {
							((((p3.x - p4.x) - (p1.x - p2.x)) * numerator) / denominator),
							((((p3.y - p4.y) - (p1.y - p2.y)) * numerator) / denominator) };
						T maxDistance = (p1 - p2).Length();

						if ((intersection - p1).Length() < maxDistance)
						{
							if ((intersection - p2).Length() < maxDistance)
							{
								return true;
							}
						}
					}*/
				}
			}
		}
		return false;
	}

	template<typename T>
	inline const GrowingArray<Line<T>>& LineVolume<T>::GetLines() const
	{
		return myLineList;
	}
	template<typename T>
	inline GrowingArray<Vector2<T>> LineVolume<T>::GetPoints() const
	{
		GrowingArray<Vector2<T>>points(3);
		if (myLineList.Size() >= 3)
		{
			for (unsigned short i = 0; i < myLineList.Size(); i++)
			{
				points.Add(myLineList[i].GetPoint0());
			}
		}
		return points;
	}
}