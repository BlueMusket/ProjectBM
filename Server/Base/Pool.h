#pragma once
#include "Singleton.h"

template<typename T>
class CPool
{
private:
	std::queue<T*> m_Pool;

public:
    void Put(T* item) 
    {
        item->~T();

        m_Pool.push(item);
    }

    template<typename... Types>
    T* Get(Types&&... args)
    {
        T* item = nullptr;

        if (m_Pool.empty())
        {
            item = New(T, std::forward<Types>(args)...);
        }
        else
        {
            item = m_Pool.front();

            new (item) T(std::forward<Types>(args)...);

            m_Pool.pop();
        }

        return item;
    }

    int GetSize() const
    {
        return (int)m_Pool.size();
    }
};


template<typename T>
class CLockFreePool
{
private:
	tbb::concurrent_queue<T*> m_Pool;

public:
    void Put(T* item) 
    {
        item->~T();

        m_Pool.push(item);
    }
    template<typename... Types>
    T* Get(Types&&... args)
    {
        T* item = nullptr;

        if (!m_Pool.try_pop(item))
        {
            item = New(T, std::forward<Types>(args)...);
        }
        else
        {
            new (item) T(std::forward<Types>(args)...);
        }

        return item;
    }

    int GetSize() const
    {
        return (int)m_Pool.unsafe_size();
    }
};

// Type trait to determine if a type is CPool or CPool2
template<typename T>
struct Is_Pool : std::false_type {};

template<typename T>
struct Is_Pool<CPool<T>> : std::true_type {};

template<typename T>
struct Is_Pool<CLockFreePool<T>> : std::true_type {};


template<typename T, typename PoolType, int ARRAY_SIZE = 1>
class CPoolArray : CSingleton<CPoolArray<T, PoolType, ARRAY_SIZE>>
{
    static_assert(Is_Pool<PoolType>::value, "PoolType must be either CPool or CLockFreePool");

private:
	CAtomic<int> m_GetIndex;
	CAtomic<int> m_PutIndex;

	std::array<PoolType, ARRAY_SIZE> m_PoolArray;

private:
    CPoolArray() : m_GetIndex(0), m_PutIndex(0) {}

public:

    static void Put(T* item) 
    {
        int index = CPoolArray::GetInstance()->m_PutIndex.Increase() % ARRAY_SIZE;

        CPoolArray::GetInstance()->m_PoolArray[index].Put(item);
    }

    template<typename... Types>
    static T* Get(Types&&... args)
    {
        int index = CPoolArray::GetInstance()->m_GetIndex.Increase() % ARRAY_SIZE;

        T* item = CPoolArray::GetInstance()->m_PoolArray[index].Get(std::forward<Types>(args)...);

        return item;
    }

    int GetTotalSize() const 
    {
        int total = 0;
        for (const auto& pool : m_PoolArray) 
        {
            total += pool.GetSize();
        }
        return total;
    }

    int GetPutCount() const 
    {
        return m_PutIndex;
    }

    int GetGetCount() const
    {
        return m_GetIndex;
    }
};


// Pool을 사용하는 클래스인지 확인
template<typename T>
struct Is_UsePool : std::false_type {};

class CAsyncTcpEvent;
template<>
struct Is_UsePool<CAsyncTcpEvent> : std::true_type {};


// Pool을 사용하는 클래스를 위한 type 어시스트
template<typename T>
struct PoolClassName
{
    using type = void;  // 기본값으로 void 사용
};

// Packet의 특수한 성격 때문에 이렇게 만든다 실제 예제는 아래
class CAsyncTcpEventPool;
template<>
struct PoolClassName<CAsyncTcpEvent>
{
    using type = CAsyncTcpEventPool;
};

//// CAsyncTcpEventPool을 특수화
//using CAsyncTcpEventPool = CPool<CAsyncTcpEvent>;
//
//template<>
//struct Is_UsePool<CAsyncTcpEvent> : std::true_type {};