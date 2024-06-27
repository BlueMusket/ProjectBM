#pragma once

#define _WINSOCKAPI_
#include <windows.h>
#include <WinSock2.h>
#include <winsock.h>
#include <MSWSock.h>

// 네트워크 세팅 관련
namespace Network
{
	bool Setup();
}

class CAsyncTcpEvent;
class CSocket
{
public:
	CSocket();
	~CSocket();

public:
	SOCKET& GetHandle();
	void Close();

	bool Listen();
	bool Accept(CSocket* newSocket, CAsyncTcpEvent* acceptEvent);
	bool Bind(sockaddr_in& addr);
	bool Connect(sockaddr_in& addr, CAsyncTcpEvent* connectEvent);
	bool Disconnect(CAsyncTcpEvent* disconnectEvent);
	bool Recv(CAsyncTcpEvent* recvEvent);
	bool Send(CAsyncTcpEvent* sendEvent);

	bool OnAccepted(CAsyncTcpEvent* acceptEvent);

private:
	SOCKET m_Handle; // 소켓 핸들
	sockaddr m_Addr;
};