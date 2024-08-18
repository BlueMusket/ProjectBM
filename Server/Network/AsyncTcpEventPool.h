#pragma once
#include "Base/Pool.h"

class CAsyncTcpEvent;
class CAsyncTcpEventPool
{
private:
    std::map<int, CPoolArray<CAsyncTcpEvent, CPool<CAsyncTcpEvent>, 4>*> m_Pools;

    int GetNextPowerOfTwo(int n) const;

public:
    CAsyncTcpEventPool( int initialSizePerPool = 25);
    ~CAsyncTcpEventPool();

    CAsyncTcpEvent* Get(CAsyncTcpEvent::EventType type, int bufferSize);
    void Put(CAsyncTcpEvent* event);
    int GetTotalSize() const;
    void PrintPoolSizes() const;
};

