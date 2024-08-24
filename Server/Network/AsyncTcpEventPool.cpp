#include "AsyncTcpEventPool.h"
#include "AsyncTcpEvent.h"

CAsyncTcpEventPool::CAsyncTcpEventPool()
{
    for (int size = MIN_PACKET_SIZE; size <= MAX_PACKET_SIZE; size *= 2)
    {
        m_Pools[size] = new CPoolArray<CAsyncTcpEvent, CPool<CAsyncTcpEvent>, 4>();
        for (int j = 0; j < 25; ++j)
        {
            m_Pools[size]->Put(new CAsyncTcpEvent(CAsyncTcpEvent::EventType::Send, size));
            m_Pools[size]->Put(new CAsyncTcpEvent(CAsyncTcpEvent::EventType::Receive, size));
        }
    }
}

CAsyncTcpEventPool::~CAsyncTcpEventPool()
{
    for (auto& pair : m_Pools)
    {
        delete pair.second;
    }
}

int CAsyncTcpEventPool::GetNextPowerOfTwo(int n) const
{
    int power = MIN_PACKET_SIZE;
    while (power < n && power < MAX_PACKET_SIZE)
    {
        power *= 2;
    }
    return power;
}

CAsyncTcpEvent* CAsyncTcpEventPool::Get(CAsyncTcpEvent::EventType type, int bufferSize)
{
    int actualSize = g_AsyncTcpEventPool->GetNextPowerOfTwo(bufferSize);
    if (actualSize > MAX_PACKET_SIZE)
    {
        throw std::out_of_range("Buffer size too large");
    }
    return g_AsyncTcpEventPool->m_Pools[actualSize]->Get(type, bufferSize);
}

void CAsyncTcpEventPool::Put(CAsyncTcpEvent* event)
{
    if (!event) return;
    auto it = g_AsyncTcpEventPool->m_Pools.find(event->GetMaxBufferSize());
    if (it != g_AsyncTcpEventPool->m_Pools.end())
    {
        it->second->Put(event);
    }
    else
    {
        delete event;  // If we don't have a pool for this size, delete the event
    }
}