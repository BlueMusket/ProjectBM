#pragma once
#include "Packet.h"
#include "PacketBase.h"
#include "AsyncTcpEvent.h"

template<typename T>
class CPacketWriter
{
public:
	CPacketWriter()
	{
		m_Packet = New(T);
		// 유효성 검증 같은걸 해야하나?
	}

	~CPacketWriter()
	{
	}

public:
	T* operator->()
	{
		return m_Packet;
	}

	CAsyncTcpEvent* operator()()
	{
		CAsyncTcpEvent* sendEvent = New(CAsyncTcpEvent, CAsyncTcpEvent::EventType::Send);
		sendEvent->SetBuffer(MakeBuffer());

		return sendEvent;
	}

private:
	uint8_t* MakeBuffer()
	{
		uint8_t* bodyBuffer = m_Packet->Pack(); // 패킷을 바이너리로

		if (nullptr == bodyBuffer)
		{
			return nullptr;
		}

		const int bodySize = sizeof(bodyBuffer);
		const int size = bodySize + sizeof(PacketHeader);
		uint8_t* packetBuffer = new uint8_t[size];

		// 패킷의 header 부분 설정
		CPacket::SetSize(packetBuffer, size);
		CPacket::SetId(packetBuffer, T::GetHash());
		CPacket::SetCompressType(packetBuffer, 0);
		CPacket::SetEncryptionType(packetBuffer, 0);

		// 컨텐츠에서 사용할 데이터인 Body 설정
		CPacket::SetBody(packetBuffer, bodyBuffer, bodySize);

		return packetBuffer;
	}

private:
	T* m_Packet;
};

