#pragma once

#include "Network/Peer.h"

class CAsyncTcpEvent;

/// <summary>
/// Peer의 연결을 담당할 Peer
/// </summary>
class CPeerListener : public CPeer
{
public:
	CPeerListener();
	virtual ~CPeerListener();

public:
	virtual void Start();
	virtual CPeer* CreatePeer();
	void PostAccept(CAsyncTcpEvent* acceptEvent);
public:
	/// <summary>
	/// Accept 이벤트를 받았을 때 호출됩니다.
	/// </summary>
	/// <param name="tcpEvent"> TCP 이벤트 객체 </param>
	virtual void OnAcceptEvent(CAsyncTcpEvent* tcpEvent);
};

