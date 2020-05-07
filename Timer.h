#pragma once
namespace CommonUtilities
{
	class CTimer
	{
	public:
		CTimer();

		void Update();

		const float GetDeltaTime() const;
		const double GetTotalTime() const;
		const float GetTotalTimeF() const;

	private:

		const double myStartTime;
		double myCurrentTime;
		double myLastTime;
		double myDeltaTime;
	};
}

namespace CU = CommonUtilities;