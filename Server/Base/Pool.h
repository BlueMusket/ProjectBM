#pragma once

template<typename T>
class CPool
{
private:
	std::queue<T*> m_Pool;

public:
    template<typename... Types>
    T* operator()(Types&&... args)
    {
        return Get(std::forward<Types>(args)...);
    }
public:
    void Init(int size)
    {
        for (int index = 0; index < size; ++index)
        {
            T* item = new T();
            m_Pool.push(item);
        }
    }

    template<typename... Types>
    T* Get(Types&&... args)
    {
        T* item = nullptr;

        if (m_Pool.empty())
        {
            item = new T(std::forward<Types>(args)...);
        }
        else
        {
            item = m_Pool.front();

            new (item) T(std::forward<Types>(args)...);

            m_Pool.pop();
        }

        return item;
    }

    void Put(T* item) 
    {
        item->~T();

        m_Pool.push(item);
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
    template<typename... Types>
    T* operator()(Types&&... args)
    {
        return Get(std::forward<Types>(args)...);
    }

public:

    void Init(int size)
    {
        for (int index = 0; index < size; ++index)
        {
            T* item = new T();
            m_Pool.push(item);
        }
    }

    template<typename... Types>
    T* Get(Types&&... args)
    {
        T* item = nullptr;

        if (!m_Pool.try_pop(item))
        {
            item = new T(std::forward<Types>(args)...);
        }
        else
        {
            new (item) T(std::forward<Types>(args)...);
        }

        return item;
    }

    void Put(T* item)
    {
        item->~T();

        m_Pool.push(item);
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
class CPoolArray
{
    static_assert(Is_Pool<PoolType>::value, "PoolType must be either CPool or CLockFreePool");

private:
	CAtomic<int> m_GetIndex;
	CAtomic<int> m_PutIndex;

	std::array<PoolType, ARRAY_SIZE> m_PoolArray;

public:
    CPoolArray() : m_GetIndex(0), m_PutIndex(0) {}

public:
    template<typename... Types>
    T* operator()(Types&&... args)
    {
        return Get(std::forward<Types>(args)...);
    }

public:

    void Init(int size)
    {
        for (int index = 0; index < ARRAY_SIZE; ++index)
        {
            m_PoolArray[index].Init(size);
        }
    }

    void Put(T* item) 
    {
        int index = m_PutIndex.Increase() % ARRAY_SIZE;

        m_PoolArray[index].Put(item);
    }

    template<typename... Types>
    T* Get(Types&&... args)
    {
        int index = m_GetIndex.Increase() % ARRAY_SIZE;

        T* item = m_PoolArray[index].Get(std::forward<Types>(args)...);

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

template<typename T>
class ObjectPool 
{
public:
    template<typename... Types>
    static T* Allocate(Types&&... args)
    {
        return new T(std::forward<Types>(args)...);
    }

    static void Deallocate(T* item) 
    {
        delete item;
    }
};