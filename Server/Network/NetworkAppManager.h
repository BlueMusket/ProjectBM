#pragma once
#include "Base/AppManager.h"

class CNetworkAppManager : public CAppManager
{
public:
	CNetworkAppManager() {};
	virtual ~CNetworkAppManager() {};

public:
	virtual bool Setup();
};

