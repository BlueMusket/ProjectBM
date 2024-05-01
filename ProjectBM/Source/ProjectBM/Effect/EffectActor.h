// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actor/BaseActor.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "EffectActor.generated.h"

UCLASS()
class PROJECTBM_API AEffectActor : public ABaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectActor(const FObjectInitializer& ObjectInitializer);

public:
	void Initialize(FVector ColisionSize, float LifeSpan);
	void Deactive();
	bool IsActive();
	void FindTargets(TArray<AActor*>& OutTargets);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	int IntervalTick; // 반복 틱

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	// Niagara 이펙트 컴포넌트
	UPROPERTY(VisibleAnywhere)
	int64 EffectId;
private:
	bool bIsActive; // 동작하는 중인지
	float LastTick; // 마지막 틱
	float NextActionTick; // 다음에 액션할 틱
};
