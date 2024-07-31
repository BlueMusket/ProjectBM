#pragma once

#include <functional>

class CTask
{
public:
	typedef std::function<void()> Callback;

public: // 1. 일반 함수 포인터를 위한 생성자
    CTask(void (*functionPointer)())
        : m_Callback(functionPointer) {}

    // 2. 함수 객체를 위한 생성자
    template<typename Functor>
    CTask(Functor&& functor)
        : m_Callback(std::forward<Functor>(functor)) {}

    // 3. 클래스의 멤버 함수를 위한 생성자
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

// 사용법
/*
void normalFunction()
{
    std::cout << "This is a normal function." << std::endl;
}

// �Լ� ��ü
struct FunctionObject
{
    void operator()() const
    {
        std::cout << "This is a function object." << std::endl;
    }
};

// Ŭ������ ��� �Լ�
class MyClass {
public:
    void memberFunction()
    {
        std::cout << "This is a member function." << std::endl;
    }
};

std::vector<std::unique_ptr<CTask>> tasks;

// 1. �Ϲ� �Լ��� ����� Task
tasks.push_back(std::make_unique<CTask>(normalFunction));

// 2. ���� ǥ������ ����� Task
tasks.push_back(std::make_unique<CTask>([]()
    {
        std::cout << "This is a lambda function." << std::endl;
    }));

// 3. �Լ� ��ü�� ����� Task
FunctionObject fo;
tasks.push_back(std::make_unique<CTask>(fo));

// 4. Ŭ������ ��� �Լ��� ����� Task
MyClass myClass;
tasks.push_back(std::make_unique<CTask>(&MyClass::memberFunction, &myClass));

// Task �����͸� ���� operator()�� ȣ��
for (const auto& task : tasks)
{
    (*task)();
}

*/