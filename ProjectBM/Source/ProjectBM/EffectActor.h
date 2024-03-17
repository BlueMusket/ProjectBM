// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "Components/BoxComponent.h"
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

	// Static mesh component to display the FBX model
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

private:
	bool bIsActive; // 동작하는 중인지
	float LastTick; // 마지막 틱
	float NextActionTick; // 다음에 액션할 틱
};
