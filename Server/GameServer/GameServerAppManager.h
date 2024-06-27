#pragma once

#include "Server/ServerAppManager.h"

class CGameServerAppManager : public CServerAppManager
{
public:
	CGameServerAppManager();
	virtual ~CGameServerAppManager();

public:
	virtual bool Setup() override;
};

