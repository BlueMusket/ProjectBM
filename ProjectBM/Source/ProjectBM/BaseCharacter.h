// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacterInterface.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	// 체력 관리 컴포넌트
	UHealthComponent* HealthComponent;

public:
	virtual void OnDeath_Implementation() override;
};
