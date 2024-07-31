#include "AsyncEventSink.h"

CAsyncEventSink::CAsyncEventSink()
	: m_RefCount(0)
{
	// 각 요소를 0으로 초기화
	for (auto& refCount : m_RefCountArray)
	{
		refCount.Store(0);
	}
}

CAsyncEventSink::~CAsyncEventSink()
{

}

/// <summary>
/// 특정 타입의 참조 카운트를 증가시킵니다.
/// </summary>
/// <param name="type"> 참조 타입 </param>
void CAsyncEventSink::IncreaseRefCount(AsyncRefType type)
{
	m_RefCountArray[type].Increase();
	m_RefCount.Increase();
}

/// <summary>
/// 특정 타입의 참조 카운트를 감소시킵니다.
/// </summary>
/// <param name="type"> 참조 타입 </param>
void CAsyncEventSink::DecreaseRefCount(AsyncRefType type)
{
	m_RefCountArray[type].Decrease();
	m_RefCount.Decrease();
}

/// <summary>
/// 특정 타입의 참조 카운트를 가져옵니다.
/// </summary>
/// <param name="type"> 참조 타입 </param>
/// <returns> 참조 카운트 </returns>
int CAsyncEventSink::GetRefCount(AsyncRefType type/* = PEER_REF_TYPE_MAX*/) const
{
	return ASYNC_REF_TYPE_MAX == type ? m_RefCount.Load() : m_RefCountArray[type].Load();
}
