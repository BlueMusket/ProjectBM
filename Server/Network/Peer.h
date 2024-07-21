#pragma once
#include "Base/Object.h"
#include "AsyncTcpEventSink.h"
#include "PeerDef.h"

class CSendPolicy;
class CSocket;
class CAsyncTcpEvent;
class CPeer;

typedef std::shared_ptr<CPeer> CPeerPtr;
class CPeer : public CAsyncTcpEventSink, public CObject
{
public:
	CPeer();
	virtual ~CPeer();

private:
	PeerId_t m_Id; ///< 피어 ID
	CPeerPtr m_Self; ///< 자신의 Shared
	std::array<CAtomic<int>, PEER_REF_TYPE_MAX> m_RefCountArray; ///< 참조 카운트 배열
	CAtomic<int> m_RefCount; ///< 전체 참조 카운트

	CSendPolicy* m_SendPolicy;
public:

	/// <summary>
	/// 소켓 통신에서 IO를 받았을때 호출
	/// </summary>
	/// <param name="tcpEvent"> 받은 이벤트 </param>
	/// <returns>성공시 처리한 바이트 수</returns>
	virtual void OnReceiveEvent(bool result, int ioByteSize, CAsyncTcpEvent* tcpEvent);

	/// <summary>
	/// Accept 성공시 호출되는 함수
	/// </summary>
	/// <param name="tcpEvent"> accept시 받은 이벤트 </param>
	virtual void OnAccepted(CAsyncTcpEvent* tcpEvent);
public:

	// 패킷을 보내기 위한 사전 작업
	bool PostSend(CAsyncTcpEvent* sendEvent);

	// 패킷을 실제로 보낸다.
	bool Send(CAsyncTcpEvent* sendEvent);

	CSocket* GetSocket();
	void SetSocket(CSocket* socket);

	void Disconnect();

public:
	/// <summary>
	/// 피어 ID를 가져옵니다.
	/// </summary>
	/// <returns> 피어 ID </returns>
	PeerId_t GetId() const;

	/// <summary>
	/// 특정 타입의 참조 카운트를 증가시킵니다.
	/// </summary>
	/// <param name="type"> 참조 타입 </param>
	void IncreaseRefCount(PeerRefType type);

	/// <summary>
	/// 특정 타입의 참조 카운트를 감소시킵니다.
	/// </summary>
	/// <param name="type"> 참조 타입 </param>
	void DecreaseRefCount(PeerRefType type);

	/// <summary>
	/// 특정 타입의 참조 카운트를 가져옵니다.
	/// </summary>
	/// <param name="type"> 참조 타입 </param>
	/// <returns> 참조 카운트 </returns>
	int GetRefCount(PeerRefType type = PEER_REF_TYPE_MAX) const;

	/// <summary>
	 /// 자신에 대한 shared_ptr를 반환합니다.
	 /// </summary>
	 /// <returns> shared_ptr로 된 자신 </returns>
	CPeerPtr GetSelf();

private:
	static std::atomic<int> s_InstanceCount; ///< Peer의 수

public:
	CAsyncTcpEventSink* ToSink() { return reinterpret_cast<CAsyncTcpEventSink*>(this); };
	CObject* ToObject() { return reinterpret_cast<CObject*>(this); };
};