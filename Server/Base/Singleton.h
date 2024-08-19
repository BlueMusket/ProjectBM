#pragma once
#include <xcall_once.h>

template<typename T>
class CSingleton
{
    friend T;

protected:
	CSingleton() = default;
	virtual ~CSingleton() = default;
    
public:
    CSingleton(const CSingleton&) = delete;
    CSingleton& operator=(const CSingleton&) = delete;

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
    virtual ~name();\
private:\
    name(const name&) = delete;\
    name& operator=(const name&) = delete;