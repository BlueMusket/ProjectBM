#include "Thread.h"
#include <Windows.h>

CThread::CThread(Milli_t waitTick/* = 0*/)
	: m_WaitTick(waitTick)
	, m_StartTick()
{
}

CThread::~CThread()
{
	m_Thread.detach();
}

void CThread::Init()
{
	m_Thread = std::thread(&CThread::Start, this);
}

void CThread::Start()
{
	// 쓰래드 세팅
	const wchar_t* threadName = GetName();
	SetThreadDescription(GetCurrentThread(), threadName);

	// TODO : DeadLock 체킹용 관리 클래스 만들기

	Run();
}

void CThread::Join()
{
	m_Thread.join();
}

void CThread::Run() 
{
	while (true) 
	{
		m_StartTick = Time::GetCurrentMilliTick();

		Execute();

		Milli_t duration = Time::GetCurrentMilliTick() - m_StartTick;

		// 너무 길면 로그

		Milli_t waitTick = Math::Min(CalculateWaitTick() - duration , (Milli_t)0);

		Sleep(waitTick);
	}
}

Milli_t CThread::CalculateWaitTick()
{
	return m_WaitTick;
}