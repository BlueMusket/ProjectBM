#pragma once

#include <functional>

class CTask
{
public:
	typedef std::function<void()> Callback;

public:
	CTask( const Callback& callback);
	virtual ~CTask();

public:
	void OnCallbackEvent();

private:
	Callback m_Callback;
};

