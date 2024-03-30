// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetContextComponent.generated.h"

class ABasePlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBM_API UWidgetContextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWidgetContextComponent();
	UWidgetContextComponent(ABasePlayerController* Owner);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Init();


public: // widget
	void CreateHUD();
	void ShowRestartWidget();
	void HideRestartWidget();
	void ToggleAdminWidget();
	void UpdateHealthPercent(float HealthPercent);

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class URestartWidget> BP_RestartWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UHUDWidget> BP_HUDWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UAdminWidget> BP_AdminWidget;

private: // widget
	UPROPERTY()
		class URestartWidget* RestartWidget;

	UPROPERTY()
		class UHUDWidget* HUDWidget;

	UPROPERTY()
		class UAdminWidget* AdminWidget;

	
	ABasePlayerController* Controller;
		
};
