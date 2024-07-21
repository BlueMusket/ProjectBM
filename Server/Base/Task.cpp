#include "Task.h"

CTask::~CTask()
{

}

void CTask::OnCallbackEvent() const
{
	m_Callback();
}