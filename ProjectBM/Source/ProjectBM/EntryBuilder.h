// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ABasePlayerController;
/**
 * 
 */
class PROJECTBM_API CEntryBuilder
{
public:
	CEntryBuilder();
	~CEntryBuilder();

public:
	void Build(ABasePlayerController* PlayerController);
};
