#include "Thread.h"
#include <Windows.h>

CThread::CThread()
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

	Run();
}

void CThread::Join()
{
	m_Thread.join();
}