#include "ServerListener.h"
#include "Network/AsyncDispatcher.h"
//#include "Network/AsyncEvent.h"
#include "Network/AsyncTcpComponent.h"
#include "Network/AsyncTcpEvent.h"
#include "Network/Socket.h"


CServerListener::CServerListener()
{

}

CServerListener::~CServerListener()
{

}

void CServerListener::Start()
{
	CAsyncTcpComponent* component = GetComponent<CAsyncTcpComponent>();
	if (nullptr == component)
	{
		return;
	}
	component->SetSocket(New(CSocket));

	{
		sockaddr_in socketAddr;
		memset(&socketAddr, 0, sizeof(socketAddr));
		socketAddr.sin_family = AF_INET;
		socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		socketAddr.sin_port = htons(13480);
		component->Bind(socketAddr);
	}
	
	component->Listen();

	g_AsyncDispatcher::GetInstance()->Associate(this, component->GetSocket());

	// 한번에 받을 수 있는 클라이언트의 수 4
	for (int index = 0; index < 2; ++index)
	{
		CAsyncTcpEvent* acceptEvent = New(CAsyncTcpEvent, CAsyncTcpEvent::EventType::Accept);
		PostAccept(acceptEvent);
	}
}