#pragma once
#include "Base/Singleton.h"

class CAsyncTimerEvent;
class CTimerShard : public CSingleton<CTimerShard>
{
public:
	virtual bool Setup() override;

private:
	tbb::concurrent_queue<CAsyncTimerEvent*> m_EventShard;
};

