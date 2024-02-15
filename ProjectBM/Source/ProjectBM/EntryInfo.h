// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTBM_API CEntryInfo
{
public:
	CEntryInfo();
	~CEntryInfo();

public:
	void SetSessionId(int NewSessionId) { SessionId = NewSessionId; }
	int GetSessionId() { return SessionId; }

	void SetPartyId(int NewPartyId) { PartyId = NewPartyId; }
	int GetPartyId() { return PartyId; }

	void SetUserId(int NewUserId) { UserId = NewUserId; }
	int GetUserId() { return UserId; }

private:
	int SessionId;
	int PartyId;
	int UserId;
};
