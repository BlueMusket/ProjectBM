#pragma once

#include <WS2tcpip.h>

class CAsyncEventSink;
class CAsyncEvent
{
public:
	struct Tag : public OVERLAPPED
	{
	public:
		CAsyncEvent* m_Owner;
	};

	CAsyncEvent();
	virtual ~CAsyncEvent();

public:
	Tag& GetTag();

public:
	virtual void Execute(bool result, int ioByteSize, CAsyncEventSink* sink);

private:
	Tag m_Body;
};

