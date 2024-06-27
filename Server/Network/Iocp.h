#pragma once

#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

class CAsyncTcpEventSink;

class CIocp
{
public:
	CIocp();
	~CIocp();

public:
	void Start();
	bool Assosiate(CAsyncTcpEventSink* sink, HANDLE& socket);
	HANDLE& GetHandle() { return m_IocpHandle; }

private:
	HANDLE m_IocpHandle;
	int m_ProcessCount;
};

