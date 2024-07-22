#include "Network/Peer.h"
#include "Base/Task.h"
#include "Network/AsyncDispatcher.h"
#include <iostream>
#include <vector>
#include <memory>
void normalFunction() 
{
    std::cout << "This is a normal function." << std::endl;
}

// 함수 객체
struct FunctionObject 
{
    void operator()() const 
    {
        std::cout << "This is a function object." << std::endl;
    }
};

// 클래스와 멤버 함수
class MyClass {
public:
    void memberFunction() 
    {
        std::cout << "This is a member function." << std::endl;
    }
};
int main()
{
    std::vector<std::unique_ptr<CTask>> tasks;

    // 1. 일반 함수를 사용한 Task
    tasks.push_back(std::make_unique<CTask>(normalFunction));

    // 2. 람다 표현식을 사용한 Task
    tasks.push_back(std::make_unique<CTask>([]() 
    {
        std::cout << "This is a lambda function." << std::endl;
    }));

    // 3. 함수 객체를 사용한 Task
    FunctionObject fo;
    tasks.push_back(std::make_unique<CTask>( fo));

    // 4. 클래스의 멤버 함수를 사용한 Task
    MyClass myClass;
    tasks.push_back(std::make_unique<CTask>(&MyClass::memberFunction, &myClass));

    // Task 포인터를 통해 operator()를 호출
    for (const auto& task : tasks) 
    {
        (*task)();  
    }
	return 0;
}