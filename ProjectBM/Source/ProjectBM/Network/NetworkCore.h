// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Sockets.h"
#include "CoreMinimal.h"

/**
 * 
 */

class PROJECTBM_API CNetworkCore
{

private:
	FSocket* Socket;
	bool IsRunning;
	bool IsConnected;

public:
	~CNetworkCore();

	void Shutdown();
	bool Connect(const FString& IPAddress, int32 Port);
	bool Send(const TArray<uint8>& Data);
	bool CheckRunning() { return IsRunning; }
	void SetRunning(bool Value) { IsRunning = Value; }

public:
	// 싱글톤 인스턴스 접근용 정적 메서드
	static CNetworkCore* Get();

private:
	CNetworkCore();
};
