#pragma once

template<typename T>
class CPool
{
private:
	std::queue<T*> m_Pool;

public:
    void Put(T* item) 
    {
        m_Pool.push(item);
    }

    T* Get() 
    {
        T* item = nullptr;

        if (m_Pool.empty())
        {
            item = New(T);
        }
        else
        {
            item = m_Pool.front();
            m_Pool.pop();
        }

        return item;
    }

    size_t GetSize() const 
    {
        return m_Pool.size();
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
        m_Pool.push(item);
    }

    T* Get() 
    {
        T* item = nullptr;

        if (!m_Pool.try_pop(item))
        {
            item = New(T);
        }

        return item;
    }

    size_t GetSize() const 
    {
        return m_Pool.unsafe_size();
    }
};

// Type trait to determine if a type is CPool or CPool2
template<typename T>
struct is_pool : std::false_type {};

template<typename T>
struct is_pool<CPool<T>> : std::true_type {};

template<typename T>
struct is_pool<CLockFreePool<T>> : std::true_type {};

template<typename T, typename PoolType, int ARRAY_SIZE = 1>
class CPoolArray
{
    static_assert(is_pool<PoolType>::value, "PoolType must be either CPool or CLockFreePool");

private:
	CAtomic<int> m_GetIndex;
	CAtomic<int> m_PutIndex;

	std::array<PoolType, ARRAY_SIZE> m_PoolArray;

public:
    CPoolArray() : m_GetIndex(0), m_PutIndex(0) {}

    void Put(T* item) 
    {
        int index = m_PutIndex.Increase() % ARRAY_SIZE;

        m_PoolArray[index].Put(item);
    }

    T* Get() 
    {
        int index = m_GetIndex.Increase() % ARRAY_SIZE;

        T* item = m_PoolArray[index].Get();

        new (item) T;

        return item;
    }

    size_t GetTotalSize() const 
    {
        size_t total = 0;
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
