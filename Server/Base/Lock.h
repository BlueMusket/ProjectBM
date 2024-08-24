#pragma once
#include <windows.h>
class CLock
{
	friend class CScopeLock;

public:
	CLock()
	{
		InitializeCriticalSection(&m_Lock);
	}

private:
	void Lock()
	{
		EnterCriticalSection(&m_Lock);
	}

	void UnLock()
	{
		LeaveCriticalSection(&m_Lock);
	}

protected:
	CRITICAL_SECTION m_Lock;
};

class CScopeLock
{
public:
	CScopeLock(CLock* lock)
		: m_Lock(lock)
	{
		m_Lock->Lock();
	}

	~CScopeLock()
	{
		m_Lock->UnLock();
		m_Lock = nullptr;
	}

private:
	CLock* m_Lock;
};

class CRWLock
{
    friend class CReadScopeLock;
    friend class CWriteScopeLock;

public:
    CRWLock()
    {
        InitializeSRWLock(&m_Lock);
    }

private:
    void LockRead()
    {
        AcquireSRWLockShared(&m_Lock);
    }

    void UnlockRead()
    {
        ReleaseSRWLockShared(&m_Lock);
    }

    void LockWrite()
    {
        AcquireSRWLockExclusive(&m_Lock);
    }

    void UnlockWrite()
    {
        ReleaseSRWLockExclusive(&m_Lock);
    }

protected:
    SRWLOCK m_Lock;
};

class CReadScopeLock
{
public:
    CReadScopeLock(CRWLock* lock)
        : m_Lock(lock)
    {
        m_Lock->LockRead();
    }

    ~CReadScopeLock()
    {
        m_Lock->UnlockRead();
        m_Lock = nullptr;
    }

private:
    CRWLock* m_Lock;
};

class CWriteScopeLock
{
public:
    CWriteScopeLock(CRWLock* lock)
        : m_Lock(lock)
    {
        m_Lock->LockWrite();
    }

    ~CWriteScopeLock()
    {
        m_Lock->UnlockWrite();
        m_Lock = nullptr;
    }

private:
    CRWLock* m_Lock;
};

class CInterLock
{
public:
    CInterLock(LONG initialValue = 0) : m_Value(initialValue) {}

    LONG Increment()
    {
        return InterlockedIncrement(&m_Value);
    }

    LONG Decrement()
    {
        return InterlockedDecrement(&m_Value);
    }

    LONG Add(LONG value)
    {
        return InterlockedAdd(&m_Value, value);
    }

    LONG Exchange(LONG value)
    {
        return InterlockedExchange(&m_Value, value);
    }

    LONG CompareExchange(LONG exchange, LONG comperand)
    {
        return InterlockedCompareExchange(&m_Value, exchange, comperand);
    }

    LONG GetValue() const
    {
        return InterlockedCompareExchange(const_cast<LONG*>(&m_Value), 0, 0);
    }

private:
    volatile LONG m_Value;
};

// 64비트 버전
class CInterLock64
{
public:
    CInterLock64(LONG64 initialValue = 0) : m_Value(initialValue) {}

    LONG64 Increment()
    {
        return InterlockedIncrement64(&m_Value);
    }

    LONG64 Decrement()
    {
        return InterlockedDecrement64(&m_Value);
    }

    LONG64 Add(LONG64 value)
    {
        return InterlockedAdd64(&m_Value, value);
    }

    LONG64 Exchange(LONG64 value)
    {
        return InterlockedExchange64(&m_Value, value);
    }

    LONG64 CompareExchange(LONG64 exchange, LONG64 comperand)
    {
        return InterlockedCompareExchange64(&m_Value, exchange, comperand);
    }

    LONG64 GetValue() const
    {
        return InterlockedCompareExchange64(const_cast<LONG64*>(&m_Value), 0, 0);
    }

private:
    volatile LONG64 m_Value;
};


class CAtomicBitSet
{
public:
    CAtomicBitSet(LONG initialValue = 0) : m_Value(initialValue) {}

    bool BitTest(LONG index)
    {
        return (InterlockedOr(&m_Value, 0) & index) != 0;
    }

    void BitSet(LONG index, bool value)
    {
        if (value)
        {
            InterlockedOr(&m_Value, index);
        }
        else
        {
            InterlockedAnd(&m_Value, ~index);
        }
    }

    LONG GetValue() const
    {
        return InterlockedCompareExchange(const_cast<LONG*>(&m_Value), 0, 0);
    }

private:
    volatile LONG m_Value;
};

template<typename T>
class AtomicPtr
{
public:
    AtomicPtr(T* initialValue = nullptr) : m_Ptr(initialValue) {}

    T* Load() const
    {
        return reinterpret_cast<T*>(InterlockedCompareExchangePointer(
            reinterpret_cast<PVOID*>(&m_Ptr), nullptr, nullptr));
    }

    void Store(T* newValue)
    {
        InterlockedExchangePointer(reinterpret_cast<PVOID*>(&m_Ptr), newValue);
    }

    T* Exchange(T* newValue)
    {
        return reinterpret_cast<T*>(InterlockedExchangePointer(
            reinterpret_cast<PVOID*>(&m_Ptr), newValue));
    }

    bool CompareExchange(T*& expected, T* desired)
    {
        PVOID comparand = expected;
        PVOID exchanged = InterlockedCompareExchangePointer(
            reinterpret_cast<PVOID*>(&m_Ptr), desired, comparand);
        if (exchanged == comparand)
        {
            return true;
        }

        expected = reinterpret_cast<T*>(exchanged);
        return false;
    }

private:
    T* volatile m_Ptr;
};