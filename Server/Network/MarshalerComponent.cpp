#include "MarshalerComponent.h"
#include "PacketHandler.h"
#include "HandlerRegistry.h"
#include "Packet.h"
#include "Peer.h"

CMarshalerComponent::CMarshalerComponent(CEntity* owner)
	: CComponent(owner)
{
}

CMarshalerComponent::~CMarshalerComponent()
{

}
int CMarshalerComponent::UnMarshal(CPeer* peer, uint8_t* buffer, int ioByte)
{
	if (ioByte < sizeof(PacketHeader))
	{
		return 0;
	}

	// 암호화 여부
	
	// 패킷 처리
	PacketId_t id;
	PacketSize_t size;
	CPacket::GetId(buffer, id);
	CPacket::GetSize(buffer, size);

	if (ioByte < size)
	{
		return 0;
	}

	CHandler* handler = g_HandlerRegistry->Find(id);

	if (nullptr == handler) 
	{
		return 0;
	}

	uint8_t* packetBody = nullptr;
	CPacket::GetBody(buffer, packetBody);

	// 패킷 핸들러 처리
	return handler->Execute(peer, packetBody, size);
}
