#pragma once

#include "Server/ServerAppManager.h"

class CGameServerAppManager : public CServerAppManager
{
public:
	virtual bool Setup() override;
};

