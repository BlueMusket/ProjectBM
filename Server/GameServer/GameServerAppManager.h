#pragma once

#include "Server/ServerAppManager.h"

class CGameServerAppManager : public CSingleton<CGameServerAppManager>
{
public:
	bool Setup();
};

#define g_GameServerAppManager CSingleton<CGameServerAppManager>::GetInstance()