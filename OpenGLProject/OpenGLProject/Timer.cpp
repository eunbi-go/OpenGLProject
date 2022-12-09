#include "stdafx.h"
#include "Timer.h"

Timer* Timer::_pInstance = nullptr;


Timer::Timer()
{
}


Timer::~Timer()
{
}

HRESULT Timer::Ready_CTimeManager()
{
	_dDeltaTime = 0.0;

	QueryPerformanceFrequency(&_CpuTick);

	QueryPerformanceCounter(&_PreTime);
	QueryPerformanceCounter(&_CurTime);

	return S_OK;
}

void Timer::Update_CTimeManager()
{
	QueryPerformanceFrequency(&_CpuTick);
	QueryPerformanceCounter(&_CurTime);

	_dDeltaTime = double(_CurTime.QuadPart - _PreTime.QuadPart) / _CpuTick.QuadPart;

	_PreTime = _CurTime;
}
