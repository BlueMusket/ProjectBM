#pragma once
#include "Base/Task.h"
#include "AsyncEvent.h"

class AsyncEventSink;
class CAsyncTask : public CTask, public CAsyncEvent
{
public:
	CAsyncTask(const Callback& callback);
	virtual ~CAsyncTask();

public:
	static void PostTask( CAsyncTask* task );

public:
	virtual int Execute(CAsyncEventSink* sink);
};

