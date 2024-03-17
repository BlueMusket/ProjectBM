// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowParam.h"
#include "PC.h"
#include "BasePlayerController.h"

FThrowParam::FThrowParam()
	: ThrowRotation(FRotator())
	, ThrowPower(0.f)
	{

}

FThrowParam::~FThrowParam()
{

}


bool FThrowParam::IsValid()
{
	return true;
}