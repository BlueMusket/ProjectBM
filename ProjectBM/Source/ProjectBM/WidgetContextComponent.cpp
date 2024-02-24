// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetContextComponent.h"
#include "RestartWidget.h"
#include "HUDWidget.h"
#include "AdminWidget.h"


// Sets default values for this component's properties
UWidgetContextComponent::UWidgetContextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RestartWidget = nullptr;
	HUDWidget = nullptr;
	AdminWidget = nullptr;

	// ...
}


// Called when the game starts
void UWidgetContextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWidgetContextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UWidgetContextComponent::CreateHUD()
{
	if (nullptr != BP_HUDWidget)
	{
		//HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		//if (nullptr != HUDWidget)
		//{
		//	HUDWidget->AddToViewport();
		//}
	}
}

void UWidgetContextComponent::ShowRestartWidget()
{
	//if (nullptr != BP_RestartWidget)
	//{
	//	SetPause(true);
	//	SetInputMode(FInputModeGameAndUI());

	//	SetShowMouseCursor(true);
	//	RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
	//	if (nullptr != RestartWidget)
	//	{
	//		RestartWidget->AddToViewport();
	//	}
	//}
}

void UWidgetContextComponent::HideRestartWidget()
{
	//RestartWidget->RemoveFromParent();
	//RestartWidget->Destruct();
	//SetPause(false);
	//SetShowMouseCursor(false);
}

void UWidgetContextComponent::ToggleAdminWidget()
{
	if (nullptr != BP_AdminWidget)
	{
		//if (nullptr == AdminWidget)
		//{
		//	AdminWidget = CreateWidget<UAdminWidget>(this, BP_AdminWidget);
		//}

		//if (true == AdminWidget->IsVisible())
		//{
		//	AdminWidget->RemoveFromParent();
		//}
		//else
		//{
		//	AdminWidget->AddToViewport();
		//}
	}
}