// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PCEntryInfo.generated.h"
/**
 * 
 */

UCLASS(Blueprintable)
class UPCEntryInfo : public UObject
{
	GENERATED_BODY()

public:
	// UObject 리플리케이션 함수
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void Deserialize(UPCEntryInfo& NewInfo);
	void Deserialize(int NewSessionId, int NewPartyId, int NewUserId);

	int GetSessionId() { return SessionId; }
	int GetPartyId() { return PartyId; }
	int GetUserId() { return UserId; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EntryInfo")
	int SessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EntryInfo")
	int PartyId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EntryInfo")
	int UserId;
};