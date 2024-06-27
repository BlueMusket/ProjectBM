﻿#include "AsyncTcpEvent.h"
#include "Socket.h"
#include "AsyncTcpEventSink.h"

#define MAX_PACKET_SIZE 1024

CAsyncTcpEvent::CAsyncTcpEvent(const EventType type)
	: m_Type(type)
	, m_ProceedingSize(0)
{
	m_MaxBufferSize = MAX_PACKET_SIZE;
	m_Buffer = new uint8_t[m_MaxBufferSize]; // 일단 이렇게
	ZeroMemory(&m_WsaBuffer, sizeof(m_WsaBuffer));
}

CAsyncTcpEvent::~CAsyncTcpEvent()
{
}

void CAsyncTcpEvent::Execute(bool result, int ioByteSize, CAsyncEventSink* sink)
{
	CAsyncTcpEventSink* tcpEventSink = dynamic_cast<CAsyncTcpEventSink*>(sink);
	int byte = 0;
	switch (GetType())
	{
	case EventType::Accept:
	{
		tcpEventSink->OnAcceptEvent(this);
		break;
	}
	case EventType::Send:
	{
		tcpEventSink->OnSendEvent(this);
		break;
	}
	case EventType::Receive:
	{
		tcpEventSink->OnReceiveEvent(result, ioByteSize, this);
		break;
	}
	case EventType::Connect:
	{
		tcpEventSink->OnConnectEvent(this);
		break;
	}
	case EventType::Disconnect:
	{
		//tcpEventSink->OnReceiveEvent(this);
		break;
	}

	default:
		break;
	}
}

void CAsyncTcpEvent::CleanBuffer()
{
	ZeroMemory(m_Buffer, sizeof(m_Buffer));
}