#pragma once
#include "Network/PeerListener.h"

class CServerListener : public CPeerListener
{
public:
	CServerListener();
	~CServerListener();

public:
	virtual void Start() override;

	/// <summary>
	/// Accept 이벤트를 받았을 때 호출됩니다.
	/// </summary>
	/// <param name="tcpEvent"> TCP 이벤트 객체 </param>
	virtual void OnAcceptEvent(CAsyncTcpEvent* tcpEvent);
};

