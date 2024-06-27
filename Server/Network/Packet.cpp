#include "Packet.h"
#include <string>
#include <Windows.h>

void CPacket::GetSize(const uint8_t* buffer, PacketSize_t& outValue)
{
	memcpy(&outValue, buffer, sizeof(PacketSize_t));
}

void CPacket::SetSize(uint8_t* outBuffer, const PacketSize_t& value)
{
	memcpy(outBuffer, &value, sizeof(PacketSize_t));
}

void CPacket::GetId(const uint8_t* buffer, PacketId_t& outValue)
{
	memcpy(&outValue, buffer + 2, sizeof(PacketId_t));
}

void CPacket::SetId(uint8_t* outBuffer, const PacketId_t& value)
{
	memcpy(outBuffer + 2, &value, sizeof(PacketId_t));
}

void CPacket::GetCompressType(const uint8_t* buffer, CompressType_t& outValue)
{
	memcpy(&outValue, buffer + 4, sizeof(CompressType_t));
}

void CPacket::SetCompressType(uint8_t* outBuffer, const CompressType_t& value)
{
	memcpy(outBuffer + 4, &value, sizeof(CompressType_t));
}

void CPacket::GetEncryptionType(const uint8_t* buffer, EncryptionType_t& outValue)
{
	memcpy(&outValue, buffer + 5, sizeof(EncryptionType_t));
}

void CPacket::SetEncryptionType(uint8_t* outBuffer, const EncryptionType_t& value)
{
	memcpy(outBuffer + 5, &value, sizeof(EncryptionType_t));
}

void CPacket::GetBody(const uint8_t* buffer, uint8_t* outBody)
{
	PacketSize_t size = 0;
	CPacket::GetSize(buffer, size);

	PacketSize_t bodySize = size - sizeof(PacketHeader);
	outBody = new uint8_t[bodySize];

	memcpy(&outBody, buffer + 6, bodySize);
}

void CPacket::SetBody(uint8_t* outBuffer, const uint8_t* body, const int len)
{
	memcpy(outBuffer + 6, &body, len);
}

int CPacket::FindPacket(int value)
{
	return 0;
}
