#pragma once
#include <atomic>

template<typename T>
class CAtomic
{
public:
    CAtomic(T initValue) : m_Value(initValue) {}

public:
    void  Store(T newValue)
    {
        m_Value.store(newValue);
    }

    T Get() const
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

private:
    std::atomic<T> m_Value;

    template<typename T, typename Func>
    bool TryExchangeWith(T value, T comparand, const Func& func)
    {
        //CScopedTryExchange scopedTryExchange(*this, value, comparand);
        //if (scopedTryExchange)
        {
            func();
            return true;
        }
        return false;
    }
};

