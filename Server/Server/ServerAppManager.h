#pragma once

#include "Network/NetworkAppManager.h"

class CServerAppManager : public CNetworkAppManager
{
public:
	virtual bool Setup();
};

