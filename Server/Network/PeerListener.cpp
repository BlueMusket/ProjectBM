#include "PeerListener.h"

#include "AsyncDispatcher.h"
//#include "AsyncEvent.h"
#include "AsyncTcpComponent.h"
#include "AsyncTcpEvent.h"
#include "Socket.h"
#include "PeerRegister.h"

CPeerListener::CPeerListener()
{

}

CPeerListener::~CPeerListener()
{
}

void CPeerListener::Start()
{
	
}

CPeer* CPeerListener::CreatePeer()
{
	// 여긴 들어오면 안된다.
	return nullptr;
}

void CPeerListener::PostAccept(CAsyncTcpEvent* acceptEvent)
{
	CAsyncTcpComponent* component = GetComponent<CAsyncTcpComponent>();
	if (nullptr == component)
	{
		return;
	}

	CSocket* newSocket = New(CSocket);
	acceptEvent->SetSocket(newSocket);

	if (true == component->Accept(newSocket, acceptEvent))
	{
		// 추가 처리를 위해 이벤트를 Enqueue
		g_AsyncDispatcher::GetInstance()->Enqueue(nullptr, &acceptEvent->GetTag());
	}
	else
	{
		DWORD lastError = GetLastError();
		if (ERROR_IO_PENDING == lastError)
		{
			// 성공
		}
		else
		{
			// 실패
		}

	}
}

/// <summary>
/// Accept 이벤트를 받았을 때 호출됩니다.
/// </summary>
/// <param name="tcpEvent"> TCP 이벤트 객체 </param>
void CPeerListener::OnAcceptEvent(CAsyncTcpEvent* tcpEvent)
{
	CPeer* newPeer = CreatePeer();
	newPeer->SetSocket(tcpEvent->GetSocket());
	
	newPeer->OnAccepted(tcpEvent);

	g_AsyncDispatcher::GetInstance()->Associate(newPeer, newPeer->GetSocket());

	g_PeerRegister::GetInstance()->AddPeer(newPeer);


	// 이벤트 다시 재활용한다.
	tcpEvent->SetSocket(nullptr);
	tcpEvent->CleanBuffer();
	
	PostAccept(tcpEvent);
}