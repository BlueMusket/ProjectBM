#pragma once
#include "Base/Object.h"
#include "AsyncTcpEventSink.h"
#include "PeerDef.h"

class CSendPolicy;
class CSocket;
class CAsyncTcpEvent;
class CPeer;

typedef std::shared_ptr<CPeer> CPeerPtr;
class CPeer : public CAsyncTcpEventSink
{
public:
	CPeer();
	virtual ~CPeer();

private:
	PeerId_t m_Id; ///< 피어 ID

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

private:
	static CAtomic<int> s_InstanceCount; ///< Peer의 수

public:
	CAsyncTcpEventSink* ToSink() { return reinterpret_cast<CAsyncTcpEventSink*>(this); };
	CObject* ToObject() { return reinterpret_cast<CObject*>(this); };
};