#include "AsyncTcpEventPool.h"
#include "AsyncTcpEvent.h"

CAsyncTcpEventPool::CAsyncTcpEventPool(int initialSizePerPool)
{
    for (int size = MIN_PACKET_SIZE; size <= MAX_PACKET_SIZE; size *= 2)
    {
        m_Pools[size] = new CPoolArray<CAsyncTcpEvent, CPool<CAsyncTcpEvent>, 4>();
        for (int j = 0; j < initialSizePerPool; ++j)
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
    int actualSize = GetNextPowerOfTwo(bufferSize);
    if (actualSize > MAX_PACKET_SIZE)
    {
        throw std::out_of_range("Buffer size too large");
    }
    return m_Pools[actualSize]->Get(type, bufferSize);
}

void CAsyncTcpEventPool::Put(CAsyncTcpEvent* event)
{
    if (!event) return;
    auto it = m_Pools.find(event->GetMaxBufferSize());
    if (it != m_Pools.end())
    {
        it->second->Put(event);
    }
    else
    {
        delete event;  // If we don't have a pool for this size, delete the event
    }
}

int CAsyncTcpEventPool::GetTotalSize() const
{
    int total = 0;
    for (const auto& pair : m_Pools)
    {
        total += pair.second->GetTotalSize();
    }
    return total;
}

void CAsyncTcpEventPool::PrintPoolSizes() const
{
    //for (const auto& pair : m_Pools)
    //{
    //    std::cout << "Pool for buffer size " << pair.first
    //        << ": " << pair.second->GetTotalSize() << " events\n";
    //}
}