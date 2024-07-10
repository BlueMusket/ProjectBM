// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Network/PacketBase.h"
/**
 * 
 */
class CG_Login : public CPacketBase
{
PACKET_FOUNDATION(CG_Login, PacketType::NO_DELAY)

public:
	std::string m_Name;
	std::string m_Pwd;
};