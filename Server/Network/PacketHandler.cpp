#include "PacketHandler.h"
#include "Peer.h"

CPacketHandler::CPacketHandler()
{
}

CPacketHandler::~CPacketHandler()
{
}

int CPacketHandler::Execute(CPeer* peer, uint8_t* buffer, int len)
{
	// 최종적인 컨텐츠로직 전 검증처리
	return 0;
}
