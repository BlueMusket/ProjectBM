#pragma once

#include "Network/NetworkAppManager.h"

class CServerAppManager : public CNetworkAppManager
{
public:
	CServerAppManager() {};
	virtual ~CServerAppManager() {};

public:
	virtual bool Setup();
};

