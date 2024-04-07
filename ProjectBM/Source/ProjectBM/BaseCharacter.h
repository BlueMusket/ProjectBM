// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacterInterface.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UAttackComponent;
class UActionContextComponent;

UCLASS()
class PROJECTBM_API ABaseCharacter : public ACharacter, public IBaseCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	// 체력 관리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

	// 공격 관리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAttackComponent* AttackComponent;

	// 액션 처리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UActionContextComponent* ActionContextComponent;
public:
	virtual void OnDeath_Implementation() override;
	virtual void OnTakeDamage_Implementation() override;
};