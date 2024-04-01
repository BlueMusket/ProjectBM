// Fill out your copyright notice in the Description page of Project Settings.


#include "PCState.h"
#include "ActionContext.h"

APCState::APCState()
{
	ActionContext = new CActionContext();
}

APCState::~APCState()
{
	delete ActionContext;
}

void APCState::BeginPlay()
{
    Super::BeginPlay();

    StartTimer();

}


void APCState::StartTimer()
{
	// 100ms마다 RepeatedFunction를 호출합니다.
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APCState::Tick, 0.1f, true);
}

void APCState::Tick()
{
	ActionContext->Tick();
}