#include "GamePeerListener.h"
#include "GamePeer.h"

CGamePeerListener::CGamePeerListener() 
{
    // 생성자 구현
}

CGamePeerListener::~CGamePeerListener() 
{
    // 소멸자 구현
}

/// <summary>
/// 리스너를 시작합니다.
/// </summary>
void CGamePeerListener::Start()
{
    __super::Start();  // 부모 클래스의 Start 함수 호출
}

/// <summary>
/// 새로운 피어를 생성합니다.
/// </summary>
/// <returns> 생성된 피어 객체 </returns>
CPeer* CGamePeerListener::CreatePeer()
{
    return New(CGamePeer);
}

/// <summary>
/// Accept 이벤트를 받았을 때 호출됩니다.
/// </summary>
/// <param name="tcpEvent"> TCP 이벤트 객체 </param>
void CGamePeerListener::OnAcceptEvent(CAsyncTcpEvent* tcpEvent)
{
    __super::OnAcceptEvent(tcpEvent);  // 부모 클래스의 OnAcceptEvent 함수 호출
}