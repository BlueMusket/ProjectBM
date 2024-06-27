#include "Task.h"

CTask::CTask(const Callback& callback)
	: m_Callback(callback)
{
}

CTask::~CTask()
{

}

void CTask::OnCallbackEvent()
{
	m_Callback();
}