// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBM_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
	void OnRestartClicked();

public:
	// BindWidget : 블루프린트의 버튼과 바인드한다.
	// OptionalWidget : 블루프린트의 버튼이름과 C++의 변수명이 일치하지 않더라고 컴파일 에러가 발생하지 않는다.
	UPROPERTY(meta = (BindWidget, OptionalWidget = true))
	class UButton* RestartButton;


};
