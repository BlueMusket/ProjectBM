#pragma once

class CPeer;
class CAsyncTcpEvent;

class CSendPolicy
{
public:
	CSendPolicy();
	~CSendPolicy();

public:
	bool PostSend(CPeer* peer, CAsyncTcpEvent* sendEvent);
};

