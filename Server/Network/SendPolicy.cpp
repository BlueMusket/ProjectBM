#include "SendPolicy.h"
#include "Peer.h"
#include "AsyncTcpEvent.h"

CSendPolicy::CSendPolicy()
{
}

CSendPolicy::~CSendPolicy()
{
}

bool CSendPolicy::PostSend(CPeer* peer, CAsyncTcpEvent* sendEvent)
{
	// 일단 그냥 보낸다.
	return peer->Send(sendEvent);
}