#include "ServerAppManager.h"
#include "Network/AsyncDispatcher.h"
#include "Network/ListenSystem.h"
#include "ServerListener.h"
#include "Base/ObjectRecycler.h"

bool CServerAppManager::Setup()
{
	bool result = __super::Setup();

    g_AsyncDispatcher->Start();
    //데이터 세팅
    g_ListenSystem->Init(New(CServerListener));
    g_ListenSystem->Start();

    g_AsyncDispatcher->Join();

    g_ObjectRecycler->Start();

	return result;
}