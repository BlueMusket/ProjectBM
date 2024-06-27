#pragma once
#include "Network/PeerListener.h"

class CServerListener : public CPeerListener
{
public:
	CServerListener();
	~CServerListener();

public:
	virtual void Start() override;
};

