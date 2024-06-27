#pragma once

class CAsyncEvent;

/// <summary>
/// 서버별 연결 정책을 담당한다.
/// Lib별로 구현되며 함수 호출, 또는 ServerPeer로의 전달을 담당한다.
/// </summary>
class CLinkPolicy
{
public:
	CLinkPolicy();
	virtual ~CLinkPolicy();

public:
	virtual void Setup() = 0;
	virtual bool Send(CAsyncEvent* sendEvent) = 0;
};