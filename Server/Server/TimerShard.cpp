#include "TimerShard.h"
#include "Network/AsyncDispatcher.h"
#include "AsyncTimerEvent.h"

class CTimerShard::CEvent
{
public:
    CTimerShard::CEvent(CAsyncTimerEvent* timerEvent)
        : m_TimerEvent(timerEvent) {}

private:
    CAsyncTimerEvent* m_TimerEvent;

public:
    bool operator<(const CEvent& other) const
    {
        return false; // �켱������ �����Ƿ� �׻� false�� ��ȯ
    }
};

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
    while (m_EventShard.try_pop(timerEvent))
    {
        g_AsyncDispatcher::GetInstance()->Enqueue(timerEvent->GetSink(), &timerEvent->GetTag());

    }
}
