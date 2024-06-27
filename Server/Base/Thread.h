#pragma once

#include <thread>
#include <string>

/// <summary>
/// Thread의 최상위 클래스
/// </summary>
class CThread
{
	enum class EState
	{
		// Tr 처리용
		WAIT = 0,
		RUN,

		Count,
	};

public:
	CThread();
	virtual ~CThread();

	void Init();
	void Start();
	void Join();
	virtual void Run() = 0;
	virtual const wchar_t* GetName() { return L"Default Thread"; }
private:
	std::thread m_Thread;
};

