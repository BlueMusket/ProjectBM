#pragma once
#include "Base/Singleton.h"

class CAsyncTimerEvent;
class CTimerShard : public CSingleton<CTimerShard>
{
private:
    class CEvent;

public:
	virtual bool Setup() override;


public:
	void Readd(CAsyncTimerEvent* timerEvent);
	void PushEvent();
	void HeartBeat();
private:
	using EventQueue = tbb::concurrent_priority_queue<CEvent>;
	std::array<EventQueue, 100> m_EventArray;
};

#define g_TimerShard CSingleton<CTimerShard>::GetInstance()