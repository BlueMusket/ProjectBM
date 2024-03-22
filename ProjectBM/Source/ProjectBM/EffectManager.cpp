// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectManager.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "EffectDataTable.h"

UEffectManager* UEffectManager::Instance = nullptr;


UEffectManager::UEffectManager()
{

}

void UEffectManager::Init()
{
    // 데이터 테이블의 경로
    const FString DataTablePath = TEXT("/Game/DataTable/EeffectDataTable.EeffectDataTable");

    // 런타임에 데이터 테이블 로드
    UDataTable* LoadedDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));

    if (LoadedDataTable != nullptr)
    {
        int identity = 0;
        // 모든 행 순회
        LoadedDataTable->ForeachRow<FEffectDataTable>(TEXT(""), [&](const FName& Key, const FEffectDataTable& Value)
            {
                UNiagaraSystem* NiagaraEffect = Value.Effect;
                if (NiagaraEffect != nullptr)
                {
                    // 1부터
                    Get()->RegisterEffect(++identity, NiagaraEffect);
                    // NiagaraEffect를 사용하는 로직, 예: 로그 출력
                    UE_LOG(LogTemp, Warning, TEXT("Effect Name: %s"), *NiagaraEffect->GetName());
                }
            });
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Data table not found."));
    }

}



UEffectManager* UEffectManager::Get()
{
    if (!Instance)
    {
        Instance = NewObject<UEffectManager>();
        Instance->AddToRoot();  // 가비지 컬렉션으로부터 보호
    }
    return Instance;
}

void UEffectManager::RegisterEffect(int64 Key, UNiagaraSystem* Effect)
{
    if (Effect)
    {
        Effects.Add(Key, Effect);
    }
}

bool UEffectManager::SpawnEffect(int64 Key, USceneComponent* AttachToComponent, FVector Location, FRotator Rotation, float LifeSpan)
{
    bool result = false;
    do
	{
		UNiagaraSystem** EffectTemplate = Effects.Find(Key);
		if (!EffectTemplate || !AttachToComponent)
		{
			break;
		}

		UNiagaraComponent* NewEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(*EffectTemplate, AttachToComponent, NAME_None, Location, Rotation, EAttachLocation::KeepRelativeOffset, true);

		if (nullptr == NewEffect)
		{
			break;
		}

        NewEffect->SetAutoDestroy(true);

        // 따로 생명 주기를 조절해야할지..

	} while (false);


    return result;
}