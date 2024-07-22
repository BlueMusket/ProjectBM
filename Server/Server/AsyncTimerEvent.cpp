#include "AsyncTimerEvent.h"
#include "Base/Task.h"
#include "Network/AsyncEventSink.h"
#include "TimerShard.h"

CAsyncTimerEvent::CAsyncTimerEvent()
    : m_Sink(nullptr)
    , m_Task(nullptr)
    , m_Activation(0)
    , m_Expiration(0)
    , m_Duration(0)
    , m_Interval(0)
    , m_MaxInterval(1)
{}

CAsyncTimerEvent::~CAsyncTimerEvent()
{

}

void CAsyncTimerEvent::Execute(bool result, int ioByteSize, CAsyncEventSink* sink)
{
    ++m_Interval;
    

    bool readd = false;
    
    do
    {
        if (m_Task)
        {
            (*m_Task)();
        }
        else
        {
            if (m_Sink)
            {
                if (sink != m_Sink)
                {
                    // error;
                    break;
                }
            }
            else
            {
                // error;
                break;
            }
        }

        readd = CanReadd();

    } while (false);

    if (true == readd)
    {
        g_TimerShard->Readd(this);
    }
    else
    {
        // 안전한 삭제?
    }
}

bool CAsyncTimerEvent::CanReadd() const
{
    if (Time::IsPast(m_Activation))
    {
        return false;
    }
    
    if (m_MaxInterval <= m_Interval)
    {
        return false;
    }

    return true;
}

/// <summary>
/// Sets the peer pointer
/// </summary>
/// <param name="peer"> Pointer to a CPeer object </param>
void CAsyncTimerEvent::SetSink(CAsyncEventSink* sink)
{
    m_Sink = sink;
}

/// <summary>
/// Gets the peer pointer
/// </summary>
/// <returns> Pointer to a CPeer object </returns>
CAsyncEventSink* CAsyncTimerEvent::GetSink() const
{
    return m_Sink;
}

/// <summary>
/// Sets Task
/// </summary>
/// <param name="task"> Task </param>
void CAsyncTimerEvent::SetTask(CTask* task)
{
    m_Task = task;
}
