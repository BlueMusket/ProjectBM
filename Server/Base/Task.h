#pragma once

#include <functional>

class CTask
{
public:
	typedef std::function<void()> Callback;

public: // 1. 일반 함수 포인터를 위한 생성자
    CTask(void (*functionPointer)())
        : m_Callback(functionPointer) {}

    // 2. 람다 표현식을 위한 생성자
    template<typename Lambda>
    CTask(Lambda&& lambda)
        : m_Callback(std::forward<Lambda>(lambda)) {}

    // 3. 함수 객체를 위한 생성자
    template<typename Functor>
    CTask(Functor&& functor)
        : m_Callback(std::forward<Functor>(functor)) {}

    // 4. 클래스의 멤버 함수를 위한 생성자
    template<typename C>
    CTask(void (C::* memberFunction)(), C* instance)
        : m_Callback(std::bind(memberFunction, instance)) {}

	virtual ~CTask();

public:
	void OnCallbackEvent() const;

private:
	Callback m_Callback;

public:
	void operator()() const
	{
        OnCallbackEvent();
	}
};

