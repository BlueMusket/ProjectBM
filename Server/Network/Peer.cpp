#include "Peer.h"
#include "AsyncTcpComponent.h"
#include "MarshalerComponent.h"
#include "AsyncTcpEvent.h"
#include "AsyncDispatcher.h"
#include "SendPolicy.h"
#include "Server/LoginPolicy.h"
#include "PeerFacade.h"


std::atomic<int> CPeer::s_InstanceCount = 0;

namespace
{	
	std::atomic<PeerId_t> s_IdIndexer = DEFAULT_PEER_ID;
	PeerId_t GetNextId()
	{
		return s_IdIndexer.fetch_add(1);
	}
}

CPeer::CPeer()
	: m_Id(GetNextId())
	, m_RefCount(0)
{
	// 각 요소를 0으로 초기화
	for (auto& refCount : m_RefCountArray) 
	{
		refCount.Store(0);
	}

	InsertComponent<CAsyncTcpComponent>();
	InsertComponent<CMarshalerComponent>();

	m_SendPolicy = New(CSendPolicy);

	s_InstanceCount.fetch_add(1);
}

CPeer::~CPeer()
{
	s_InstanceCount.fetch_add(-1);
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

/// <summary>
/// 피어 ID를 가져옵니다.
/// </summary>
/// <returns> 피어 ID </returns>
PeerId_t CPeer::GetId() const
{
	return m_Id;
}

/// <summary>
/// 특정 타입의 참조 카운트를 증가시킵니다.
/// </summary>
/// <param name="type"> 참조 타입 </param>
void CPeer::IncreaseRefCount(PeerRefType type)
{
	m_RefCountArray[type].Increase();
	m_RefCount.Increase();
}

/// <summary>
/// 특정 타입의 참조 카운트를 감소시킵니다.
/// </summary>
/// <param name="type"> 참조 타입 </param>
void CPeer::DecreaseRefCount(PeerRefType type)
{
	m_RefCountArray[type].Decrease();
	m_RefCount.Decrease(1);
}

/// <summary>
/// 특정 타입의 참조 카운트를 가져옵니다.
/// </summary>
/// <param name="type"> 참조 타입 </param>
/// <returns> 참조 카운트 </returns>
int CPeer::GetRefCount(PeerRefType type/* = PEER_REF_TYPE_MAX*/) const
{
	return PEER_REF_TYPE_MAX == type ? m_RefCount.Load() : m_RefCountArray[type].Load();
}