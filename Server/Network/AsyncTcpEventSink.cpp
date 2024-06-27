#include "AsyncTcpEventSink.h"
#include "AsyncTcpEvent.h"

CAsyncTcpEventSink::CAsyncTcpEventSink()
{
}

CAsyncTcpEventSink::~CAsyncTcpEventSink()
{
}

void CAsyncTcpEventSink::OnAcceptEvent(CAsyncTcpEvent* tcpEvent)
{
}

void CAsyncTcpEventSink::OnConnectEvent(CAsyncTcpEvent* tcpEvent)
{
}

void CAsyncTcpEventSink::OnReceiveEvent(bool result, int ioByteSize, CAsyncTcpEvent* tcpEvent)
{
}

void CAsyncTcpEventSink::OnSendEvent(CAsyncTcpEvent* tcpEvent)
{
}

void CAsyncTcpEventSink::OnDisconnectEvent(CAsyncTcpEvent* tcpEvent)
{
}