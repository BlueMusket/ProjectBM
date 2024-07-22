#include "GameServerAppManager.h"
#include "Network/AsyncDispatcher.h"
#include "Network/ListenSystem.h"
#include "Server/ServerListener.h"
#include "GamePacketHandlerSetup.h"

bool CGameServerAppManager::Setup()
{
    bool result = __super::Setup();
    if (false == result)
    {
        return false;
    }
    // 핸들러 추가
    {
        GamePacketHandlerSetup::Setup();
    }

    g_AsyncDispatcher->Start();
    //데이터 세팅
    g_ListenSystem->Init(New(CServerListener));
    g_ListenSystem->Start();

    g_AsyncDispatcher->Join();


    return result;
}