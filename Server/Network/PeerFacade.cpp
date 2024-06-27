#include "PeerFacade.h"
#include "AsyncEventSink.h"
#include "Peer.h"

void CPeerFacade::Disconnected(CAsyncEventSink* sink)
{
	CPeer* peer = static_cast<CPeer*>(sink);

	peer->Disconnect();
}
