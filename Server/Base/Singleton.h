#pragma once

template<typename T>
class CSingleton
{
protected:
	CSingleton() {};
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