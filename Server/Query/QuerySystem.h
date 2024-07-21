#pragma once

#include "Base/Singleton.h"

class CQuerySystem : public CSingleton<CQuerySystem>
{
public:
	void SendQuery();
};

#define g_QuerySystem CSingleton<CQuerySystem>::GetInstance()