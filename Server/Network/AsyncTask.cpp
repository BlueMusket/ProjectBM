#include "AsyncTask.h"
#include "AsyncDispatcher.h"
#include "AsyncEventSink.h"

CAsyncTask::CAsyncTask(const Callback& callback)
	: CTask(callback)
{
}

CAsyncTask::~CAsyncTask()
{
}

void CAsyncTask::PostTask(CAsyncTask* task)
{
	g_AsyncDispatcher::GetInstance()->Enqueue(nullptr, &task->GetTag());
}

int CAsyncTask::Execute(CAsyncEventSink* sink)
{
	OnCallbackEvent();

	return 0;
}