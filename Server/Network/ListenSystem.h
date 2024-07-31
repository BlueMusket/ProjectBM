#pragma once
#include "Base/Singleton.h"
#include "PeerListener.h"

class CListenSystem : public CSingleton<CListenSystem>
{
	SINGLETON_FOUNDATION(CListenSystem)

public:
	void Init(CPeerListener* listener);
	void Start();

private:
	CPeerListener* m_Listener;
};

#define g_ListenSystem CSingleton<CListenSystem>::GetInstance()