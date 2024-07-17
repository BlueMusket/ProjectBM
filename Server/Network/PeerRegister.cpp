#include "PeerRegister.h"
#include "Peer.h"

bool CPeerRegister::Setup()
{
    return true;
}

/// <summary>
/// 피어를 등록합니다.
/// </summary>
/// <param name="peer"> 등록할 피어 객체 </param>
void CPeerRegister::AddPeer(CPeer* peer)
{
    CScopeLock lock(&m_Lock);
    m_PeerMap.emplace(std::make_pair(peer->GetId(), peer));
}

/// <summary>
 /// 서버 종료시 피어들을 Disconnect 시킴
 /// </summary>
void CPeerRegister::Shutdown()
{
    CScopeLock lock(&m_Lock);
    for (auto& iter : m_PeerMap)
    {
        CPeer* peer = iter.second;
        peer->Disconnect();
    }
}