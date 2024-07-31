#pragma once
#include "Base/Entity.h"
#include "Base/Object.h"
/// <summary>
/// AsyncEvent를 전달한 객체
/// </summary>

enum AsyncRefType
{
	ASYNC_REF_TYPE_RECV = 0, // recv중
	ASYNC_REF_TYPE_SEND, // send 중
	ASYNC_REF_TYPE_EVENT, // 이벤트 실행중
	ASYNC_REF_TYPE_TIMER,
	ASYNC_REF_TYPE_MAX
};


class CAsyncEventSink : public CEntity, public CObject
{
public:
	CAsyncEventSink();
	virtual ~CAsyncEventSink();

private:
	std::array<CAtomic<int>, ASYNC_REF_TYPE_MAX> m_RefCountArray; ///< 참조 카운트 배열
	CAtomic<int> m_RefCount; ///< 전체 참조 카운트

public:
	/// <summary>
/// 특정 타입의 참조 카운트를 증가시킵니다.
/// </summary>
/// <param name="type"> 참조 타입 </param>
	void IncreaseRefCount(AsyncRefType type);

	/// <summary>
	/// 특정 타입의 참조 카운트를 감소시킵니다.
	/// </summary>
	/// <param name="type"> 참조 타입 </param>
	void DecreaseRefCount(AsyncRefType type);

	/// <summary>
	/// 특정 타입의 참조 카운트를 가져옵니다.
	/// </summary>
	/// <param name="type"> 참조 타입 </param>
	/// <returns> 참조 카운트 </returns>
	int GetRefCount(AsyncRefType type = ASYNC_REF_TYPE_MAX) const;

};