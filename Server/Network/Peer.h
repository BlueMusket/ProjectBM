#pragma once

#include "AsyncTcpEventSink.h"

class CSendPolicy;
class CLoginPolicy;
class CSocket;
class CAsyncTcpEvent;

class CPeer : public CAsyncTcpEventSink
{
public:
	CPeer();
	virtual ~CPeer();

public:

	/// <summary>
	/// 소켓 통신에서 IO를 받았을때 호출
	/// </summary>
	/// <param name="tcpEvent"> 받은 이벤트 </param>
	/// <returns>성공시 처리한 바이트 수</returns>
	virtual void OnReceiveEvent(bool result, int ioByteSize, CAsyncTcpEvent* tcpEvent);

	/// <summary>
	/// Accept 성공시 호출되는 함수
	/// </summary>
	/// <param name="tcpEvent"> accept시 받은 이벤트 </param>
	virtual void OnAccepted(CAsyncTcpEvent* tcpEvent);
public:

	// 패킷을 보내기 위한 사전 작업
	bool PostSend(CAsyncTcpEvent* sendEvent);

	// 패킷을 실제로 보낸다.
	bool Send(CAsyncTcpEvent* sendEvent);

	CSocket* GetSocket();
	void SetSocket(CSocket* socket);

public:

	void Disconnect();

private:
	CSendPolicy* m_SendPolicy;
	CLoginPolicy* m_LoginPolicy;
};

