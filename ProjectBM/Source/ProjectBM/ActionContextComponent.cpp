// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionContextComponent.h"
#include "BasePlayerController.h"
#include "PC.h"
#include "Kismet/GameplayStatics.h"
#include "AttackComponent.h"

#if UE_EDITOR
PRAGMA_DISABLE_OPTIMIZATION
#endif

UActionContextComponent::UActionContextComponent()
	: StartTime()
	, IsActive(false)
	, Lock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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


		// 이미 실행중이라면 다른 처리
		if (true == GetIsActive())
		{
			return;
		}

		FTimespan TimeToAdd = FTimespan::FromMilliseconds(ActiveTick);

		StartTime = FDateTime::Now() + TimeToAdd;

		Active();
	}
}

void UActionContextComponent::StartAction()
{
	{
		CScopeLock ScopeLock(Lock);

		UAttackComponent* attackComponent = GetOwner()->GetComponentByClass<UAttackComponent>();

		if (nullptr != attackComponent)
		{
			attackComponent->OnThrow();
		}
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

		if (FDateTime::Now() < StartTime)
		{
			break;
		}

		canAction = true;

	} while (false);
		
	return canAction;
}

void UActionContextComponent::ServerStartThrowAction(FThrowParam Param)
{
	// 서버가 아니면 처리 X
	if (ROLE_Authority != GetOwnerRole())
	{
		return;
	}

	InitAction(100, Param);
}