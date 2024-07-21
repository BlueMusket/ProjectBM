#pragma once
#include <vector>

#include "Base/System.h"
#include "Base/Thread.h"

#include "AsyncEvent.h"
#include "Iocp.h"

class CPeer;
class CSocket;
class CAsyncTcpEventSink;
class CAsyncEventSink;

class CAsyncDispatcher : public CSingleton<CAsyncDispatcher>
{
public:
	CAsyncDispatcher();
	virtual ~CAsyncDispatcher();

public:
	void Start();
	void Join();
	bool Associate(CAsyncTcpEventSink* sink, CSocket* socket);
	bool Enqueue(CAsyncEventSink* sink, CAsyncEvent::Tag* tag);
	bool Dequeue(ULONG_PTR* sink, LPOVERLAPPED* tag, DWORD& ioByte);

private:
	class CIocpThread : public CThread
	{
	public:
		CIocpThread();
		~CIocpThread();

	public:
		virtual void Run();
		virtual const wchar_t* GetName() { return L"Iocp Thread"; }
	};

private:
	CIocp* m_Iocp;
	std::vector<CIocpThread*> m_ThreadList;
};

#define g_AsyncDispatcher CSingleton<CAsyncDispatcher>::GetInstance()