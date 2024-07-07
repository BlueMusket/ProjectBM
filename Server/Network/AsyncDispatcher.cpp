#include "AsyncDispatcher.h"
#include <thread>
#include "AsyncEvent.h"
#include "AsyncTcpEventSink.h"
#include "Socket.h"
#include "PeerFacade.h"

CAsyncDispatcher::CAsyncDispatcher()
{
	m_Iocp = New(CIocp);
}

CAsyncDispatcher::~CAsyncDispatcher()
{
}

void CAsyncDispatcher::Start()
{
	m_Iocp->Start();

	const int threadCount = 4;
	for (int index = 0; index < threadCount; ++index)
	{
		CIocpThread* workerThread = New(CIocpThread);
		workerThread->Init();

		m_ThreadList.push_back(workerThread);
	}
}

void CAsyncDispatcher::Join()
{
	const int count = (int)m_ThreadList.size();

	for (auto thread : m_ThreadList)
	{
		thread->Join();
	}
}

bool CAsyncDispatcher::Associate(CAsyncTcpEventSink* sink, CSocket* socket)
{
	return nullptr != CreateIoCompletionPort((HANDLE)socket->GetHandle(), m_Iocp->GetHandle(), (ULONG_PTR)sink, 0);
}

bool CAsyncDispatcher::Enqueue(CAsyncEventSink* sink, CAsyncEvent::Tag* tag)
{
	return PostQueuedCompletionStatus(m_Iocp->GetHandle(), 0, (ULONG_PTR)sink, (LPOVERLAPPED)(tag));
}

bool CAsyncDispatcher::Dequeue(ULONG_PTR* sink, LPOVERLAPPED* tag, DWORD& ioByte)
{
	return GetQueuedCompletionStatus(m_Iocp->GetHandle(), &ioByte, sink, tag, INFINITE);
}


CAsyncDispatcher::CIocpThread::CIocpThread()
{
}

CAsyncDispatcher::CIocpThread::~CIocpThread()
{
}

void CAsyncDispatcher::CIocpThread::Run()
{
	while (true)
	{
		CAsyncEventSink* sink = nullptr;
		CAsyncEvent::Tag* tag = nullptr;
		DWORD ioByteSize = 0;

		bool result = g_AsyncDispatcher::GetInstance()->Dequeue(
												  reinterpret_cast<ULONG_PTR*>(&sink)
												, reinterpret_cast<LPOVERLAPPED*>(&tag)
												, ioByteSize);

		const DWORD lastError = GetLastError();
		if (nullptr != tag && (0 == lastError || ERROR_IO_PENDING == lastError))
		{
			tag->m_Owner->Execute(result, ioByteSize, sink);
		}
		else
		{
			CPeerFacade::Disconnected(sink);
		}
	}
}
