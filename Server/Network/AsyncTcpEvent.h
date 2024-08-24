#pragma once
#include "AsyncEvent.h"
#include "Base/Pool.h"

class CSocket;
class CAsyncEventSink;
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

private:
	CSocket* m_Socket;
	EventType m_Type;

	uint8_t* m_Buffer;

	// event가 다루는 버퍼의 최대 사이즈
	int m_MaxBufferSize;

	WSABUF m_WsaBuffer;

	// event가 진행중인 크기
	int m_ProceedingSize;

public:
	CAsyncTcpEvent(const EventType type, int bufferSize);
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
};


// 풀링 처리 hpp로 옮길까..?
template<>
struct Is_UsePool<CAsyncTcpEvent> : std::true_type {};

template<>
class ObjectPool<CAsyncTcpEvent> 
{
private:
	static std::map<int, CPoolArray<CAsyncTcpEvent, CLockFreePool<CAsyncTcpEvent>, 4>*> m_Pools;

	static int GetNextPowerOfTwo(int n)
	{
		int power = MIN_PACKET_SIZE;
		while (power < n && power < MAX_PACKET_SIZE)
		{
			power *= 2;
		}
		return power;
	}

	static CAsyncTcpEvent* Get(CAsyncTcpEvent::EventType type, int bufferSize)
	{
		int actualSize = GetNextPowerOfTwo(bufferSize);
		if (actualSize > MAX_PACKET_SIZE)
		{
			return nullptr;
		}

		return m_Pools[actualSize]->Get(type, bufferSize);
	}

	static void Put(CAsyncTcpEvent* item)
	{
		if (!item)
		{
			return;
		}

		auto it = m_Pools.find(item->GetMaxBufferSize());
		if (it != m_Pools.end())
		{
			it->second->Put(item);
		}
		else
		{
			delete item;  // If we don't have a pool for this size, delete the event
		}
	}
public:
	template<typename... Types>
	static CAsyncTcpEvent* Allocate(Types&&... args)
	{
		return Get(std::forward<Types>(args)...);
	}

	static void Deallocate(CAsyncTcpEvent* item)
	{
		Put(item);
	}
};