#pragma once
#include "Base/Object.h"
#include "Network/Peer.h"

/// <summary>
/// 서버에서 다루는 유저의 정보
/// </summary>
class CUser : public CObject
{
private:
	CPeer* m_Peer;
};

