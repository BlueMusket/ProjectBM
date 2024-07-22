#pragma once
#include "Base/Singleton.h"

class CTask;
class CAsyncEventSink;
class CAsyncTimerEvent;
class CTimerShard : public CSingleton<CTimerShard>
{
SINGLETON_FOUNDATION(CTimerShard)

private:
	struct COMPARE
	{
		bool operator()(const CAsyncTimerEvent* lhs, const CAsyncTimerEvent* rhs) const
		{
			return lhs->GetActivation() < rhs->GetActivation();
		}
	};

	using EventQueue = tbb::concurrent_priority_queue<CAsyncTimerEvent*, COMPARE>;
	std::array<EventQueue, 100> m_EventArray;
	EventQueue m_PushEventArray;

	CAtomic<int> m_Index;

public:
	void PushEvent(CTask* task, CAsyncEventSink* sink, Milli_t delay, Milli_t expiration = INVALID_TIME);
	void PushEvent(CAsyncTimerEvent* timerEvent);
	void HeartBeat(Milli_t now);
};

#define g_TimerShard CSingleton<CTimerShard>::GetInstance()