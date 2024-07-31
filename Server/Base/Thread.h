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
	CThread(Milli_t waitTick = 0);
	virtual ~CThread();

	void Init();
	void Start();
	void Join();
	virtual Milli_t CalculateWaitTick();
	virtual void Execute() = 0;
	void Run();
	virtual const wchar_t* GetName() { return L"Default Thread"; }
private:
	std::thread m_Thread;

	Milli_t m_StartTick;
	Milli_t m_WaitTick;
};

