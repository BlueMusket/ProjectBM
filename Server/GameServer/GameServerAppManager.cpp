#include "GameServerAppManager.h"
#include "GamePacketHandlerSetup.h"
#include "Network/AsyncDispatcher.h"
#include "Network/ListenSystem.h"
#include "Network/Socket.h"
#include "Server/ServerListener.h"
#include "Base/ObjectRecycler.h"


bool CGameServerAppManager::Setup()
{
    {
        Network::Setup();
    }

    // 핸들러 추가
    {
        GamePacketHandlerSetup::Setup();
    }

    // window 생성?
    // 엑셀 데이터들 로딩
    {
        g_AsyncDispatcher->Start();
        g_ListenSystem->Init(New(CServerListener));
        g_ListenSystem->Start();

        g_ObjectRecycler->Start();
    }

    return true;
}