#pragma once
#include "Base/Pool.h"
#include "Base/Singleton.h"

class CAsyncTcpEvent;

/// <summary>
/// CAsyncTcpEvent의 Pool을 다루는 객체 일반적인 Pool과 구조가 다르지만 사용법이 동일해야한다.
/// </summary>
class CAsyncTcpEventPool : public CSingleton<CAsyncTcpEventPool>
{
SINGLETON_FOUNDATION(CAsyncTcpEventPool)

private:
    std::map<int, CPoolArray<CAsyncTcpEvent, CPool<CAsyncTcpEvent>, 4>*> m_Pools;

    int GetNextPowerOfTwo(int n) const;

public:
    static CAsyncTcpEvent* Get(CAsyncTcpEvent::EventType type, int bufferSize);
    static void Put(CAsyncTcpEvent* event);
};

#define g_AsyncTcpEventPool CSingleton<CAsyncTcpEventPool>::GetInstance()

//template<typename... Types>
//CAsyncTcpEvent* PoolAlloc(Types&&... args)
//{
//    return nullptr;
//}
//
//template<>
//void PoolDealloc(CAsyncTcpEvent* item)
//{
//
//}
//
