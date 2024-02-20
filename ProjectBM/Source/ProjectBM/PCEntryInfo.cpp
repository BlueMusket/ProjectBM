// Fill out your copyright notice in the Description page of Project Settings.


#include "PCEntryInfo.h"
#include "Net/UnrealNetwork.h"

void UPCEntryInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 이 클래스의 리플리케이션 가능한 프로퍼티를 설정
    DOREPLIFETIME(UPCEntryInfo, SessionId);
    DOREPLIFETIME(UPCEntryInfo, PartyId);
    DOREPLIFETIME(UPCEntryInfo, UserId);
}

void UPCEntryInfo::Deserialize(UPCEntryInfo& NewInfo)
{
    SessionId = NewInfo.SessionId;
    PartyId = NewInfo.PartyId;
    UserId = NewInfo.UserId;
}

void UPCEntryInfo::Deserialize(int NewSessionId, int NewPartyId, int NewUserId)
{
    SessionId = NewSessionId;
    PartyId = NewPartyId;
    UserId = NewUserId;
}