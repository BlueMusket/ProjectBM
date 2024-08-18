#pragma once
#include <mutex>

template<typename T>
class CSingleton
{
protected:
	virtual ~CSingleton() {};

public:
	static T* GetInstance()
	{
        static std::once_flag flag;
        static T* instance = nullptr;

        // threadSafe한 객체 생성
        std::call_once(flag, []()
        {
            instance = new T;
        });

        return instance;
	}
};

#define SINGLETON_FOUNDATION(name)\
public:\
name();\
protected:\
virtual ~name();