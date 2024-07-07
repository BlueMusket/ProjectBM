#pragma once

template<typename T>
class CSingleton
{
protected:
	CSingleton() { Setup(); };
	virtual ~CSingleton() {};


	virtual void Setup() {};


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