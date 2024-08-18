#include "TimerShard.h"
#include "Network/AsyncDispatcher.h"


CTimerShard::CTimerShard()
    : m_Index(-1)
    , m_EventArray()
    , m_PushEventArray()
{
}

CTimerShard::~CTimerShard()
{
    // 전부 제거?
}

void CTimerShard::PushEvent(CAsyncTimerEvent* timerEvent)
{
    m_PushEventArray.emplace(timerEvent);
}

void CTimerShard::PushEvent(CTask* task, CAsyncEventSink* sink, Milli_t delay, Milli_t expiration/* = INVALID_TIME*/)
{
    CAsyncTimerEvent* newEvent = New(CAsyncTimerEvent);
    newEvent->SetTask(task);
    newEvent->SetSink(sink);
    newEvent->SetActivation(CTime::GetElapsedTick(delay));
    newEvent->SetExpiration(expiration);

    PushEvent(newEvent);
}

void CTimerShard::HeartBeat(Milli_t now)
{
    // 지금 호출이 필요한 timer enqueue
    static int eventArraySize = (int)m_EventArray.size();

    int index = ++m_Index;
    index = index % eventArraySize;

    CAsyncTimerEvent* timerEvent = nullptr;
	while (m_EventArray[index].try_pop(timerEvent))
	{
		g_AsyncDispatcher->Enqueue(timerEvent->GetSink(), &timerEvent->GetTag());
	}

    int nextIndex = index + 1;
    while (m_PushEventArray.try_pop(timerEvent))
    {
        // 실행이 필요한 타이머
        if (timerEvent->GetActivation() < now)
        {
            Milli_t gap = now - timerEvent->GetActivation();
            if (50 < gap)
            {
                // 로그 처리 너무 느리다.
            }

            g_AsyncDispatcher->Enqueue(timerEvent->GetSink(), &timerEvent->GetTag());
        }
        else
        {
            Milli_t remainTick = timerEvent->GetActivation() - now;
            // 50 : timer 호출 최소 단위
            int offset = min((int)(remainTick / 50), eventArraySize);
            int pushIndex = (offset + nextIndex) % eventArraySize;

            m_EventArray[pushIndex].emplace(timerEvent);
        }
    }
}
