#pragma once

template<typename T>
class CSingleton
{
protected:
	virtual ~CSingleton() {};

public:
	static T* GetInstance()
	{
		static T* instance;
		if (nullptr == instance)
		{
			instance = new T;
		}

		return instance;
	}
};

#define SINGLETON_FOUNDATION(name)\
public:\
name();\
protected:\
virtual ~name();