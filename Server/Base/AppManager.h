#pragma once
#include "Singleton.h"

class CAppManager : public CSingleton<CAppManager>
{
SINGLETON_FOUNDATION(CAppManager)

public:
	virtual bool Setup();
};

