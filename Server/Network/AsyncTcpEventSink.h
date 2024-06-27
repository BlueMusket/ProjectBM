#pragma once
#include "AsyncEventSink.h"

class CAsyncTcpEvent;
class CAsyncTcpEventSink : public CAsyncEventSink
{
public:
	CAsyncTcpEventSink();
	virtual ~CAsyncTcpEventSink();

public:
	virtual void OnAcceptEvent(CAsyncTcpEvent* tcpEvent);
	virtual void OnConnectEvent(CAsyncTcpEvent* tcpEvent);
	virtual void OnReceiveEvent(bool result, int ioByteSize, CAsyncTcpEvent* tcpEvent);
	virtual void OnSendEvent(CAsyncTcpEvent* tcpEvent);
	virtual void OnDisconnectEvent(CAsyncTcpEvent* tcpEvent);
};

