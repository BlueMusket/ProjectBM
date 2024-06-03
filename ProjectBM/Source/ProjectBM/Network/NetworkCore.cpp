// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkCore.h"
#include "Async/AsyncWork.h"
#include "SocketSubsystem.h"
#include "Networking.h"


class FRecvTask : public FNonAbandonableTask
{
public:
    FRecvTask(CNetworkCore* NewOwner, FSocket* NewSocket) : Socket(NewSocket), Owner(NewOwner) {}

    void DoWork()
    {
       // 예시 작업: 일정 시간 동안 대기
        FPlatformProcess::Sleep(1.0f);
        UE_LOG(LogTemp, Warning, TEXT("Async task completed"));
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FRecvTask, STATGROUP_ThreadPoolAsyncTasks);
    }

private:
    FSocket* Socket;

    CNetworkCore* Owner;
};


class FPingTask : public FNonAbandonableTask
{
public:
    FPingTask(CNetworkCore* NewOwner, FSocket* NewSocket) : Socket(NewSocket), Owner(NewOwner) {}

    void DoWork()
    {
        // 연결이 완료 될 때 까지 대기
        while (true)
        {
            ESocketConnectionState State = Socket->GetConnectionState();
            if (SCS_Connected == State)
            {
                break;
            }

            FPlatformProcess::Sleep(1.0f);
        }

        // recv 시작
        while (true)
        {
            if (Socket && Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(1.0)))
            {
                FString ReceivedMessage = ReceiveMessage();
                if (!ReceivedMessage.IsEmpty())
                {
                    UE_LOG(LogTemp, Log, TEXT("Received message: %s"), *ReceivedMessage);
                }
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Async task completed"));
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FPingTask, STATGROUP_ThreadPoolAsyncTasks);
    }

    FString ReceiveMessage()
    {
        TArray<uint8> ReceivedData;
        uint32 Size;
        FString ReceivedString;

        while (Socket->HasPendingData(Size))
        {
            ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

            int32 Read = 0;
            Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

            ReceivedString += FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
        }

        return ReceivedString;
    }


private:
    FSocket* Socket;
    CNetworkCore* Owner;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CNetworkCore* CNetworkCore::Get()
{
    static CNetworkCore* Instance = nullptr;

    if (!Instance)
    {
        Instance = new CNetworkCore();
    }
    return Instance;
}


CNetworkCore::CNetworkCore()
    : Socket(nullptr), bIsConnected(false)
{
}

CNetworkCore::~CNetworkCore()
{
    Shutdown();
}

bool CNetworkCore::Connect(const FString& IPAddress, int32 Port)
{
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

    FIPv4Address IP;
    FIPv4Address::Parse(IPAddress, IP);

    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);

    Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("default"), Addr->GetProtocolType());

    Socket->SetNonBlocking();

    (new FAutoDeleteAsyncTask<FRecvTask>(this, Socket))->StartBackgroundTask();
    (new FAutoDeleteAsyncTask<FPingTask>(this, Socket))->StartBackgroundTask();

    bIsConnected = Socket->Connect(*Addr);

    if (bIsConnected)
    {
        UE_LOG(LogTemp, Log, TEXT("Connected to server"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to connect to server"));
    }

    
    ESocketErrors LastError = SocketSubsystem->GetLastErrorCode();

    return bIsConnected;
}

void CNetworkCore::Shutdown()
{
    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
    bIsConnected = false;
}

bool CNetworkCore::Send(const TArray<uint8>& Data)
{
    if (!bIsConnected || !Socket)
    {
        return false;
    }

    int32 BytesSent = 0;
    return Socket->Send(Data.GetData(), Data.Num(), BytesSent);
}