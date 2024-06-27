#pragma once
#include "Packet.h"
#include "PacketBase.h"

template<typename T>
class CPacketReader
{
public:
	CPacketReader(uint8_t* buffer)
	{

		// 컨텐츠에서 사용할 데이터인 Body 설정
		uint8_t* bodyBuffer = nullptr;
		CPacket::GetBody(buffer, bodyBuffer);

		m_Packet = New(T);
		// 유효성 검증 같은걸 해야하나?
		m_Packet->UnPack(bodyBuffer);
	}

	~CPacketReader()
	{
	}

public:
	T* operator->()
	{
		return m_Packet;
	}
private:
	T* m_Packet;
};

