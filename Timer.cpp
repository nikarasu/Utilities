#include "stdafx.h"
#include "Timer.h"
#include <chrono>

CommonUtilities::CTimer::CTimer() :
	myStartTime(static_cast<double>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) / std::chrono::high_resolution_clock::period::den)
{
	myLastTime = myStartTime;
	myCurrentTime = myStartTime;
	myDeltaTime = 0;
}

void CommonUtilities::CTimer::Update()
{
	myCurrentTime = static_cast<double>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) / std::chrono::high_resolution_clock::period::den;
	myDeltaTime = (myCurrentTime - myLastTime);
	myLastTime = myCurrentTime;
}

const float CommonUtilities::CTimer::GetDeltaTime() const
{	
	return static_cast<float>(myDeltaTime);
}

const double CommonUtilities::CTimer::GetTotalTime() const
{
	return (myCurrentTime - myStartTime);
}

const float CommonUtilities::CTimer::GetTotalTimeF() const
{
	return static_cast<float>(myCurrentTime - myStartTime);
}
