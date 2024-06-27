#include "GameServerAppManager.h"
#include "Network/AsyncDispatcher.h"
#include "Network/ListenSystem.h"
#include "Server/ServerListener.h"

CGameServerAppManager::CGameServerAppManager()
{
}

CGameServerAppManager::~CGameServerAppManager()
{
}

bool CGameServerAppManager::Setup()
{
    bool result = __super::Setup();
    if (false == result)
    {
        return false;
    }
    // 핸들러 추가
    {
        //TradeServerHandlerSetup::Setup();
    }

    g_AsyncDispatcher::GetInstance()->Start();
    //데이터 세팅
    g_ListenSystem::GetInstance()->Init(New(CServerListener));
    g_ListenSystem::GetInstance()->Start();

    g_AsyncDispatcher::GetInstance()->Join();


    return result;
}