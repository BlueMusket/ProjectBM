#pragma once

#include "Base/Singleton.h"

class CQuerySystem : public CSingleton<CQuerySystem>
{
public:
	void SendQuery();
};

typedef CSingleton<CQuerySystem> g_QuerySystem;