#include "Iocp.h"
#include "Peer.h"
#include <WS2tcpip.h>
#include <thread>

CIocp::CIocp()
	: m_IocpHandle()
	, m_ProcessCount(0)
{
}

CIocp::~CIocp()
{
	CloseHandle(m_IocpHandle);
}

void CIocp::Start()
{
	m_ProcessCount = std::thread::hardware_concurrency();
	m_IocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, m_ProcessCount);
	HANDLE m_IocpHandle2 = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, m_ProcessCount);
	//sockaddr_in server_addr;
	//memset(&server_addr, 0, sizeof(server_addr));
	//server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//server_addr.sin_port = htons(13480);

	//bool isStart = false;
	//do
	//{
	//	if (SOCKET_ERROR == ::bind(session->getSocketHandle(), reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)))
	//	{
	//		break;
	//	}

	//	if (SOCKET_ERROR == ::listen(session->getSocketHandle(), SOMAXCONN))
	//	{
	//		break;
	//	}

	//} while (false);

	//if (false == isStart)
	//{
	//	// 로그를 넣을거에요~
	//}
}

bool CIocp::Assosiate(CAsyncTcpEventSink* sink, HANDLE& socket)
{
	const bool result = CreateIoCompletionPort(socket, GetHandle(), (ULONG_PTR)&sink, m_ProcessCount);

	/*if (false == result)
	{
		DWORD error = GetLastError();
	}*/

	return result;
}