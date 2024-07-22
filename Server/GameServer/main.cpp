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
int main()
{
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
    tasks.push_back(std::make_unique<CTask>( fo));

    // 4. Ŭ������ ��� �Լ��� ����� Task
    MyClass myClass;
    tasks.push_back(std::make_unique<CTask>(&MyClass::memberFunction, &myClass));

    // Task �����͸� ���� operator()�� ȣ��
    for (const auto& task : tasks) 
    {
        (*task)();  
    }
	return 0;
}