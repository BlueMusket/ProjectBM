#pragma once
#include "Base/System.h"
#include "PeerListener.h"

class CListenSystem : public CSystem
{
public:
	CListenSystem();
	virtual ~CListenSystem();

	void Init(CPeerListener* listener);
	void Start();
private:
	CPeerListener* m_Listener;
};

typedef CSingleton<CListenSystem> g_ListenSystem;