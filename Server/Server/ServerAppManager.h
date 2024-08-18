#pragma once

#include "Network/NetworkAppManager.h"

class CServerAppManager : public CSingleton<CServerAppManager>
{
SINGLETON_FOUNDATION(CServerAppManager)

public:
	bool Setup();
};

