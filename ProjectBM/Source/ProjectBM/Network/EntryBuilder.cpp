// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryBuilder.h"
#include "../Controller/BasePlayerController.h"
#include "Misc/DefaultValueHelper.h"

CEntryBuilder::CEntryBuilder(ABasePlayerController* Target)
	: PlayerController(Target)
{
}

CEntryBuilder::~CEntryBuilder()
{
}

void CEntryBuilder::Build(const FString& Options)
{
    FString BuildOption = Options.Replace(TEXT(" "), TEXT(""));

	// ','로 분리하여 각 파트를 TArray에 저장
	TArray<FString> Parts;
    BuildOption.ParseIntoArray(Parts, TEXT(","), true);

    // 결과 값을 저장할 변수
    int32 SessionId = 0;
    int32 PartyId = 0;
    int32 UserId = 0;

    for (FString& Part : Parts)
    {
        // '='로 분리하여 키와 값을 추출
        FString Key, Value;
        Part.Split(TEXT("="), &Key, &Value);

        // Key에서 '?' 제거
        Key.RemoveFromStart("?");

        // 값을 int32로 변환하고 적절한 변수에 할당
        if ("SessionId" == Key)
        {
            FDefaultValueHelper::ParseInt(Value, SessionId);
        }
        else if ("PartyId" == Key)
        {
            FDefaultValueHelper::ParseInt(Value, PartyId);
        }
        else if ("UserId" == Key)
        {
            FDefaultValueHelper::ParseInt(Value, UserId);
        }
    }

    PlayerController->Deserialize(SessionId, PartyId, UserId);
}