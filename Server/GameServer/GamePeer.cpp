#include "GamePeer.h"

CGamePeer::CGamePeer()
{
    // 생성자 구현
}

CGamePeer::~CGamePeer()
{
    // 소멸자 구현
}

/// <summary>
/// 소켓 통신에서 IO를 받았을 때 호출
/// </summary>
/// <param name="result"> IO 작업의 성공 여부 </param>
/// <param name="ioByteSize"> 처리된 바이트 수 </param>
/// <param name="tcpEvent"> 받은 이벤트 </param>
/// <returns> 성공 시 처리한 바이트 수 </returns>
void CGamePeer::OnReceiveEvent(bool result, int ioByteSize, CAsyncTcpEvent* tcpEvent)
{
    __super::OnReceiveEvent(result, ioByteSize, tcpEvent);  // 부모 클래스의 OnReceiveEvent 함수 호출
    // 추가 구현
}

/// <summary>
/// Accept 성공 시 호출되는 함수
/// </summary>
/// <param name="tcpEvent"> accept 시 받은 이벤트 </param>
void CGamePeer::OnAccepted(CAsyncTcpEvent* tcpEvent)
{
    __super::OnAccepted(tcpEvent);  // 부모 클래스의 OnAccepted 함수 호출
    // 추가 구현
}