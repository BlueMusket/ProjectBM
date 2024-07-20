#pragma once
#include "AsyncEvent.h"

class CAsyncEventSink;

class CAsyncTimerEvent : public CAsyncEvent
{
public:
	virtual void Execute(bool result, int ioByteSize, CAsyncEventSink* sink);
};

