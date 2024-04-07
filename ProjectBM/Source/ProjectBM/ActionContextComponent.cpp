// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionContextComponent.h"
#include "BasePlayerController.h"
#include "ThrowParam.h"
#include "PC.h"
#include "Kismet/GameplayStatics.h"

UActionContextComponent::UActionContextComponent()
	: StartTick(0)
	, ThrowParam()
	, IsActive(false)
	, Lock()
{
}

UActionContextComponent::~UActionContextComponent()
{
}


// Called every frame
void UActionContextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (ROLE_Authority != GetOwnerRole())
	{
		return;
	}

	// 나중에 액션 타입별로 기능을 추가해야 할수도...

	{
		CScopeLock ScopeLock(Lock);

		if (true == CheckCanAction())
		{
			StartAction();

			DeActive();
		}
	}
}

void UActionContextComponent::InitAction(int ActiveTick, FThrowParam& Param)
{
	{
		CScopeLock ScopeLock(Lock);

		int32 currentMiliTick = FDateTime::Now().GetMillisecond();

		// 이미 실행중이라면 다른 처리
		if (true == GetIsActive())
		{
			return;
		}


		StartTick = currentMiliTick + ActiveTick;
		ThrowParam = Param;

		Active();
	}
}

void UActionContextComponent::StartAction()
{
	{
		CScopeLock ScopeLock(Lock);


	}
}


bool UActionContextComponent::CheckCanAction()
{
	bool canAction = false;

	do
	{
		if (false == GetIsActive())
		{
			break;
		}

		int32 currentMiliTick = FDateTime::Now().GetMillisecond();
		if (currentMiliTick < StartTick)
		{
			break;
		}

		canAction = true;

	} while (false);
		
	return canAction;
}