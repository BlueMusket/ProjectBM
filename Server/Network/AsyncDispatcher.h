#pragma once

#include "Base/Thread.h"

#include "AsyncEvent.h"
#include "Iocp.h"

class CPeer;
class CSocket;
class CAsyncTcpEventSink;
class CAsyncEventSink;

class CAsyncDispatcher : public CSingleton<CAsyncDispatcher>
{
	SINGLETON_FOUNDATION(CAsyncDispatcher)

public:
	void Start();
	void Join();
	bool Associate(CAsyncTcpEventSink* sink, CSocket* socket);
	bool Enqueue(CAsyncEventSink* sink, CAsyncEvent::Tag* tag);
	bool Dequeue(ULONG_PTR* sink, LPOVERLAPPED* tag, DWORD& ioByte);

private:
private:
	CIocp* m_Iocp;

	class CIocpThread;
	std::vector<CIocpThread*> m_ThreadList;
};

#define g_AsyncDispatcher CSingleton<CAsyncDispatcher>::GetInstance()