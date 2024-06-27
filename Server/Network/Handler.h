#pragma once

class CPeer;
class CHandler
{
public:
	CHandler();
	virtual ~CHandler();
public:
	virtual int Execute(CPeer* peer, uint8_t* buffer, int len);
};