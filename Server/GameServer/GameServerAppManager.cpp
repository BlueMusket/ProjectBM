#include "GameServerAppManager.h"
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

    // window 생성?
    // 엑셀 데이터들 로딩
    {

    }

    return result;
}