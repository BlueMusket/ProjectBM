#pragma once
#include "Handler.h"

class CPeer;
class CPacketHandler : public CHandler
{
public:
	CPacketHandler();
	virtual ~CPacketHandler();

public:
	virtual int Execute( CPeer* peer, uint8_t* buffer, int len) override;
};



#define PACKET_HANDLER_CLASS(name)\
class name##Handler : public CPacketHandler\
{\
public:\
	name##Handler() {} \
	virtual ~name##Handler() {} \
	static std::string	GetName() { return #name; }\
	static int			GetHash() { return std::hash<std::string>()(#name); } \
	static CPacketHandler* GetClone() \
	{ \
		return New(name##Handler); \
	}\
public:\
	virtual int Execute( CPeer* peer, uint8_t* buffer, int len) final;\
};