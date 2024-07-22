#pragma once

#include "Base/Singleton.h"

class CQuerySystem : public CSingleton<CQuerySystem>
{
	SINGLETON_FOUNDATION(CQuerySystem)
public:
	void SendQuery();
};

#define g_QuerySystem CSingleton<CQuerySystem>::GetInstance()