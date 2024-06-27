#pragma once
#include "AsyncEvent.h"

class CSocket;
class CAsyncEventSink;
class CSendPolicy;
class CAsyncTcpEvent : public CAsyncEvent
{
public:
	enum class EventType
	{
		  Accept = 0
		, Send
		, Receive
		, Connect
		, Disconnect
		, Count
	};
public:
	CAsyncTcpEvent(const EventType type);
	virtual ~CAsyncTcpEvent();

public:
	virtual void Execute(bool result, int ioByteSize, CAsyncEventSink* sink);

public:
	EventType GetType() { return m_Type; }
	CSocket* GetSocket() const { return m_Socket; };
	void SetSocket(CSocket* socket) { m_Socket = socket; }

	int GetProceedingSize() const { return m_ProceedingSize; }
	void SetProceedingSize(int proceedingSize) { m_ProceedingSize = proceedingSize; }
	const int GetMaxBufferSize() const { return m_MaxBufferSize; }
	
	uint8_t* GetBuffer() { return m_Buffer; };
	void SetBuffer(uint8_t* buffer) { m_Buffer = buffer; };

	void CleanBuffer();
	WSABUF* GetWsaBuffer() { return &m_WsaBuffer; };
	
private:
	CSocket* m_Socket;
	EventType m_Type;

	uint8_t* m_Buffer;

	// event가 다루는 버퍼의 최대 사이즈
	int m_MaxBufferSize;

	WSABUF m_WsaBuffer;

	// event가 진행중인 크기
	int m_ProceedingSize;
};