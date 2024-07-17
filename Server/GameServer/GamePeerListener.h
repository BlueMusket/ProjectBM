#pragma once
#include "Network\PeerListener.h"

class CGamePeerListener : public CPeerListener
{
public:
    CGamePeerListener();
    virtual ~CGamePeerListener();

public:
    /// <summary>
    /// 리스너를 시작합니다.
    /// </summary>
    virtual void Start() override;

    /// <summary>
    /// 새로운 피어를 생성합니다.
    /// </summary>
    /// <returns> 생성된 피어 객체 </returns>
    virtual CPeer* CreatePeer() override;

public:
    /// <summary>
    /// Accept 이벤트를 받았을 때 호출됩니다.
    /// </summary>
    /// <param name="tcpEvent"> TCP 이벤트 객체 </param>
    virtual void OnAcceptEvent(CAsyncTcpEvent* tcpEvent) override;
};

