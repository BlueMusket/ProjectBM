#pragma once
#include "Base/AppManager.h"

class CNetworkAppManager : public CAppManager
{
	SINGLETON_FOUNDATION(CNetworkAppManager)
public:
	virtual bool Setup()  override;
};

