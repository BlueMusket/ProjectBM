#include "TimerShard.h"
#include "Network/AsyncDispatcher.h"
#include "AsyncTimerEvent.h"


bool CTimerShard::Setup()
{
    return true;
}

void CTimerShard::Readd(CAsyncTimerEvent* timerEvent)
{
}

void CTimerShard::PushEvent()
{
}

void CTimerShard::HeartBeat()
{
    CAsyncTimerEvent* timerEvent = nullptr;
    //while (m_EventShard.try_pop(timerEvent))
    {
        g_AsyncDispatcher->Enqueue(timerEvent->GetSink(), &timerEvent->GetTag());

    }
}
