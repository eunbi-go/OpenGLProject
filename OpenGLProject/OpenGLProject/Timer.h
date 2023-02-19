#pragma once

#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
private:
	Timer();
	~Timer();

public:
	HRESULT Ready_CTimeManager();
	void Update_CTimeManager();

public:
	float Get_DeltaTime() { return (float)_dDeltaTime; }


public:
	static Timer* Get_Instance()
	{
		if (!_pInstance)
			_pInstance = new Timer;
		return _pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(_pInstance);
	}

private:
	static Timer*			_pInstance;
	LARGE_INTEGER			_CpuTick;
	LARGE_INTEGER			_PreTime;
	LARGE_INTEGER			_CurTime;
	double					_dDeltaTime;
};

#endif // !__TIMER_H__