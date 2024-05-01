// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "EffectManager.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTBM_API UEffectManager : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // 싱글톤 인스턴스 접근용 정적 메서드
    static UEffectManager* Get();

private:
    UEffectManager();


public:
    void Init();

    // 이펙트 관리 관련 메서드
    void RegisterEffect(int64 Key, UNiagaraSystem* Effect);

    bool SpawnEffect(int64 Key, USceneComponent* AttachToComponent, FVector Location, FRotator Rotation, float LifeSpan);

private:
    // 싱글톤 인스턴스를 저장하는 정적 멤버
    static UEffectManager* Instance;

    // 등록된 이펙트 리스트
    TMap<int64, UNiagaraSystem*> Effects;
};