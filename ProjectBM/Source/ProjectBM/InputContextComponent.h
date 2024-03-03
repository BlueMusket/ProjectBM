// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputContextComponent.generated.h"


class UInputComponent;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPowerTickDelegate, float, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAngleTickDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBM_API UInputContextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputContextComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	
	void OnMove(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	void OnThrow(const FInputActionValue& Value);
	void OnAngle(const FInputActionValue& Value);
	void OnPrePower(const FInputActionValue& Value);
	void OnPower(const FInputActionValue& Value);
	void OnPostPower(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputMappingContext* IC_PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* IA_Throw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* IA_Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		class UInputAction* IA_Power;

public:
	// 델리게이트 선언
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPowerTickDelegate OnPowerTickEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAngleTickDelegate OnAngleTickEvent;


private:
	bool bIsOnPower;
};
