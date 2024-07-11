#pragma once
#include <windows.h>
class CLock
{
	friend class CScopeLock;

public:
	CLock()
	{
		InitializeCriticalSection(&m_Lock);
	}

private:
	void Lock()
	{
		EnterCriticalSection(&m_Lock);
	}

	void UnLock()
	{
		LeaveCriticalSection(&m_Lock);
	}

protected:
	CRITICAL_SECTION m_Lock;
};

class CScopeLock
{
public:
	CScopeLock(CLock* lock)
		: m_Lock(lock)
	{
		m_Lock->Lock();
	}

	~CScopeLock()
	{
		m_Lock->UnLock();
		m_Lock = nullptr;
	}

private:
	CLock* m_Lock;
};