#pragma once
#include <atomic>

template<typename T>
class CAtomic
{
public:
    CAtomic(T initValue) : m_Value(initValue) {}
    CAtomic() : m_Value(NULL) {}

public:
    void  Store(T newValue)
    {
        m_Value.store(newValue);
    }

    T Load() const
    {
        return m_Value.load();
    }

    // 예상 값과 현재 값이 일치하면 새 값으로 교체
    bool CompareAndExchange(T expectedValue, T newValue) 
    {
        // compare_exchange_strong은 예상 값이 현재 값과 일치하면 새 값을 설정하고 true를 반환
        // 일치하지 않으면 현재 값을 expectedValue에 저장하고 false를 반환
        return m_Value.compare_exchange_strong(expectedValue, newValue);
    }

    // Increase 함수
    T Increase(T value = 1) 
    {
        return m_Value.fetch_add(value);
    }

    // Decrease 함수
    T Decrease(T value = 1) 
    {
        return m_Value.fetch_sub(value);
    }

    //T operator++() { return Increase(); }
    //T operator--() { return Decrease(); }
    //T operator+=(T value) { return Increase(value); }
    //T operator-=(T value) { return Decrease(value); }
    T operator=(T value) { Store(value); return value; }
    operator T() const { return Load(); }
private:
    std::atomic<T> m_Value;
};

