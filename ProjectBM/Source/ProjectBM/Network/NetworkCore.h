// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Sockets.h"
#include "CoreMinimal.h"


class FWorkerThread : public FRunnable
{
public:
	FWorkerThread(FSocket* InSocket);
	virtual ~FWorkerThread();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	FString ReceiveMessage();
private:
	FSocket* Socket;
	FRunnableThread* Thread;
	bool bStopThread;
};

/**
 * 
 */

class PROJECTBM_API CNetworkCore
{

private:
	FSocket* Socket;
	TUniquePtr<FWorkerThread> WorkerThread;
	bool bIsConnected;

public:
	~CNetworkCore();

	void Shutdown();
	bool Connect(const FString& IPAddress, int32 Port);
	bool Send(const TArray<uint8>& Data);


public:
	// 싱글톤 인스턴스 접근용 정적 메서드
	static CNetworkCore* Get();

private:
	CNetworkCore();
};
