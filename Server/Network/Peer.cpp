#include "Peer.h"
#include "AsyncTcpComponent.h"
#include "MarshalerComponent.h"
#include "AsyncTcpEvent.h"
#include "AsyncDispatcher.h"
#include "SendPolicy.h"
#include "PeerFacade.h"

CPeer::CPeer()
{
	InsertComponent<CAsyncTcpComponent>();
	InsertComponent<CMarshalerComponent>();

	m_SendPolicy = New(CSendPolicy);
}

CPeer::~CPeer()
{
}

void CPeer::OnReceiveEvent(bool result, int ioByteSize, CAsyncTcpEvent* tcpEvent)
{
	CMarshalerComponent* marshaler = GetComponent<CMarshalerComponent>();

	if (true == result && 0 < ioByteSize)
	{
		int total = tcpEvent->GetProceedingSize() + ioByteSize;
		int handled = 0;

		while (handled < total)
		{
			int result = marshaler->UnMarshal(this, tcpEvent->GetBuffer() + handled, total - handled);

			if (result <= 0)
			{
				break;
			}
			else
			{
				handled += result;
			}
		}

		// 처리 못한 byte는 앞으로 넘겨준다.
		memmove(tcpEvent->GetBuffer(), tcpEvent->GetBuffer() + handled, total - handled);

		tcpEvent->SetProceedingSize(total - handled);

	}
	else
	{
		CPeerFacade::Disconnected(this);
	}
	
	CAsyncTcpComponent* tcpComponent = GetComponent<CAsyncTcpComponent>();
	tcpComponent->Recv();
}

void CPeer::OnAccepted(CAsyncTcpEvent* tcpEvent)
{
	CAsyncTcpComponent* component = GetComponent<CAsyncTcpComponent>();
	if (nullptr == component)
	{
		return;
	}

	component->OnAccepted(tcpEvent);

	component->Recv();
}

bool CPeer::PostSend(CAsyncTcpEvent* sendEvent)
{
	return m_SendPolicy->PostSend(this, sendEvent);;
}

bool CPeer::Send(CAsyncTcpEvent* sendEvent)
{
	return GetComponent<CAsyncTcpComponent>()->Send(sendEvent);
}

CSocket* CPeer::GetSocket()
{
	return GetComponent<CAsyncTcpComponent>()->GetSocket();
}

void CPeer::SetSocket(CSocket* socket)
{
	GetComponent<CAsyncTcpComponent>()->SetSocket(socket);
}

void CPeer::Disconnect()
{
	CAsyncTcpComponent* component = GetComponent<CAsyncTcpComponent>();
	if (nullptr == component)
	{
		return;
	}

	component->Disconnect();
}
