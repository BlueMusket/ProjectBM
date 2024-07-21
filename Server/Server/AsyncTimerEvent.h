#pragma once
#include "Network/AsyncEvent.h"

class CAsyncEventSink;
class CTask;
class CAsyncTimerEvent : public CAsyncEvent
{
private:
    CAsyncEventSink* m_Sink;
    CTask* m_Task;
    
    Milli_t m_Activation; ///< 활성화 시간
    Milli_t m_NextActiveTick; ///<다음 활성화 시간
    Milli_t m_Duration; ///< 활성화 간격
    int m_Interval; ///< 활성화 횟수
    int m_MaxInterval; ///< 최대 활성화 횟수
public:
    CAsyncTimerEvent();
    virtual ~CAsyncTimerEvent();

public:
	virtual void Execute(bool result, int ioByteSize, CAsyncEventSink* sink);

private:
    bool CanReadd() const;

public:
    /// <summary>
    /// Sets Sink
    /// </summary>
    /// <param name="sink"> Pointer to a sink </param>
    void SetSink(CAsyncEventSink* sink);

    /// <summary>
    /// Gets Sink
    /// </summary>
    /// <returns> Pointer to a CPeer object </returns>
    CAsyncEventSink* GetSink() const;

    /// <summary>
    /// Sets Task
    /// </summary>
    /// <param name="task"> Task </param>
    void SetTask(CTask* task);

    Milli_t GetActivation() const { return m_Activation; }
    void SetActivation(Milli_t activation) { m_Activation = activation; }
    Milli_t GetNextActiveTick() const { return m_NextActiveTick; }
    void SetNextActiveTick(Milli_t nextActiveTick) { m_NextActiveTick = nextActiveTick; }
    Milli_t GetDuration() const { return m_Duration; }
    void SetDuration(Milli_t duration) { m_Duration = duration; }
    int GetInterval() const { return m_Interval; }
    void SetInterval(int interval) { m_Interval = interval; }
    int GetMaxInterval() const { return m_MaxInterval; }
    void SetMaxInterval(int maxInterval) { m_MaxInterval = maxInterval; }
};

