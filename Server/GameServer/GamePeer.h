#pragma once
#include "Server/ServerPeer.h"

class CGamePeer : public CServerPeer
{
public:
    CGamePeer();
    virtual ~CGamePeer();

public:
    /// <summary>
    /// 소켓 통신에서 IO를 받았을 때 호출
    /// </summary>
    /// <param name="result"> IO 작업의 성공 여부 </param>
    /// <param name="ioByteSize"> 처리된 바이트 수 </param>
    /// <param name="tcpEvent"> 받은 이벤트 </param>
    /// <returns> 성공 시 처리한 바이트 수 </returns>
    virtual void OnReceiveEvent(bool result, int ioByteSize, CAsyncTcpEvent* tcpEvent) override;

    /// <summary>
    /// Accept 성공 시 호출되는 함수
    /// </summary>
    /// <param name="tcpEvent"> accept 시 받은 이벤트 </param>
    virtual void OnAccepted(CAsyncTcpEvent* tcpEvent) override;
};

